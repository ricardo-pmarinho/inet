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

#ifndef INET_COMMON_ORACLE_ORACLE_H_
#define INET_COMMON_ORACLE_ORACLE_H_

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IL3AddressType.h"

namespace inet {

using namespace std;

class INET_API Oracle : public cSimpleModule
{
private:
    map<L3Address, pair<L3Address,int>> *devsChMap; //map of current CH and its battery for a device
    map<L3Address, int> *chDef; //address and how many times the node was elected CH
    map<L3Address, int> *semiChDef; //address and how many times the node was elected semi CH
    map<L3Address, pair<int,bool>> *curCHs; //current CH nodes with their battery percentage
    pair<L3Address, int> *chCandidate; //the current best candidate node address for CH with it's battery percentage
    map<L3Address,pair<L3Address,bool>> *semiChs; //maps the devices that are cluster heads but are connected to other cluster heads
    map<L3Address,pair<L3Address,bool>> *fullChs; //maps the devices that are cluster heads and are not connected to other cluster heads
    map<L3Address,bool> *noChs; //maps the devices that are not connected to any cluster head
    map<L3Address,bool> *devs; //maps the devices that are not a CH
    map<L3Address,bool> *shutdownNodes; //stores the nodes that has already shutdown
    map<L3Address,bool> *startNodes; //stores the nodes that has send a cainTrigger message
    map<L3Address,bool> *recNodes;//full ch receiving messages
    L3Address antennaAddress;

    bool chUpdated=false;

    simsignal_t numChSignal;
    simsignal_t numSemiChSignal;
    simsignal_t numActiveChSignal;
    simsignal_t numActiveSemiChSignal;
    simsignal_t numActiveFullChSignal;
    simsignal_t numNoChSignal;
    simsignal_t chUpgradeSignal;
    simsignal_t chDowngradeSignal;
    simsignal_t simulationEndSignal;
    simsignal_t startNodeSignal;
    long numCh=0;
    long numSemiCh=0;
    long numActiveCh=0;
    long numActiveSemiCh=0;
    long numActiveFullCh=0;
    long numNoCh=0;
    long chDowngrade=0;
    long chUpgrade=0;
    long simulationEnd=0;
    long startNodesNum=0;
protected:
    void handleMessageWhenUp(cMessage *msg);
    void initialize(int stage);
    virtual int numInitStages() const { return NUM_INIT_STAGES; }
public:
    Oracle();
    virtual ~Oracle();

    pair<L3Address,int> getChforDev(L3Address devAddr){
        return devsChMap->operator [](devAddr);
    }

    void setChforDev(L3Address devAddr, L3Address chAddr, int batteryPower);

    map<L3Address, int>* getChDef() const {
        return chDef;
    }
    void printChDef();
    void setChDef();
    void printDevsChMap();

    const pair<L3Address, int>* getChCandidate() const {
        return chCandidate;
    }

    void setChCandidate(L3Address candidate, int battery) {
        this->chCandidate = new pair<L3Address,int>(candidate,battery);
    }

    void updateCandidate(L3Address candidate, int battery){
        this->chCandidate->first = candidate;
        this->chCandidate->second = battery;
    }

    void setAntennaAddress(L3Address antennaAddr);
    L3Address getAntennaAddress();
    L3Address getCainDestination(L3Address nodeAddr, int numNode);

    bool isCh(L3Address devAddr);
    void updateCurrChs();
    void updateSemiChs();
    void printCurrChs();
    void printNoChs();
    void printSemiChs();
    void printFullChs();
    void clearDevCh(L3Address devAddr);
    void printDevs();

    void setShudDownNode(L3Address nodeAddr);
    void checkShutdownTime(int numNodes);
    void setStartNode(L3Address nodeAddr);

    void insertRecNode(L3Address nodeAddr);
    void shutDownRecNode(L3Address nodeAddr);
    void checkShutdownNodes();
};

} /* namespace inet */

#endif /* INET_COMMON_ORACLE_ORACLE_H_ */
