//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "inet/common/oracle/Oracle.h"


namespace inet {

Define_Module(Oracle);


void Oracle::initialize(int stage){
    if (stage == INITSTAGE_LOCAL) {
        chDef = new map<L3Address,int>();
        chCandidate = new pair<L3Address,int>(L3Address("0.0.0.0"),-1);
        devsChMap = new map<L3Address,pair<L3Address,int>>();
        curCHs = new map<L3Address,pair<int,bool>>();
        semiChs = new map<L3Address,pair<L3Address,bool>>();
        fullChs = new map<L3Address,pair<L3Address,bool>>();
        noChs = new map<L3Address,bool>();
        semiChDef = new map<L3Address,int>();
        devs = new map<L3Address,bool>;
        shutdownNodes = new map<L3Address,bool>();
        startNodes = new map<L3Address,bool>();
        recNodes = new map<L3Address,bool>();

        numChSignal = registerSignal("numChSignal");
        numSemiChSignal = registerSignal("numSemiChSignal");
        numActiveChSignal = registerSignal("numActiveChSignal");
        numActiveSemiChSignal = registerSignal("numActiveSemiChSignal");
        numActiveFullChSignal = registerSignal("numActiveFullChSignal");
        numNoChSignal = registerSignal("numNoChSignal");
        chUpgradeSignal = registerSignal("chUpgradeSignal");
        chDowngradeSignal = registerSignal("chDowngradeSignal");
        simulationEndSignal = registerSignal("simulationEndSignal");
        startNodeSignal = registerSignal("startNodeSignal");
    }
}

void Oracle::handleMessageWhenUp(cMessage *msg){

}

void Oracle::setAntennaAddress(L3Address antennaAddr){
    antennaAddress = antennaAddr;
}

L3Address Oracle::getAntennaAddress(){
    return antennaAddress;
}

void Oracle::setChforDev(L3Address devAddr, L3Address chAddr, int batteryPower){
    if(!devAddr.isUnspecified() && !chAddr.isUnspecified()){
        pair<L3Address,int> ch = pair<L3Address,int>(chAddr,batteryPower);
        devsChMap->operator [](devAddr) = ch;
    }
    chUpdated=false;
}

void Oracle::setChDef(){
    if(!chUpdated){
        map<L3Address, pair<int,bool>>::iterator curChIt = curCHs->begin();
        for(;curChIt != curCHs->end();curChIt++){
            L3Address chAddr = curChIt->first;
            EV << "setting " << chAddr << endl;
            EV << chDef->operator [](chAddr) << endl;
            if(curChIt->second.second){
                if(chDef->count(chAddr) == 0)
                    chDef->operator [](chAddr)=1;
                else
                    chDef->operator [](chAddr)++;
            }
        }
    }
    chUpdated=true;
}

void Oracle::printChDef(){
    EV_INFO << "Cluster Heads definitions:" << endl;
    map<L3Address,int>::iterator it;
    for(it = chDef->begin(); it != chDef->end(); it++){
        EV << "CH IP: " << it->first << " | count: " << it->second << endl;;
    }
}

void Oracle::updateCurrChs(){
    numActiveCh = 0;
    map<L3Address,pair<L3Address,int>>::iterator devsChIt = devsChMap->begin();//<devAddr,<chAddr,battery>>
    printDevsChMap();

    if(!curCHs->empty()){
        map<L3Address,pair<int,bool>>::iterator curChIt = curCHs->begin();
        for(;curChIt != curCHs->end();curChIt++)
            curChIt->second.second = false;
    }
    if(!noChs->empty()){
        map<L3Address,bool>::iterator noChIt = noChs->begin();
        for(; noChIt != noChs->end(); noChIt++)
            noChIt->second = false;
    }

    devsChIt = devsChMap->begin();
    for(;devsChIt != devsChMap->end(); devsChIt++){
        L3Address chAddr = devsChIt->second.first;
        if(!chAddr.isUnspecified()){
            pair<int,bool> chInfo = pair<int,bool>(devsChIt->second.second,true);
            curCHs->operator [](chAddr) = chInfo;
        }else
            noChs->operator [](devsChIt->first) = true;
    }
    numCh=curCHs->size();
    numNoCh = noChs->size();

    map<L3Address,pair<int,bool>>::iterator curChIt = curCHs->begin();
    for(;curChIt != curCHs->end();curChIt++){
        if(curChIt->second.second)
            numActiveCh++;
    }
    emit(numChSignal, numCh);
    emit(numNoChSignal,numNoCh);
    emit(numActiveChSignal,numActiveCh);

    updateSemiChs();
    setChDef();

    printCurrChs();
    printSemiChs();
    printFullChs();
    printNoChs();
    printChDef();
}

void Oracle::updateSemiChs(){
    vector<L3Address> oldSemiCh;
    vector<L3Address> oldFullCh;
    vector<L3Address> newSemiCh;
    vector<L3Address> newFullCh;


    map<L3Address,pair<L3Address,bool>>::iterator semiChIt = semiChs->begin();
    for(;semiChIt != semiChs->end(); semiChIt++){
        if(semiChIt->second.second)
            oldSemiCh.push_back(semiChIt->first);
    }
    map<L3Address,pair<L3Address,bool>>::iterator fullChIt = fullChs->begin();
    for(;fullChIt != fullChs->end(); fullChIt++){
        if(fullChIt->second.second)
            oldFullCh.push_back(semiChIt->second.first);
    }

    map<L3Address,pair<int,bool>>::iterator curChIt = curCHs->begin();
    if(!semiChs->empty()){
        semiChIt = semiChs->begin();
        for(;semiChIt != semiChs->end(); semiChIt++)
            semiChIt->second.second = false;
    }
    if(!fullChs->empty()){
        fullChIt = fullChs->begin();
        for(;fullChIt != fullChs->end(); fullChIt++)
            fullChIt->second.second = false;
    }
    for(;curChIt != curCHs->end();curChIt++){
        L3Address semichAddr = curChIt->first;
        L3Address chAddr = devsChMap->operator [](semichAddr).first;
        if(semichAddr != chAddr)
            semiChs->operator [](semichAddr)=pair<L3Address,bool>(chAddr,true);
        else
            fullChs->operator [](chAddr)=pair<L3Address,bool>(chAddr,true);
    }

    semiChIt = semiChs->begin();
    for(;semiChIt != semiChs->end(); semiChIt++){
        if(semiChIt->second.second){
            newSemiCh.push_back(semiChIt->first);
            newFullCh.push_back(semiChIt->second.first);
        }
    }

    fullChIt = fullChs->begin();
    for(;fullChIt != fullChs->end(); fullChIt++){
        if(fullChIt->second.second)
            newFullCh.push_back(fullChIt->second.first);
    }

    numSemiCh=semiChs->size();

    chUpgrade=0;
    vector<L3Address>::iterator listChIt = oldSemiCh.begin();
    for(; listChIt != oldSemiCh.end(); listChIt++){
        vector<L3Address>::iterator newChit = newFullCh.begin();
        for(; newChit != newFullCh.end(); newChit++){
            if(*newChit == *listChIt)
                chUpgrade++;
        }
    }

    chDowngrade=0;
    listChIt = newSemiCh.begin();
    for(; listChIt != newSemiCh.end(); listChIt++){
        vector<L3Address>::iterator oldChit = oldFullCh.begin();
        for(; oldChit != oldFullCh.end(); oldChit++){
            if(*oldChit == *listChIt)
                chDowngrade++;
        }
    }

    emit(numSemiChSignal,numSemiCh);
    emit(chUpgradeSignal,chUpgrade);
    emit(chDowngradeSignal,chDowngrade);
}

L3Address Oracle::getCainDestination(L3Address nodeAddr, int numNode){
    if(devsChMap->size() > 0){
        int index = rand()%devsChMap->size();
        int searchTimes = par("searchTimes");
        map<L3Address,pair<L3Address,int>>::iterator it = devsChMap->begin();
        std::advance(it,index);
        for(int i = 0; i < searchTimes; i++){
            if(it->first != nodeAddr && !isCh(it->first)){
                return it->first;
            }else{
                index = rand()%devsChMap->size();
                it = devsChMap->begin();
                std::advance(it,index);
            }
        }
        return L3Address("0.0.0.0");
    }
}

void Oracle::printDevsChMap(){
    map<L3Address,pair<L3Address,int>>::iterator devsChIt = devsChMap->begin();//<devAddr,<chAddr,battery>>
    EV << "Devices CH map: " << endl;
        for(;devsChIt != devsChMap->end(); devsChIt++)
            EV << "Dev addr: " << devsChIt->first << "| dev ch: " << devsChIt->second.first <<
            "| ch battery: " << devsChIt->second.second << endl;
}

void Oracle::printCurrChs(){
    map<L3Address,pair<int,bool>>::iterator curChIt = curCHs->begin();
    EV_INFO << "Current Cluster Heads:" << endl;
    for(;curChIt != curCHs->end();curChIt++)
        EV << "CH addr: " << curChIt->first << "| Battery: " << curChIt->second.first <<
        "| Active=" << (curChIt->second.second ? "True" : "False") << endl;
}

void Oracle::printNoChs(){
    map<L3Address,bool>::iterator noChIt = noChs->begin();
    EV << "Devices without CH: " << endl;
    for(; noChIt != noChs->end(); noChIt++)
        EV << "Device addr: " << noChIt->first <<
        "| Active=" << (noChIt->second ? "True":"False") << endl;
}

void Oracle::printDevs(){
    map<L3Address,bool>::iterator devsIt = devs->begin();
    EV << "Devices that are not CH:" << endl;
    for(; devsIt != devs->end(); devsIt++)
        EV << "Device addr: " << devsIt->first << "| Active=" << (devsIt->second ? "True":"False") << endl;

}

void Oracle::printSemiChs(){
    numActiveSemiCh = 0;
    map<L3Address,pair<L3Address,bool>>::iterator semiChIt = semiChs->begin();
    EV<< "Semi Chs: " << endl;
    for(;semiChIt != semiChs->end(); semiChIt++){
        EV << "semi ch addr: " << semiChIt->first << "| Ch addr: " << semiChIt->second.first <<
                "| Active= " << (semiChIt->second.second ? "true" : "false") << endl;
        if(semiChIt->second.second)
            numActiveSemiCh++;
    }
    emit(numActiveSemiChSignal,numActiveSemiCh);
}

void Oracle::printFullChs(){
    numActiveFullCh=0;
    map<L3Address,pair<L3Address,bool>>::iterator fullChIt = fullChs->begin();
    EV<< "Full Chs: " << endl;
    for(;fullChIt != fullChs->end(); fullChIt++){
        EV << "Full Chs:  ch addr: " << fullChIt->first << "| Ch addr: " << fullChIt->second.first <<
                "| Active= " << (fullChIt->second.second ? "true" : "false") << endl;
        if(fullChIt->second.second)
            numActiveFullCh++;
    }
    emit(numActiveFullChSignal,numActiveFullCh);
}
/*
 * reset the cluster head to a device for the case that
 * it does not have a cluster head available due to battery
 * threshold
 * */
void Oracle::clearDevCh(L3Address devAddr){
    devsChMap->erase(devAddr);
}

bool Oracle::isCh(L3Address devAddr){
    if(semiChs->count(devAddr) > 0){
        if(semiChs->operator [](devAddr).second)
            return true;
    }
    if(fullChs->count(devAddr) > 0){
        if(fullChs->operator [](devAddr).second)
            return true;
    }
    return false;
}

void Oracle::setShudDownNode(L3Address nodeAddr){
    this->shutdownNodes->operator [](nodeAddr)=true;
}

void Oracle::setStartNode(L3Address nodeAddr){
    this->startNodes->operator [](nodeAddr)=true;
}

void Oracle::checkShutdownTime(int numNodes){
     if(this->shutdownNodes->size() >=0.7*numNodes){
         EV << "All nodes shutdown" << endl;
         simulationEnd = lround(simTime().dbl());

         emit(simulationEndSignal,simulationEnd);

         startNodesNum = this->startNodes->size();

         endSimulation();
     }
}

void Oracle::insertRecNode(L3Address nodeAddr){
    this->recNodes->operator [](nodeAddr)=true;
}

void Oracle::shutDownRecNode(L3Address nodeAddr){
    map<L3Address,bool>::iterator itMap = recNodes->find(nodeAddr);
    if(itMap != this->recNodes->end()){
        this->recNodes->operator [](nodeAddr)=false;
    }
}

void Oracle::checkShutdownNodes(){
    map<L3Address,bool>::iterator it = this->recNodes->begin();
    int nodeCount=0;
    for(; it != this->recNodes->end();it++){
        if(!it->second)
            nodeCount++;
    }
    if(nodeCount >=0.6*recNodes->size()){
        simulationEnd = lround(simTime().dbl());

        emit(simulationEndSignal,simulationEnd);

        startNodesNum = this->startNodes->size();

        EV << "node started: " << startNodesNum << endl;

//         emit(startNodeSignal,startNodesNum);
        endSimulation();
    }
}

Oracle::Oracle() {
    // TODO Auto-generated constructor stub

}

Oracle::~Oracle() {
    // TODO Auto-generated destructor stub
}

} /* namespace inet */
