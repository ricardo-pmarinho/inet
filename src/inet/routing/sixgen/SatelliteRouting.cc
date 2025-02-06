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

#include "SatelliteRouting.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/common/L3Tools.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/ipv4/IcmpHeader.h"
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "inet/networklayer/ipv4/Ipv4Route.h"
#include "inet/transportlayer/common/L4PortTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo.h"
#include "inet/routing/sixgen/HeartBeatRouteData.h"
#include "inet/common/geometry/common/Coord.h"
#include <cmath>
#include <string>

namespace inet {
namespace SatelliteRouting {

Define_Module(SatelliteRouting);

const int KIND_DELAYEDSEND = 100;

void SatelliteRouting::initialize(int stage)
{

    if (stage == INITSTAGE_ROUTING_PROTOCOLS)
        addressType = getSelfIPAddress().getAddressType();  // needed for handleStartOperation()

    RoutingProtocolBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        lastBroadcastTime = SIMTIME_ZERO;
        rebootTime = SIMTIME_ZERO;
        rreqId = sequenceNum = 0;
        rreqCount = rerrCount = 0;
        host = getContainingNode(this);
        routingTable = getModuleFromPar<IRoutingTable>(par("routingTableModule"), this);
        interfaceTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        networkProtocol = getModuleFromPar<INetfilter>(par("networkProtocolModule"), this);

        WirelessRoutingUDPPort = par("udpPort");
        askGratuitousRREP = par("askGratuitousRREP");
        useHelloMessages = par("useHelloMessages");
        destinationOnlyFlag = par("destinationOnlyFlag");
        activeRouteTimeout = par("activeRouteTimeout");
        helloInterval = par("helloInterval");
        allowedHelloLoss = par("allowedHelloLoss");
        netDiameter = par("netDiameter");
        nodeTraversalTime = par("nodeTraversalTime");
        rerrRatelimit = par("rerrRatelimit");
        rreqRetries = par("rreqRetries");
        rreqRatelimit = par("rreqRatelimit");
        timeoutBuffer = par("timeoutBuffer");
        ttlStart = par("ttlStart");
        ttlIncrement = par("ttlIncrement");
        ttlThreshold = par("ttlThreshold");
        localAddTTL = par("localAddTTL");
        jitterPar = &par("jitter");
        periodicJitter = &par("periodicJitter");

        myRouteTimeout = par("myRouteTimeout");
        deletePeriod = par("deletePeriod");
        blacklistTimeout = par("blacklistTimeout");
        netTraversalTime = par("netTraversalTime");
        nextHopWait = par("nextHopWait");
        pathDiscoveryTime = par("pathDiscoveryTime");
        expungeTimer = new cMessage("ExpungeTimer");
        counterTimer = new cMessage("CounterTimer");
        rrepAckTimer = new cMessage("RrepAckTimer");
        blacklistTimer = new cMessage("BlackListTimer");
        if (useHelloMessages)
            helloMsgTimer = new cMessage("HelloMsgTimer");

        recCainFwdMsgSignal = registerSignal("recCainFwdMsgSignal");
        distSignal = registerSignal("distSignal");
        recDroneMsgSignal = registerSignal("recDroneMsgSignal");
        recSatMsgSignal = registerSignal("recSatMsgSignal");
        droneDistSignal = registerSignal("droneDistSignal");
        satDistSignal = registerSignal("satDistSignal");

    }
    else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {
        networkProtocol->registerHook(0, this);
        host->subscribe(linkBrokenSignal, this);
        usingIpv6 = (routingTable->getRouterIdAsGeneric().getType() == L3Address::IPv6);
        neighborBattery = new std::map<L3Address,int>();
        baseMobility = check_and_cast<BonnMotionMobility*>(host->getSubmodule("mobility"));
        energyStorage = check_and_cast<SimpleEpEnergyStorage*>(host->getSubmodule("energyStorage"));
        energyManagement = check_and_cast<SimpleEpEnergyManagement*>(host->getSubmodule("energyManagement"));
        numNodes = getModuleByPath("simpleNetwork")->par("numHost");
        antennaAddr = addressType->getUnspecifiedAddress();
        qtd_ranges = 3;
        send_prob = 50;
        distMap = new map<L3Address,double>();
        neighbMap = new map<L3Address,int>();
        sentMessages = new list<std::string>();
        leachNeigh = new std::vector<L3Address>();

        routes = new map<pair<L3Address,L3Address>,pair<L3Address,int>>();
        revRoute = new map<pair<L3Address,L3Address>,L3Address>();

        fwdAck = new vector<int>();
        reqAck = new vector<int>();
        hopAck = new vector<int>();
        int mlThreshold = getModuleByPath("simpleNetwork")->par("mlThreshold");

        vector<float>* a0;
        vector<float>* a1;
        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(0);
        a0->push_back(0.15);
        a0->push_back(0.35);
        a1->push_back(0.35);
        a1->push_back(0.15);
        a1->push_back(0);
        stateMatrix[0][0]=a0;
        stateMatrix[0][1]=a1;
        stateMatrix[0][2]=a0;
        stateMatrix[0][3]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();
        a0->push_back(0.1);
        a0->push_back(0.2);
        a0->push_back(0.2);
        a1->push_back(0);
        a1->push_back(0);
        a1->push_back(0);
        stateMatrix[1][0]=a0;
        stateMatrix[1][1]=a1;
        stateMatrix[1][2]=a0;
        stateMatrix[1][3]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();
        a0->push_back(0);
        a0->push_back(0.15);
        a0->push_back(0.35);
        a1->push_back(0);
        a1->push_back(0);
        a1->push_back(0);
        stateMatrix[2][0]=a0;
        stateMatrix[2][1]=a1;
        stateMatrix[2][2]=a0;
        stateMatrix[2][3]=a1;

        create_reward_matrix();

        for(int i=0;i<3;i++){
            for(int j=0; j<4; j++){
                qMatrix[i][j]=0;
            }
        }

        network=network->createDnn(3, 2, 3, 1);

    }
}

void SatelliteRouting::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
    EV << "receive signal" << endl;
//    Enter_Method("receiveChangeNotification");
//    if (signalID == linkBrokenSignal) {
//        EV_DETAIL << "Received link break signal" << endl;
//        Packet *datagram = check_and_cast<Packet *>(obj);
//        const auto& networkHeader = findNetworkProtocolHeader(datagram);
//        if (networkHeader != nullptr) {
//            L3Address unreachableAddr = networkHeader->getDestinationAddress();
//            if (unreachableAddr.getAddressType() == addressType) {
//                // A node initiates processing for a RERR message in three situations:
//                //
//                //   (i)     if it detects a link break for the next hop of an active
//                //           route in its routing table while transmitting data (and
//                //           route repair, if attempted, was unsuccessful), or
//
//                // TODO: Implement: local repair
//
//                IRoute *route = routingTable->findBestMatchingRoute(unreachableAddr);
//
//                if (route && route->getSource() == this)
//                    handleLinkBreakSendRERR(route->getNextHopAsGeneric());
//            }
//        }
//    }
}


void SatelliteRouting::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (auto waitForRrep = dynamic_cast<WaitForRrep *>(msg))
            handleWaitForRREP(waitForRrep);
       else if (msg == helloMsgTimer)
            sendHelloMessagesIfNeeded();
        else if (msg == expungeTimer)
            expungeRoutes();

        else if (msg == counterTimer) {
            scheduleAt(simTime() + 1, counterTimer);
            timeCounter++;
            if(timeCounter == 5){
                timeCounter=0;
                com_range=0;
            }
            if(lround(simTime().dbl())>=176){
                //oracle_->shutDownSimulation();
            }
        }else if (msg == rrepAckTimer)
            handleRREPACKTimer();
        else if (msg == blacklistTimer)
            handleBlackListTimer();
        else if (msg->getKind() == KIND_DELAYEDSEND) {
            auto timer = check_and_cast<PacketHolderMessage*>(msg);
            socket.send(timer->dropOwnedPacket());
            delete timer;
        }
        else{
            throw cRuntimeError("Unknown self message");
        }
    }
    else
        socket.processMessage(msg);
}

void SatelliteRouting::handleBlackListTimer()
{
    simtime_t nextTime = SimTime::getMaxTime();

    for (auto it = blacklist.begin(); it != blacklist.end(); ) {
        auto current = it++;

        // Nodes are removed from the blacklist set after a BLACKLIST_TIMEOUT period
        if (current->second <= simTime()) {
            EV_DETAIL << "Blacklist lifetime has expired for " << current->first << " removing it from the blacklisted addresses" << endl;
            blacklist.erase(current);
        }
        else if (nextTime > current->second)
            nextTime = current->second;
    }

    if (nextTime != SimTime::getMaxTime())
        scheduleAt(nextTime, blacklistTimer);
}

void SatelliteRouting::sendHelloMessagesIfNeeded()
{
    ASSERT(useHelloMessages);
    // Every HELLO_INTERVAL milliseconds, the node checks whether it has
    // sent a broadcast (e.g., a RREQ or an appropriate layer 2 message)
    // within the last HELLO_INTERVAL.  If it has not, it MAY broadcast
    // a RREP with TTL = 1

    // A node SHOULD only use hello messages if it is part of an
    // active route.
    bool hasActiveRoute = false;

    for (int i = 0; i < routingTable->getNumRoutes(); i++) {
        IRoute *route = routingTable->getRoute(i);
        if (route->getSource() == this) {
            HeartBeatRouteData *routeData = check_and_cast<HeartBeatRouteData *>(route->getProtocolData());
            if (routeData->isActive()) {
                hasActiveRoute = true;
                break;
            }
        }
    }

    if (hasActiveRoute && (lastBroadcastTime == 0 || simTime() - lastBroadcastTime > helloInterval)) {
        EV_INFO << "It is hello time, broadcasting Hello Messages with TTL=1" << endl;
        auto helloMessage = createHelloMessage();
        sendHeartBeatpkg(helloMessage, addressType->getBroadcastAddress(), 1, 0);
    }

    scheduleAt(simTime() + helloInterval - *periodicJitter, helloMsgTimer);
}

void SatelliteRouting::handleRREPACKTimer()
{
    // when a node detects that its transmission of a RREP message has failed,
    // it remembers the next-hop of the failed RREP in a "blacklist" set.

    EV_INFO << "RREP-ACK didn't arrived within timeout. Adding " << failedNextHop << " to the blacklist" << endl;

    blacklist[failedNextHop] = simTime() + blacklistTimeout;    // lifetime

    if (!blacklistTimer->isScheduled())
        scheduleAt(simTime() + blacklistTimeout, blacklistTimer);
}

const Ptr<SNOOPHB> SatelliteRouting::createHelloMessage()
{
    // called a Hello message, with the RREP
    // message fields set as follows:
    //
    //    Destination IP Address         The node's IP address.
    //
    //    Destination Sequence Number    The node's latest sequence number.
    //
    //    Hop Count                      0
    //
    //    Lifetime                       ALLOWED_HELLO_LOSS *HELLO_INTERVAL

    auto helloMessage = makeShared<SNOOPHB>(); // TODO: "AODV-HelloMsg");
    helloMessage->setPacketType(usingIpv6 ? SNP_IPv6 : SNP);
    helloMessage->setChunkLength(usingIpv6 ? B(44) : B(20));

    helloMessage->setDestAddr(getSelfIPAddress());
    helloMessage->setDestSeqNum(sequenceNum);
    helloMessage->setHopCount(0);
//    helloMessage->setLifeTime(allowedHelloLoss * helloInterval);

    return helloMessage;
}

INetfilter::IHook::Result SatelliteRouting::ensureRouteForDatagram(Packet *datagram)
{
    const auto& networkHeader = getNetworkProtocolHeader(datagram);
    const L3Address& destAddr = networkHeader->getDestinationAddress();
    const L3Address& sourceAddr = networkHeader->getSourceAddress();

    if (destAddr.isBroadcast() || routingTable->isLocalAddress(destAddr) || destAddr.isMulticast())
        return ACCEPT;
    else {
        EV_INFO << "Finding route for source " << sourceAddr << " with destination " << destAddr << endl;
        IRoute *route = routingTable->findBestMatchingRoute(destAddr);
        HeartBeatRouteData *routeData = route ? dynamic_cast<HeartBeatRouteData *>(route->getProtocolData()) : nullptr;
        bool isActive = routeData && routeData->isActive();
        if (isActive && !route->getNextHopAsGeneric().isUnspecified()) {
            EV_INFO << "Active route found: " << route << endl;

            // Each time a route is used to forward a data packet, its Active Route
            // Lifetime field of the source, destination and the next hop on the
            // path to the destination is updated to be no less than the current
            // time plus ACTIVE_ROUTE_TIMEOUT.

            updateValidRouteLifeTime(destAddr, simTime() + activeRouteTimeout);
            updateValidRouteLifeTime(route->getNextHopAsGeneric(), simTime() + activeRouteTimeout);

            return ACCEPT;
        }
        else {
            bool isInactive = routeData && !routeData->isActive();
            // A node disseminates a RREQ when it determines that it needs a route
            // to a destination and does not have one available.  This can happen if
            // the destination is previously unknown to the node, or if a previously
            // valid route to the destination expires or is marked as invalid.

            EV_INFO << (isInactive ? "Inactive" : "Missing") << " route for destination " << destAddr << endl;

            delayDatagram(datagram);

            if (!hasOngoingRouteDiscovery(destAddr)) {
                // When a new route to the same destination is required at a later time
                // (e.g., upon route loss), the TTL in the RREQ IP header is initially
                // set to the Hop Count plus TTL_INCREMENT.
                if (isInactive)
                    startRouteDiscovery(destAddr, route->getMetric() + ttlIncrement);
                else
                    startRouteDiscovery(destAddr);
            }
            else
                EV_DETAIL << "Route discovery is in progress, originator " << getSelfIPAddress() << " target " << destAddr << endl;

            return QUEUE;
        }
    }
}

void SatelliteRouting::expungeRoutes()
{
    for (int i = 0; i < routingTable->getNumRoutes(); i++) {
        IRoute *route = routingTable->getRoute(i);
        if (route->getSource() == this) {
            HeartBeatRouteData *routeData = check_and_cast<HeartBeatRouteData *>(route->getProtocolData());
            ASSERT(routeData != nullptr);
            if (routeData->getLifeTime() <= simTime()) {
                if (routeData->isActive()) {
                    EV_DETAIL << "Route to " << route->getDestinationAsGeneric() << " expired and set to inactive. It will be deleted after DELETE_PERIOD time" << endl;
                    // An expired routing table entry SHOULD NOT be expunged before
                    // (current_time + DELETE_PERIOD) (see section 6.11).  Otherwise, the
                    // soft state corresponding to the route (e.g., last known hop count)
                    // will be lost.
                    routeData->setIsActive(false);
                    routeData->setLifeTime(simTime() + deletePeriod);
                }
                else {
                    // Any routing table entry waiting for a RREP SHOULD NOT be expunged
                    // before (current_time + 2 * NET_TRAVERSAL_TIME).
                    if (hasOngoingRouteDiscovery(route->getDestinationAsGeneric())) {
                        EV_DETAIL << "Route to " << route->getDestinationAsGeneric() << " expired and is inactive, but we are waiting for a RREP to this destination, so we extend its lifetime with 2 * NET_TRAVERSAL_TIME" << endl;
                        routeData->setLifeTime(simTime() + 2 * netTraversalTime);
                    }
                    else {
                        EV_DETAIL << "Route to " << route->getDestinationAsGeneric() << " expired and is inactive and we are not expecting any RREP to this destination, so we delete this route" << endl;
                        routingTable->deleteRoute(route);
                    }
                }
            }
        }
    }
    scheduleExpungeRoutes();
}

void SatelliteRouting::scheduleExpungeRoutes()
{
    simtime_t nextExpungeTime = SimTime::getMaxTime();
    for (int i = 0; i < routingTable->getNumRoutes(); i++) {
        IRoute *route = routingTable->getRoute(i);

        if (route->getSource() == this) {
            HeartBeatRouteData *routeData = check_and_cast<HeartBeatRouteData *>(route->getProtocolData());
            ASSERT(routeData != nullptr);

            if (routeData->getLifeTime() < nextExpungeTime)
                nextExpungeTime = routeData->getLifeTime();
        }
    }
    if (nextExpungeTime == SimTime::getMaxTime()) {
        if (expungeTimer->isScheduled())
            cancelEvent(expungeTimer);
    }
    else {
        if (!expungeTimer->isScheduled())
            scheduleAt(nextExpungeTime, expungeTimer);
        else {
            if (expungeTimer->getArrivalTime() != nextExpungeTime) {
                cancelEvent(expungeTimer);
                scheduleAt(nextExpungeTime, expungeTimer);
            }
        }
    }
}

void SatelliteRouting::startRouteDiscovery(const L3Address& target, unsigned timeToLive)
{
    EV_INFO << "Starting route discovery with originator " << getSelfIPAddress() << " and destination " << target << endl;
    ASSERT(!hasOngoingRouteDiscovery(target));
}

void SatelliteRouting::sendSnooping(const Ptr<SNOOPHB>& snoop, unsigned int timeToLive){
    EV << "sending snooping message" << endl;
//    sendHeartBeatpkg(snoop,addressType->getBroadcastAddress(),timeToLive,*jitterPar);
    sendHeartBeatpkg(snoop,addressType->getBroadcastAddress(),timeToLive,0);
}

void SatelliteRouting::sendResp(const Ptr<RESPHB>& resp, const L3Address& destAddr, unsigned int timeToLive){
    EV << "sending response message" << endl;
    EV << "Destination: " << resp->getDestAddr() << endl;
    EV << "Source: " << resp->getOriginatorAddr() << endl;
//    sendHeartBeatpkg(resp,destAddr,timeToLive,currBackoff);
    sendHeartBeatpkg(resp,destAddr,timeToLive,0);
}

void SatelliteRouting::sendCainMsg(const Ptr<CAINMSG>& cainmsg, unsigned int timeToLive, double delay){
    EV << "sending CAIN ";
    int type = cainmsg->getPacketType();
    switch(type){
    case CAINREQ:
    case CAINREQ_IPv6:
        EV << "REQ ";
        break;
    case CAINRESP:
    case CAINRESP_IPv6:
        EV << "RESP ";
        break;
    case CAINFWD:
    case CAINFWD_IPv6:
        EV << "FWD ";
        break;
    case NEWFWD:
    case NEWFWD_IPv6:
        EV << "NEW FDW ";
        break;
    case CAINHOP:
    case CAINHOP_IPv6:
        EV << "HOP ";
        break;
    case CAINERR:
    case CAINERR_IPv6:
        EV << "ERR ";
        break;
    case CAINACK:
    case CAINACK_IPv6:
        EV << "ACK ";
        break;
    case LAR:
    case LAR_IPv6:
        EV << "LAR ";
        break;
    case SPR:
    case SPR_IPv6:
        EV << "SPRAY ";
        break;
    case BRAP:
    case BRAP_IPv6:
        EV << "BRAP ";
        break;
    }
    EV << "message." << endl;

//    if(!cainmsg->getDestAddr().isUnspecified())
        sendHeartBeatpkg(cainmsg,addressType->getBroadcastAddress(),timeToLive,delay);
}

void SatelliteRouting::sendHeartBeatpkg(const Ptr<HeartBeat>& hbpacket, const L3Address& destAddr, unsigned int timeToLive, double delay){
    ASSERT(timeToLive != 0);
    EV << "sending hb message" << endl;

    const char *className = hbpacket->getClassName();
    Packet *packet = new Packet(!strncmp("inet::", className, 6) ? className + 6 : className);
    packet->insertAtBack(hbpacket);

    int interfaceId = CHK(interfaceTable->findInterfaceByName(par("interface")))->getInterfaceId(); // TODO: Implement: support for multiple interfaces
    packet->addTag<InterfaceReq>()->setInterfaceId(interfaceId);
    packet->addTag<HopLimitReq>()->setHopLimit(timeToLive);
    packet->addTag<L3AddressReq>()->setDestAddress(destAddr);
    packet->addTag<L4PortReq>()->setDestPort(WirelessRoutingUDPPort);

    if (destAddr.isBroadcast())
        lastBroadcastTime = simTime();

    if (delay == 0)
        socket.send(packet);
    else {
        if (simTime() > rebootTime + deletePeriod) {
            auto *timer = new PacketHolderMessage("aodv-send-jitter", KIND_DELAYEDSEND);
            timer->setOwnedPacket(packet);
            scheduleAt(simTime()+delay, timer);
        }
    }
}

const Ptr<SNOOPHB> SatelliteRouting::createSnoopMsg(){
    auto snoopPkg = makeShared<SNOOPHB>();
    Coord coord;
    int batteryPercent = 100;
    //if(strcmp(this->getParentModule()->getName(),"drone")){//not a drone
        coord = Coord(baseMobility->getCurrentPosition());
        batteryPercent = (int)round(unit(energyStorage->getResidualEnergyCapacity()/energyStorage->getNominalEnergyCapacity()).get() * 100);
    //}else
        //coord = Coord(droneMobility->getCurrentPosition());
    //Coord senderCoord = Coord(baseMobility->getCurrentPosition());
    Coord senderCoord = coord;
    snoopPkg->setPacketType(usingIpv6 ? SNP_IPv6 : SNP);
    snoopPkg->setChunkLength(usingIpv6 ? B(48) : B(24));
    snoopPkg->setHopCount(0);
    snoopPkg->setOriginatorAddr(getSelfIPAddress());
    snoopPkg->setDestAddr(addressType->getBroadcastAddress());
    snoopPkg->setMsgCoord(senderCoord);
    snoopPkg->setBatteryPercent(batteryPercent);
    snoopPkg->setTwoHop(false);
    snoopPkg->setNodeName(this->getParentModule()->getName());
    return snoopPkg;
}

bool SatelliteRouting::hasOngoingRouteDiscovery(const L3Address& target)
{
    return waitForRREPTimers.find(target) != waitForRREPTimers.end();
}

INetfilter::IHook::Result SatelliteRouting::datagramForwardHook(Packet *datagram)
{
    // TODO: Implement: Actions After Reboot
    // If the node receives a data packet for some other destination, it SHOULD
    // broadcast a RERR as described in subsection 6.11 and MUST reset the waiting
    // timer to expire after current time plus DELETE_PERIOD.

    Enter_Method("datagramForwardHook");
    const auto& networkHeader = getNetworkProtocolHeader(datagram);
    const L3Address& destAddr = networkHeader->getDestinationAddress();
    const L3Address& sourceAddr = networkHeader->getSourceAddress();
    IRoute *ipSource = routingTable->findBestMatchingRoute(sourceAddr);

    if (destAddr.isBroadcast() || routingTable->isLocalAddress(destAddr) || destAddr.isMulticast()) {
        if (routingTable->isLocalAddress(destAddr) && ipSource && ipSource->getSource() == this)
            updateValidRouteLifeTime(ipSource->getNextHopAsGeneric(), simTime() + activeRouteTimeout);

        return ACCEPT;
    }

    // TODO: IMPLEMENT: check if the datagram is a data packet or we take control packets as data packets

    IRoute *routeDest = routingTable->findBestMatchingRoute(destAddr);
    HeartBeatRouteData *routeDestData = routeDest ? dynamic_cast<HeartBeatRouteData *>(routeDest->getProtocolData()) : nullptr;

    // Each time a route is used to forward a data packet, its Active Route
    // Lifetime field of the source, destination and the next hop on the
    // path to the destination is updated to be no less than the current
    // time plus ACTIVE_ROUTE_TIMEOUT

    updateValidRouteLifeTime(sourceAddr, simTime() + activeRouteTimeout);
    updateValidRouteLifeTime(destAddr, simTime() + activeRouteTimeout);

    if (routeDest && routeDest->getSource() == this)
        updateValidRouteLifeTime(routeDest->getNextHopAsGeneric(), simTime() + activeRouteTimeout);

    // Since the route between each originator and destination pair is expected
    // to be symmetric, the Active Route Lifetime for the previous hop, along the
    // reverse path back to the IP source, is also updated to be no less than the
    // current time plus ACTIVE_ROUTE_TIMEOUT.

    if (ipSource && ipSource->getSource() == this)
        updateValidRouteLifeTime(ipSource->getNextHopAsGeneric(), simTime() + activeRouteTimeout);

    EV_INFO << "We can't forward datagram because we have no active route for " << destAddr << endl;
    if (routeDest && routeDestData && !routeDestData->isActive()) {    // exists but is not active
        // A node initiates processing for a RERR message in three situations:
        // (ii)      if it gets a data packet destined to a node for which it
        //           does not have an active route and is not repairing (if
        //           using local repair)

        // TODO: check if it is not repairing (if using local repair)

        // 1. The destination sequence number of this routing entry, if it
        // exists and is valid, is incremented for cases (i) and (ii) above,
        // and copied from the incoming RERR in case (iii) above.

        if (routeDestData->hasValidDestNum())
            routeDestData->setDestSeqNum(routeDestData->getDestSeqNum() + 1);

        // 2. The entry is invalidated by marking the route entry as invalid <- it is invalid

        // 3. The Lifetime field is updated to current time plus DELETE_PERIOD.
        //    Before this time, the entry SHOULD NOT be deleted.
        routeDestData->setLifeTime(simTime() + deletePeriod);

        sendRERRWhenNoRouteToForward(destAddr);
    }
    else if (!routeDest || routeDest->getSource() != this) // doesn't exist at all
        sendRERRWhenNoRouteToForward(destAddr);

    return ACCEPT;
}

void SatelliteRouting::sendRERRWhenNoRouteToForward(const L3Address& unreachableAddr)
{
    if (rerrCount >= rerrRatelimit) {
        EV_WARN << "A node should not generate more than RERR_RATELIMIT RERR messages per second. Canceling sending RERR" << endl;
        return;
    }
    std::vector<UnreachableNode> unreachableNodes;
    UnreachableNode node;
    node.addr = unreachableAddr;

    IRoute *unreachableRoute = routingTable->findBestMatchingRoute(unreachableAddr);
    HeartBeatRouteData *unreachableRouteData = unreachableRoute ? dynamic_cast<HeartBeatRouteData *>(unreachableRoute->getProtocolData()) : nullptr;

    if (unreachableRouteData && unreachableRouteData->hasValidDestNum())
        node.seqNum = unreachableRouteData->getDestSeqNum();
    else
        node.seqNum = 0;

    unreachableNodes.push_back(node);
    auto rerr = createRERR(unreachableNodes);

    rerrCount++;
    EV_INFO << "Broadcasting Route Error message with TTL=1" << endl;
//    sendHeartBeatpkg(rerr, addressType->getBroadcastAddress(), 1, *jitterPar);    // TODO: unicast if there exists a route to the source
    sendHeartBeatpkg(rerr, addressType->getBroadcastAddress(), 1,0);
}

void SatelliteRouting::handleLinkBreakSendRERR(const L3Address& unreachableAddr)
{
    // For case (i), the node first makes a list of unreachable destinations
    // consisting of the unreachable neighbor and any additional
    // destinations (or subnets, see section 7) in the local routing table
    // that use the unreachable neighbor as the next hop.

    // Just before transmitting the RERR, certain updates are made on the
    // routing table that may affect the destination sequence numbers for
    // the unreachable destinations.  For each one of these destinations,
    // the corresponding routing table entry is updated as follows:
    //
    // 1. The destination sequence number of this routing entry, if it
    //    exists and is valid, is incremented for cases (i) and (ii) above,
    //    and copied from the incoming RERR in case (iii) above.
    //
    // 2. The entry is invalidated by marking the route entry as invalid
    //
    // 3. The Lifetime field is updated to current time plus DELETE_PERIOD.
    //    Before this time, the entry SHOULD NOT be deleted.

    IRoute *unreachableRoute = routingTable->findBestMatchingRoute(unreachableAddr);

    if (!unreachableRoute || unreachableRoute->getSource() != this)
        return;

    std::vector<UnreachableNode> unreachableNodes;
    HeartBeatRouteData *unreachableRouteData = check_and_cast<HeartBeatRouteData *>(unreachableRoute->getProtocolData());

    if (unreachableRouteData->isActive()) {
        UnreachableNode node;
        node.addr = unreachableAddr;
        node.seqNum = unreachableRouteData->getDestSeqNum();
        unreachableNodes.push_back(node);
    }

    // For case (i), the node first makes a list of unreachable destinations
    // consisting of the unreachable neighbor and any additional destinations
    // (or subnets, see section 7) in the local routing table that use the
    // unreachable neighbor as the next hop.

    for (int i = 0; i < routingTable->getNumRoutes(); i++) {
        IRoute *route = routingTable->getRoute(i);

        HeartBeatRouteData *routeData = dynamic_cast<HeartBeatRouteData *>(route->getProtocolData());
        if (routeData && routeData->isActive() && route->getNextHopAsGeneric() == unreachableAddr) {
            if (routeData->hasValidDestNum())
                routeData->setDestSeqNum(routeData->getDestSeqNum() + 1);

            EV_DETAIL << "Marking route to " << route->getDestinationAsGeneric() << " as inactive" << endl;

            routeData->setIsActive(false);
            routeData->setLifeTime(simTime() + deletePeriod);
            scheduleExpungeRoutes();

            UnreachableNode node;
            node.addr = route->getDestinationAsGeneric();
            node.seqNum = routeData->getDestSeqNum();
            unreachableNodes.push_back(node);
        }
    }

    // The neighboring node(s) that should receive the RERR are all those
    // that belong to a precursor list of at least one of the unreachable
    // destination(s) in the newly created RERR.  In case there is only one
    // unique neighbor that needs to receive the RERR, the RERR SHOULD be
    // unicast toward that neighbor.  Otherwise the RERR is typically sent
    // to the local broadcast address (Destination IP == 255.255.255.255,
    // TTL == 1) with the unreachable destinations, and their corresponding
    // destination sequence numbers, included in the packet.

    if (rerrCount >= rerrRatelimit) {
        EV_WARN << "A node should not generate more than RERR_RATELIMIT RERR messages per second. Canceling sending RERR" << endl;
        return;
    }

    if (unreachableNodes.empty())
        return;

    auto rerr = createRERR(unreachableNodes);
    rerrCount++;

    // broadcast
    EV_INFO << "Broadcasting Route Error message with TTL=1" << endl;
//    sendHeartBeatpkg(rerr, addressType->getBroadcastAddress(), 1, *jitterPar);
    sendHeartBeatpkg(rerr, addressType->getBroadcastAddress(), 1, 0);
}

const Ptr<Rerr> SatelliteRouting::createRERR(const std::vector<UnreachableNode>& unreachableNodes)
{
    auto rerr = makeShared<Rerr>(); // TODO: "AODV-RERR");
    rerr->setPacketType(usingIpv6 ? def : def);

    unsigned int destCount = unreachableNodes.size();
    rerr->setUnreachableNodesArraySize(destCount);

    for (unsigned int i = 0; i < destCount; i++) {
        UnreachableNode node;
        node.addr = unreachableNodes[i].addr;
        node.seqNum = unreachableNodes[i].seqNum;
        rerr->setUnreachableNodes(i, node);
    }

    rerr->setChunkLength(B(4 + destCount * (usingIpv6 ? (4 + 16) : (4 + 4))));

    return rerr;
}

bool SatelliteRouting::updateValidRouteLifeTime(const L3Address& destAddr, simtime_t lifetime)
{
    IRoute *route = routingTable->findBestMatchingRoute(destAddr);
    if (route && route->getSource() == this) {
        HeartBeatRouteData *routeData = check_and_cast<HeartBeatRouteData *>(route->getProtocolData());
        if (routeData->isActive()) {
            simtime_t newLifeTime = std::max(routeData->getLifeTime(), lifetime);
            EV_DETAIL << "Updating " << route << " lifetime to " << newLifeTime << endl;
            routeData->setLifeTime(newLifeTime);
            return true;
        }
    }
    return false;
}

void SatelliteRouting::processPacket(Packet *packet)
{
    L3Address sourceAddr = packet->getTag<L3AddressInd>()->getSrcAddress();
    // KLUDGE: I added this -1 after TTL decrement has been moved in Ipv4
    unsigned int arrivalPacketTTL = packet->getTag<HopLimitInd>()->getHopLimit() - 1;
    const auto& hbPacket = packet->popAtFront<HeartBeat>();
    //TODO aodvPacket->copyTags(*udpPacket);
//
    auto packetType = hbPacket->getPacketType();

    switch (packetType) {
        case SNP:
        case SNP_IPv6:
            EV << "Snooping message arrived" << endl;
            handleSnooping(CHK(dynamicPtrCast<SNOOPHB>(hbPacket->dupShared())), sourceAddr);
            delete packet;
            return;
        case CAINFWD:
        case CAINFWD_IPv6:
            EV << "CAIN FWD message arrived" << endl;
            handleCainFWD(CHK(dynamicPtrCast<CAINMSG>(hbPacket->dupShared())));
            delete packet;
            return;
        case ANTN:
        case ANTN_IPv6:
            EV << "Antenna message arriving" << endl;
            handleAntennaMsg(CHK(dynamicPtrCast<ANTENNA>(hbPacket->dupShared())));
            delete packet;
            return;
        case DRONE:
        case DRONE_IPv6:
            EV << "Drone message arriving" << endl;
            handleDroneMsg(CHK(dynamicPtrCast<DRONEMSG>(hbPacket->dupShared())));
            delete packet;
            return;
        default:
            delete packet;
            return;
    }
}

void SatelliteRouting::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void SatelliteRouting::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void SatelliteRouting::handleStartOperation(LifecycleOperation *operation)
{


    socket.setOutputGate(gate("socketOut"));
    socket.setCallback(this);
    socket.bind(L3Address(), WirelessRoutingUDPPort);
    socket.setBroadcast(true);



    rebootTime = simTime();


    // RFC 5148:
    // Jitter SHOULD be applied by reducing this delay by a random amount, so that
    // the delay between consecutive transmissions of messages of the same type is
    // equal to (MESSAGE_INTERVAL - jitter), where jitter is the random value.
    if (useHelloMessages)
        scheduleAt(simTime() + helloInterval - *periodicJitter, helloMsgTimer);
    scheduleAt(simTime() + 2, counterTimer);

//    scheduleAt(simTime()+0.7, cainFwdTimer);handleCainFWD
}

void SatelliteRouting::handleCainFWD(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
            ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "CAIN destination: " << cainmsg->getCainDestAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;

    calculate_q_matrix();
    std::string netType = getModuleByPath("simpleNetwork")->par("networkType");
    if(netType == "SC" || netType == "EECRM"){
        updateBestHop(cainmsg->getSourceAddr());
    }else if(netType == "LAR"){
        updateLarBestHop(cainmsg->getSourceAddr(),cainmsg->getSenderCoord());
    }

    calcDelayMean(cainmsg->getTimeInit());

    double back = 0;

    oracle_->insertRecNode(getSelfIPAddress());

    int hops=cainmsg->getHops();
    cainmsg->setHops(++hops);

    if(getSelfIPAddress() == chAddr && cainmsg->getCainDestAddr() == getSelfIPAddress()){

        EV << "Antenna address: " << antennaAddr << endl;
        if(!antennaAddr.isUnspecified()){
            cainmsg->setSourceAddr(getSelfIPAddress());
            cainmsg->setDestAddr(addressType->getBroadcastAddress());
            cainmsg->setCainDestAddr(antennaAddr);
            int hopcount=cainmsg->getHopCount();
            cainmsg->setHopCount(--hopcount);
            EV << "antenna address: " << antennaAddr << endl;
            sendCainMsg(cainmsg,1,back);
        }

        Coord senderCoord = cainmsg->getSenderCoord();
        dist = baseMobility->getCurrentPosition().distance(senderCoord);
        emit(distSignal,dist);
        msgHops=cainmsg->getHops();
        emit(hopCountSignal,msgHops);
        EV << "Reached a full CH." << endl;
        cainMsg++;
        emit(cainMsgSignal,cainMsg);

        recCainFwdMsg++;
        emit(recCainFwdMsgSignal,recCainFwdMsg);


        simtime_t arrivalTime = simTime();
        delay=arrivalTime-cainmsg->getTimeInit();
        EV << "msg delay: " << delay << endl;
        emit(timeSignal,delay);

        if(!droneAddr.isUnspecified()){
            cainmsg->setCainDestAddr(droneAddr);
            cainmsg->setDestAddr(droneAddr);
            cainmsg->setSourceAddr(getSelfIPAddress());
            sendCainMsg(cainmsg,1,0);
        }

        if(rl_type == "Hop1" || rl_type == "Hop2" || rl_type == "Hop3"){
            cainmsg->setPacketType(usingIpv6 ? CAINREPLY_IPv6 : CAINREPLY);
            cainmsg->setHops(hops);
            cainmsg->setHopCount(hops);
            cainmsg->setCainDestAddr(addressType->getBroadcastAddress());
            cainmsg->setDestAddr(addressType->getBroadcastAddress());
            cainmsg->setSourceAddr(getSelfIPAddress());
            sendCainMsg(cainmsg, hops, 0);
        }
    }else{
        if(cainmsg->getHopCount()>0){
            cainmsg->setSourceAddr(getSelfIPAddress());
            cainmsg->setDestAddr(addressType->getBroadcastAddress());
            cainmsg->setCainDestAddr(chAddr);
            int hopcount=cainmsg->getHopCount();
            cainmsg->setHopCount(--hopcount);
            sentCainFwdMsg++;
            emit(sentCainFwdMsgSignal,sentCainFwdMsg);
            sendCainMsg(cainmsg, 2,back);
        }
    }
}


void SatelliteRouting::handleCainREQ(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;

    calcDelayMean(cainmsg->getTimeInit());

    if(recFwdMessages->find(cainmsg->getOriginatorAddr()) == recFwdMessages->end() &&
            cainmsg->getCainDestAddr() == getSelfIPAddress()){
        recFwdMessages->operator [](cainmsg->getOriginatorAddr())=cainmsg->getMsgId();

        recCainReqMsg++;
        emit(recCainReqMsgSignal,recCainReqMsg);

        int hops=cainmsg->getHops();
        cainmsg->setHops(hops);
        std::string netType = getModuleByPath("simpleNetwork")->par("networkType");
        if(netType == "SC" || netType == "EECRM"){
           updateBestHop(cainmsg->getSourceAddr());
        }else if(netType == "LAR"){
            updateLarBestHop(cainmsg->getSourceAddr(),cainmsg->getSenderCoord());
        }else{
            if(!chAddr.isUnspecified()&&
                    cainmsg->getHopCount()>0){
                //node is connected to a CH: forward the message to it
                cainmsg->setPacketType(usingIpv6 ? CAINFWD_IPv6 : CAINFWD);
                cainmsg->setSourceAddr(getSelfIPAddress());
                cainmsg->setCentrality(respMap->size());
                cainmsg->setDestAddr(chAddr);
                cainmsg->setCainDestAddr(chAddr);

                Coord sendercoord = cainmsg->getSenderCoord();
                double dist = baseMobility->getCurrentPosition().distance(sendercoord);
                dist+=cainmsg->getDistance();
                cainmsg->setDistance(dist);

                int hopcount=cainmsg->getHopCount();
                cainmsg->setHopCount(--hopcount);
                double back = 0;//backoffTimer();
                sentCainFwdMsg++;
                emit(sentCainFwdMsgSignal,sentCainFwdMsg);
                sendCainMsg(cainmsg, 10,back);
            }else{
                //node is not connected to a CH: send a hop message
                EV << "Creating CAIN HOP msg" << endl;
                L3Address bestHopAddr = L3Address("0.0.0.0");
                int distMapsize = distMap->size();
                int hopMapsize = hopMap->size();
                if((distMapsize > 0 || hopMapsize > 0) && getModuleByPath("simpleNetwork")->par("mlEnable")){
                    bestHopAddr = findHopRL();
                }else{
                    bestHopAddr = addressType->getBroadcastAddress();
                }

                sentCainHopMsg++;
                emit(sentCainHopMsgSignal,sentCainHopMsg);
                auto cainhopmsg = createCainHopMsg(bestHopAddr);
                hopAck->push_back(fwdSeqNum);

                Coord sendercoord = cainhopmsg->getSenderCoord();
                double dist = baseMobility->getCurrentPosition().distance(sendercoord);
                dist+=cainhopmsg->getDistance();
                cainhopmsg->setDistance(dist);
                cainhopmsg->setTimeInit(cainmsg->getTimeInit());

                EV << "best hop: " << bestHopAddr << endl;
                if(cainhopmsg->getCainDestAddr() == addressType->getBroadcastAddress()){
                    sendCainMsg(cainhopmsg, 10,0);
                }else{
                    if(getModuleByPath("simpleNetwork")->par("mlEnable")){
                        calculate_q_matrix();
                        int state = get_coverage_state(cainhopmsg->getCainDestAddr());
                        bool decision = sendMessageML(state);
                        if(decision){
                            double back = 0;
                            sendCainMsg(cainhopmsg, 10,0);
                        }
                        calculate_coverage_reward(state,decision,cainhopmsg->getCainDestAddr());
                    }else{
                        sendCainMsg(cainhopmsg, 10,0);
                    }
                }
                ostringstream stream;
                stream << "HOP-" << cainhopmsg->getSeqNum() << "-" << bestHopAddr.str();
            }
        }
    }
}

void SatelliteRouting::calcDelayMean(simtime_t msgInit){
    simtime_t timeDiff = simTime() - msgInit;
    meanDelay*=qtdMsg;
    meanDelay+=timeDiff;
    meanDelay/=++qtdMsg;

}

void SatelliteRouting::handleAntennaMsg(const Ptr<ANTENNA>& antennaMsg){
    EV << "antenna message arriving with address: " << antennaMsg->getSourceAddr() << endl;
    if(strcmp(this->getParentModule()->getName(),"antenna")){
        //it is a regular node: the strcmp returns 1
        antennaAddr = antennaMsg->getSourceAddr();
        recAntennaMsg++;
        emit(recAntennaMsgSignal,recAntennaMsg);
    }
}

void SatelliteRouting::handleDroneMsg(const Ptr<DRONEMSG>& droneMsg){
    EV << "Drone message arriving with address: " << droneMsg->getSourceAddr() << endl;
    EV << "This addr: " << getSelfIPAddress() << endl;
    EV << "ch addr " << chAddr << endl;
        //it is a regular node: the strcmp returns 1
    Coord thisCoord = Coord(baseMobility->getCurrentPosition());
    Coord senderCoord = droneMsg->getSenderCoord();
    double dist = thisCoord.distance(senderCoord);
    droneAddr = droneMsg->getSourceAddr();
    droneDistMap->operator [](droneAddr) = dist;

}

void SatelliteRouting::handleWeightMsg(const Ptr<FLWEIGHT>& weightMsg){
    EV << "weight message arriving with address: " << weightMsg->getSourceAddr() << endl;

    recWeightMsg++;
    emit(recWeightMsgSignal,recWeightMsg);

    std::vector<float> *weightVector = new std::vector<float>();
    weightVector->push_back(weightMsg->getW11());
    weightVector->push_back(weightMsg->getW12());
    weightVector->push_back(weightMsg->getW13());
    weightVector->push_back(weightMsg->getW21());
    weightVector->push_back(weightMsg->getW22());
    weightVector->push_back(weightMsg->getW23());
    weightVector->push_back(weightMsg->getW31());
    weightVector->push_back(weightMsg->getW32());
    weightVector->push_back(weightMsg->getW33());
    weightVector->push_back(weightMsg->getWo1());
    weightVector->push_back(weightMsg->getWo2());
    weightVector->push_back(weightMsg->getWo3());

    if(this->chAddr == getSelfIPAddress()){
        this->network->setNeuronTotalWeights(weightVector);
        this->weightMsgCounter++;
        this->network->updateWeights(this->weightMsgCounter,this->chAddr == getSelfIPAddress());
    }else if(weightMsg->getSourceAddr() == chAddr){
        this->network->setNeuronTotalWeights(weightVector);
        this->network->updateWeights(this->weightMsgCounter,this->chAddr == getSelfIPAddress());
    }

}

void SatelliteRouting::handleCainRESP(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;
    std::pair<L3Address,int> msgSource = std::pair<L3Address,int>(cainmsg->getSourceAddr(),
            cainmsg->getBatteryPercent());


//    if(recFwdMessages->find(cainmsg->getOriginatorAddr()) == recFwdMessages->end()){
//        recFwdMessages->operator [](cainmsg->getOriginatorAddr())=cainmsg->getMsgId();

    calcDelayMean(cainmsg->getTimeInit());
        recCainRespMsg++;
        emit(recCainRespMsgSignal,recCainRespMsg);
        respMap->operator [](msgSource) = pair<L3Address,int>(cainmsg->getChAddr(),cainmsg->getChBattery());
        centralityMap->operator [](cainmsg->getSourceAddr()) = cainmsg->getCentrality();
//    }
}

void SatelliteRouting::handleCainHOP(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;

    calcDelayMean(cainmsg->getTimeInit());
    if(strcmp(this->getParentModule()->getName(),"antenna")){
        recFwdMessages->operator [](cainmsg->getOriginatorAddr())=cainmsg->getMsgId();

        double back = 0;
        recCainHopMsg++;
        emit(recCainHopMsgSignal,recCainHopMsg);
        int hop=cainmsg->getHops();
        cainmsg->setHops(++hop);
        int hopcount=cainmsg->getHopCount();
        cainmsg->setHopCount(--hopcount);
        if(cainmsg->getOriginatorAddr() != getSelfIPAddress() && cainmsg->getHopCount() > 0){
            if(!chAddr.isUnspecified()){
                    sentCainFwdMsg++;
                    emit(sentCainFwdMsgSignal,sentCainFwdMsg);
                        auto cainfwdmsg = createCainFwdMsg(chAddr);
                        fwdAck->push_back(fwdSeqNum);
                        cainfwdmsg->setTimeInit(cainmsg->getTimeInit());
                        sendCainMsg(cainfwdmsg, 1,back);
                        ostringstream stream;
                        stream << "FWD-" << cainfwdmsg->getSeqNum();
            }else{
                sendCainMsg(cainmsg, cainmsg->getHopCount(), 0);
            }
        }
    }
}

void SatelliteRouting::handleCainERR(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
            ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;

    double back = 0;//backoffTimer();
    recCainErrMsg++;
    emit(recCainErrMsgSignal,recCainErrMsg);
    if(cainmsg->getDestAddr() != cainmsg->getOriginatorAddr()){
        EV << "Error message not arrived at originator" << endl;
        cainmsg->setDestAddr(cainmsg->getOriginatorAddr());
        cainmsg->setSourceAddr(getSelfIPAddress());
        sendCainMsg(cainmsg, 1,back);
    }else{
        EV << "Error message arrived at originator" << endl;
    }
}


void SatelliteRouting::handleCainACK(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;
    EV << "Current backoff index: " << currBackoff << endl;
    EV << "Message being acked type: ";
    currBackoff = 0;
    vector<int>::iterator it;
    auto packetType = cainmsg->getAckType();
    switch(packetType){
        case CAINFWD:
        case CAINFWD_IPv6:
            it = fwdAck->begin();
            for(;it != fwdAck->end();it++){
                if(*it == cainmsg->getAckSeqNum()){
                    fwdAck->erase(it);
                    return;
                }
            }
            break;
        case CAINREQ:
        case CAINREQ_IPv6:
            it = reqAck->begin();
            for(;it != reqAck->end();it++){
                if(*it == cainmsg->getAckSeqNum()){
                    reqAck->erase(it);
                    return;
                }
            }
            break;
        case CAINHOP:
        case CAINHOP_IPv6:
            it = hopAck->begin();
            for(;it != hopAck->end();it++){
                if(*it == cainmsg->getAckSeqNum()){
                    hopAck->erase(it);
                    return;
                }
            }
            break;
        default:
            return;
    }
}

void SatelliteRouting::handleFwdTimer(){
    if(strcmp(this->getParentModule()->getName(),"antenna")){
        map<pair<L3Address,int>,pair<L3Address,int>>::iterator respIt = respMap->begin();
        int bestChBattery = 0;
        int bestHopBattery = 0;
        int bestNeighbBattery = 0;
        L3Address bestNeighbAddr = L3Address("0.0.0.0");
        L3Address bestHopAddr = L3Address("0.0.0.0");
        EV << "Resp map:" << endl;
        for(; respIt != respMap->end(); respIt++){
            EV << "Dev addr: " << respIt->first.first << "| Dev battery: " << respIt->first.second <<
                    "| CH addr: " << respIt->second.first << "| Battery: " << respIt->second.second << endl;

            if(respIt->second.first != L3Address("0.0.0.0") && respIt->second.first == chAddr){
                //neighb is connected to the same ch
                if(respIt->second.second > bestChBattery && respIt->first.second > bestNeighbBattery){
                    map<L3Address,int>::iterator centralIt = centralityMap->begin();
                    bestNeighbAddr = respIt->first.first;
                    bestNeighbBattery = respIt->first.second;
                    bestChBattery = respIt->second.second;
                }
            }
        }
        EV << "Best addr: " << bestNeighbAddr << "| Battery: " << bestNeighbBattery << endl;
        EV << "Best hop addr: " << bestHopAddr << "| Battery: " << bestHopBattery << endl;

        if(!bestNeighbAddr.isUnspecified()){
            //there is a neighbor device connected to a CH
            EV << "Creating CAIN FWD msg" << endl;
            if(this->chAddr != getSelfIPAddress()){
                if (simTime() > rebootTime + deletePeriod || rebootTime == 0) {
                    sentCainFwdMsg++;
                    emit(sentCainFwdMsgSignal,sentCainFwdMsg);
                    auto cainfwdmsg = createCainFwdMsg(bestNeighbAddr);
                    fwdAck->push_back(fwdSeqNum);
                    sendCainMsg(cainfwdmsg, 10,0);
                    ostringstream stream;
                    stream << "FWD-" << cainfwdmsg->getSeqNum();
                }
            }
        }else{
            //there is not a neighbor device connected to a CHelse{//node not conneted to a ch
            int distMapsize = distMap->size();
            int hopMapsize = hopMap->size();
            if((distMapsize > 0 || hopMapsize > 0) && getModuleByPath("simpleNetwork")->par("mlEnable")){
                bestHopAddr = findHopRL();
            }else{
                bestHopAddr = addressType->getBroadcastAddress();
            }
            std::string netType = getModuleByPath("simpleNetwork")->par("networkType");
            if(netType == "CAIN"){
                EV << "Creating CAIN HOP msg" << endl;
                if (simTime() > rebootTime + deletePeriod || rebootTime == 0) {
                    sentCainHopMsg++;
                    emit(sentCainHopMsgSignal,sentCainHopMsg);
                    auto cainhopmsg = createCainHopMsg(bestHopAddr);
                    hopAck->push_back(fwdSeqNum);
                    EV << "best hop: " << bestHopAddr << endl;
                    if(cainhopmsg->getCainDestAddr() == addressType->getBroadcastAddress()){
                        sendCainMsg(cainhopmsg, 10,0);
                    }else{
                        if(getModuleByPath("simpleNetwork")->par("mlEnable")){
                            calculate_q_matrix();
                            int state = get_coverage_state(cainhopmsg->getCainDestAddr());
                            bool decision = sendMessageML(state);
                            if(decision){
                                double back = 0;//backoffTimer();
                                sendCainMsg(cainhopmsg, 10,0);
                            }
                            calculate_coverage_reward(state,decision,cainhopmsg->getCainDestAddr());
                        }else{
                            sendCainMsg(cainhopmsg, 10,0);
                        }
                    }
                    ostringstream stream;
                    stream << "HOP-" << cainhopmsg->getSeqNum() << "-" << bestHopAddr.str();
                }
            }
        }
    }
}

void SatelliteRouting::handleCainRREQ(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;
    if(strcmp(this->getParentModule()->getName(),"antenna")){
        double back = 0;//backoffTimer();
        updateBestHop(cainmsg->getSourceAddr());
        int hopCount=cainmsg->getHopCount();
        if(getSelfIPAddress() == chAddr){
            Coord ueCoord = cainmsg->getSenderCoord();
            Coord thisCoord = baseMobility->getCurrentPosition();
            dist = thisCoord.distance(ueCoord);
            emit(distSignal,dist);
            recCainRREQFwdMsg++;
            emit(recCainRREQFwdMsgSignal,recCainRREQFwdMsg);
        }else if(hopCount>0){
            cainmsg->setCainDestAddr(bestHopAddr->first);
            cainmsg->setHopCount(hopCount-1);
            cainmsg->setSourceAddr(getSelfIPAddress());
            sendCainMsg(cainmsg, 2,back);
        }
    }
}

void SatelliteRouting::handleCainRREP(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;
    if(strcmp(this->getParentModule()->getName(),"antenna")){
        updateBestHop(cainmsg->getSourceAddr());
        std::pair<L3Address,L3Address> routeOrigDest = std::pair<L3Address,L3Address>(cainmsg->getCainDestAddr(),
                cainmsg->getRrepSource());
        int battery;
        if(routes->count(routeOrigDest) >= 1){
            if(routes->operator [](routeOrigDest).second < cainmsg->getBatteryPercent()){
                battery = cainmsg->getBatteryPercent();
            }else
                battery =routes->operator [](routeOrigDest).second;
        }else
            battery = cainmsg->getBatteryPercent();

        std::pair<L3Address,int> routeNextBattery = std::pair<L3Address,int>(cainmsg->getSourceAddr(),battery);
        routes->operator [](routeOrigDest) = routeNextBattery;

        L3Address nextHop = revRoute->operator [](routeOrigDest);
        if(cainmsg->getCainDestAddr() == getSelfIPAddress()){
            EV << "Route response message arrived" << endl;
            auto fwdMessage = createCainRREQ();
            fwdMessage->setDestAddr(nextHop);
            fwdMessage->setCainDestAddr(cainmsg->getRrepSource());
            sendCainMsg(fwdMessage, 2,0);
        }else{
            L3Address nextHop = revRoute->operator [](routeOrigDest);
            cainmsg->setDestAddr(nextHop);
            cainmsg->setSourceAddr(getSelfIPAddress());

            sendCainMsg(cainmsg, 2,0);
        }
    }
}

void SatelliteRouting::handleSCMSG(const Ptr<CAINMSG>& cainmsg){

    if(recFwdMessages->find(cainmsg->getOriginatorAddr()) == recFwdMessages->end()){
        recFwdMessages->operator [](cainmsg->getOriginatorAddr())=cainmsg->getMsgId();

        updateBestHop(cainmsg->getSourceAddr());
        int hopCount=cainmsg->getHopCount();


        if(!antennaAddr.isUnspecified()){
            cainmsg->setSourceAddr(getSelfIPAddress());
            cainmsg->setDestAddr(addressType->getBroadcastAddress());
            cainmsg->setCainDestAddr(antennaAddr);
            int hopcount=cainmsg->getHopCount();
            cainmsg->setHopCount(--hopcount);
            EV << "antenna address: " << antennaAddr << endl;
            sendCainMsg(cainmsg,1,0);
        }else{
            int hops=cainmsg->getHops();
            cainmsg->setHops(++hops);
            if(getSelfIPAddress() == chAddr){
                msgHops=cainmsg->getHops();
                emit(hopCountSignal,msgHops);
                recCainFwdMsg++;
                emit(recCainFwdMsgSignal,recCainFwdMsg);

                simtime_t arrivalTime = simTime();
                delay=arrivalTime-cainmsg->getTimeInit();
                EV << "msg delay: " << delay << endl;
                emit(timeSignal,delay);

                Coord ueCoord = cainmsg->getSenderCoord();
                Coord thisCoord = baseMobility->getCurrentPosition();
                dist = thisCoord.distance(ueCoord);
                emit(distSignal,dist);

                if(!droneAddr.isUnspecified()){
                    cainmsg->setCainDestAddr(droneAddr);
                    cainmsg->setDestAddr(droneAddr);
                    cainmsg->setSourceAddr(getSelfIPAddress());
                    sendCainMsg(cainmsg,1,0);
                }

            }else{
                if(chAddr.isUnspecified())
                    cainmsg->setCainDestAddr(bestHopAddr->first);
                else
                    cainmsg->setCainDestAddr(chAddr/*bestHopAddr->first*/);
                //cainmsg->setHopCount(hopCount-1);
                cainmsg->setSourceAddr(getSelfIPAddress());
                sentCainFwdMsg++;
                emit(sentCainFwdMsgSignal,sentCainFwdMsg);
                sendCainMsg(cainmsg, 2,0);
            }
        }
    }
}


void SatelliteRouting::handleCainLAR(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;
    if(recFwdMessages->find(cainmsg->getOriginatorAddr()) == recFwdMessages->end()){
        recFwdMessages->operator [](cainmsg->getOriginatorAddr())=cainmsg->getMsgId();

        if(!antennaAddr.isUnspecified()){
            cainmsg->setSourceAddr(getSelfIPAddress());
            cainmsg->setDestAddr(addressType->getBroadcastAddress());
            cainmsg->setCainDestAddr(antennaAddr);
            int hopcount=cainmsg->getHopCount();
            cainmsg->setHopCount(--hopcount);
            EV << "antenna address: " << antennaAddr << endl;
            sendCainMsg(cainmsg,1,0);
        }else{
            int hops=cainmsg->getHops();
            cainmsg->setHops(++hops);
            updateLarBestHop(cainmsg->getSourceAddr(),cainmsg->getSenderCoord());
            int hopCount=cainmsg->getHopCount();
            if(getSelfIPAddress() == chAddr){
                Coord ueCoord = cainmsg->getSenderCoord();
                Coord thisCoord = baseMobility->getCurrentPosition();
                dist = thisCoord.distance(ueCoord);
                emit(distSignal,dist);
                recLarMsg++;
                emit(recLarMsgSignal,recLarMsg);
                msgHops=cainmsg->getHops();
                emit(hopCountSignal,msgHops);
                simtime_t arrivalTime = simTime();
                delay=arrivalTime-cainmsg->getTimeInit();

                emit(timeSignal,delay);
                if(!droneAddr.isUnspecified()){
                    cainmsg->setCainDestAddr(droneAddr);
                    cainmsg->setDestAddr(droneAddr);
                    cainmsg->setSourceAddr(getSelfIPAddress());
                    sendCainMsg(cainmsg,1,0);
                }
            }else if(hopCount>0 && getSelfIPAddress() == cainmsg->getCainDestAddr()){
                cainmsg->setCainDestAddr(bestLarHopAddr->first);
                cainmsg->setHopCount(hopCount-1);
                cainmsg->setSourceAddr(getSelfIPAddress());
                cainmsg->setSenderCoord(baseMobility->getCurrentPosition());
                sentLarMsg++;
                emit(sentLarMsgSignal,sentLarMsg);
                sendCainMsg(cainmsg, cainmsg->getHopCount(),0);
            }
        }
    }
}

void SatelliteRouting::handleCainSPR(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;
    if(recFwdMessages->find(cainmsg->getOriginatorAddr()) == recFwdMessages->end()){
        recFwdMessages->operator [](cainmsg->getOriginatorAddr())=cainmsg->getMsgId();

        int hopCount=cainmsg->getHopCount();

        if(!antennaAddr.isUnspecified()){
            cainmsg->setSourceAddr(getSelfIPAddress());
            cainmsg->setDestAddr(addressType->getBroadcastAddress());
            cainmsg->setCainDestAddr(antennaAddr);
            int hopcount=cainmsg->getHopCount();
            cainmsg->setHopCount(--hopcount);
            EV << "antenna address: " << antennaAddr << endl;
            sendCainMsg(cainmsg,1,0);
        }else{
            vector<L3Address>::iterator it = std::find(sprayNWaitNeighb->begin(),sprayNWaitNeighb->end(),cainmsg->getSourceAddr());
            if(it == sprayNWaitNeighb->end()){
                sprayNWaitNeighb->push_back(cainmsg->getSourceAddr());
            }
            int hopCount=cainmsg->getHopCount();
            if(getSelfIPAddress() == chAddr){
                Coord ueCoord = cainmsg->getSenderCoord();
                Coord thisCoord = baseMobility->getCurrentPosition();
                dist = thisCoord.distance(ueCoord);
                emit(distSignal,dist);
                recSprMsg++;
                emit(recSprMsgSignal,recSprMsg);


                simtime_t arrivalTime = simTime();
                delay=arrivalTime-cainmsg->getTimeInit();
                EV << "msg delay: " << delay << endl;
                emit(timeSignal,delay);
            }else if(hopCount>0 && getSelfIPAddress() == cainmsg->getCainDestAddr()){
                int qtdNeighb = cainmsg->getSprayQtdNeigh();
                cainmsg->setSprayQtdNeigh(qtdNeighb/2);
                cainmsg->setHopCount(hopCount-1);
                sendSprayMsg(cainmsg);
            }
        }
    }
}

void SatelliteRouting::handleCainBRAP(const Ptr<CAINMSG>& cainmsg){
    EV << "Destined to: " << cainmsg->getDestAddr() << ", initiated by: " << cainmsg->getOriginatorAddr() <<
                    ", sent by: " << cainmsg->getSourceAddr() << endl;
    EV << "Self ipAddr: " << getSelfIPAddress() << endl;

    if(!antennaAddr.isUnspecified()){
        cainmsg->setSourceAddr(getSelfIPAddress());
        cainmsg->setDestAddr(addressType->getBroadcastAddress());
        cainmsg->setCainDestAddr(antennaAddr);
        int hopcount=cainmsg->getHopCount();
        cainmsg->setHopCount(--hopcount);
        EV << "antenna address: " << antennaAddr << endl;
        sendCainMsg(cainmsg,1,0);
    }
}

void SatelliteRouting::handleCainReply(const Ptr<CAINMSG>& cainmsg){
    if(strcmp(this->getParentModule()->getName(),"antenna")){
        if(cainmsg->getOriginatorAddr() == getSelfIPAddress()){
            if(std::find(sentMessages->begin(), sentMessages->end(), cainmsg->getMsgId()) != sentMessages->end()){
                averageHop *= qtdMessArrived;
                qtdMessArrived++;
                averageHop += cainmsg->getHops();
                averageHop /= qtdMessArrived;
            }
            cainmsg->setPacketType(usingIpv6 ? HOPCOUNT_IPv6 : HOPCOUNT);
            cainmsg->setHopCount(1);
            cainmsg->setHops(averageHop);
            cainmsg->setOriginatorAddr(getSelfIPAddress());
            sendCainMsg(cainmsg, 1, 0);
        }else{
            int hopcount = cainmsg->getHopCount();
            cainmsg->setHopCount(--hopcount);
            sendCainMsg(cainmsg, cainmsg->getHopCount(), 0);
        }
    }
}

void SatelliteRouting::handleCainHopCount(const Ptr<CAINMSG>& cainmsg){
    hopMap->operator [](cainmsg->getOriginatorAddr())=cainmsg->getHops()+1;
}



void SatelliteRouting::updateRoutingTable(IRoute *route, const L3Address& nextHop, unsigned int hopCount, bool hasValidDestNum, unsigned int destSeqNum, bool isActive, simtime_t lifeTime)
{
    EV_DETAIL << "Updating existing route: " << route << endl;

    route->setNextHop(nextHop);
    route->setMetric(hopCount);

    HeartBeatRouteData *routingData = check_and_cast<HeartBeatRouteData *>(route->getProtocolData());
    ASSERT(routingData != nullptr);

    routingData->setLifeTime(lifeTime);
    routingData->setDestSeqNum(destSeqNum);
    routingData->setIsActive(isActive);
    routingData->setHasValidDestNum(hasValidDestNum);

    EV_DETAIL << "Route updated: " << route << endl;

    scheduleExpungeRoutes();
}

void SatelliteRouting::recLeachMsg(L3Address neighAddr, const Ptr<SNOOPHB>& snoop){
    //there is no two hop information
    int neighBattery = snoop->getBatteryPercent();
    Coord senderCoord = snoop->getMsgCoord();
    Coord devCoord = baseMobility->getCurrentPosition();
    double dist = devCoord.distance(senderCoord);
    if(std::find(this->leachNeigh->begin(),this->leachNeigh->end(),neighAddr) == this->leachNeigh->end()){
        int neighNum = leachNeigh->size();
        leachNeigh->push_back(neighAddr);
        neighBatteryMean*=neighNum;
        neighBatteryMean+=neighBattery;
        neighBatteryMean/=(neighNum+1);
        if(neighBattery > higherNeighBattery)
            higherNeighBattery = neighBattery;
        neighDistMean*=neighNum;
        neighDistMean+=dist*0.02;
        neighDistMean/=(neighNum+1);
    }
}

void SatelliteRouting::calcPheromone(L3Address neighAddr, const Ptr<CAINMSG>& cainmsg){
    if(cainmsg->getPheromone()!=0){
        EV << "This phero " << cainmsg->getPheromone() << endl;
        neighPherom->operator [](neighAddr) = cainmsg->getPheromone();
        EV << neighAddr << endl;
        EV << neighPherom->operator [](neighAddr) << endl;
        map<L3Address,double>::iterator connectedIt = neighPherom->begin();
        double sumPhero=0.0;
        if(!neighPherom->empty()){
            for(; connectedIt != neighPherom->end(); connectedIt++){
                EV << "neigh phero " << neighPherom->operator [](connectedIt->first) << endl;
                sumPhero+=neighPherom->operator [](connectedIt->first);
            }
            EV << "sumPhero " << sumPhero << endl;
            probPhero=this->phero/(sumPhero);
            perhomoneS=this->phero;
            emit(pheromoneSignal, perhomoneS);
        }
    }
}

/*void SatelliteRouting::recLeachRespMsg(const Ptr<RESPHB>& respMsg){
    //when the message has the two hop information
    int neighBattery = respMsg->getBatteryPercent();
    Coord senderCoord = respMsg->getSenderCoord();
    Coord devCoord = baseMobility->getCurrentPosition();
    double dist = devCoord.distance(senderCoord);
    L3Address neighAddr = respMsg->getSourceAddr();
    if(std::find(this->leachNeigh->begin(),this->leachNeigh->end(),neighAddr) == this->leachNeigh->end()){
        int neighNum = leachNeigh->size();
        leachNeigh->push_back(neighAddr);
        neighBatteryMean*=neighNum;
        neighBatteryMean+=neighBattery;
        neighBatteryMean/=(neighNum+1);
        if(neighBattery > higherNeighBattery)
            higherNeighBattery = neighBattery;
        neighDistMean*=neighNum;
        neighDistMean+=dist*0.02;
        neighDistMean/=(neighNum+1);
        phero = getDevBatteryPower()/neighDistMean;
    }
}*/

void SatelliteRouting::chDecision(){
    //reset CH address for the next round
    //this->chAddr = addressType->getUnspecifiedAddress();
    if(leachNeigh->size() != 0){
        double leachCalc = (getDevBatteryPower()/neighBatteryMean)*chNum;
        double energyFactor = getDevBatteryPower()/higherNeighBattery;
        double leachFactor = energyFactor/neighDistMean;
        leachCalc*=leachFactor;
        double chProbability = leachCalc < 1 ? leachCalc : 1;
        double randNum = (float)rand()/((float)RAND_MAX)/2;
        if(randNum <= chProbability){
            this->chAddr = getSelfIPAddress();
            auto chDefMsg = createChDefMsg();
            sendHeartBeatpkg(chDefMsg, addressType->getBroadcastAddress(), 1, 0);
        }
    }
    resetLeachCalculation();
}

void SatelliteRouting::resetLeachCalculation(){
    delete(this->leachNeigh);
    this->leachNeigh = new std::vector<L3Address>();
    neighBatteryMean = 0.0;
    higherNeighBattery=0.0;
}

void SatelliteRouting::updateChCandidate(L3Address candidate, int batteryPercent, Coord senderCoord){
    int selfBattery = getDevBatteryPower();
    Coord devCoord = baseMobility->getCurrentPosition();
    double n_dist = devCoord.distance(senderCoord);
    double o_dist;
    bool mlEnable = getModuleByPath("simpleNetwork")->par("mlEnable");
    if(chCoord == Coord(0,0,0)){
        if(mlEnable)
            o_dist = 10000;
        else
            o_dist = 0;
    } else
        o_dist = devCoord.distance(chCoord);
    if(!candidate.isUnspecified()){
        if(candidate == chAddr){
            newChBattery = batteryPercent;
            newChAddr = candidate;
            chCoord = senderCoord;
        }else{
            if(mlEnable){
                if(n_dist < o_dist){
                    if(selfBattery < batteryPercent){
                        if(batteryPercent > chBattery && batteryPercent >= batteryThresh){
                            newChBattery = batteryPercent;
                            newChAddr = candidate;
                            chCoord = senderCoord;
                        }
                    }else{
                        if(selfBattery > chBattery){
                            if(selfBattery >= batteryThresh){
                                newChBattery = selfBattery;
                                newChAddr = getSelfIPAddress();
                                chCoord = senderCoord;
                            }
                        }
                    }
                }
            }else{
                if(n_dist > o_dist){
                    if(selfBattery < batteryPercent){
                        if(batteryPercent > chBattery && batteryPercent >= batteryThresh){
                            newChBattery = batteryPercent;
                            newChAddr = candidate;
                            chCoord = senderCoord;
                        }
                    }else{
                        if(selfBattery > chBattery){
                            if(selfBattery >= batteryThresh){
                                newChBattery = selfBattery;
                                newChAddr = getSelfIPAddress();
                                chCoord = senderCoord;
                            }
                        }
                    }
                }
            }
        }
    }
    EV << "CH: " << chAddr << endl << "CH battery: " << chBattery << endl;
}

IRoute *SatelliteRouting::createRoute(const L3Address& destAddr, const L3Address& nextHop,
        unsigned int hopCount, bool hasValidDestNum, unsigned int destSeqNum,
        bool isActive, simtime_t lifeTime)
{

    // create a new route
    IRoute *newRoute = routingTable->createRoute();

    // adding generic fields
    newRoute->setDestination(destAddr);
    newRoute->setNextHop(nextHop);
    newRoute->setPrefixLength(addressType->getMaxPrefixLength());    // TODO:
    newRoute->setMetric(hopCount);
    InterfaceEntry *ifEntry = interfaceTable->findInterfaceByName(par("interface"));    // TODO: IMPLEMENT: multiple interfaces
    if (ifEntry)
        newRoute->setInterface(ifEntry);
    newRoute->setSourceType(IRoute::SIXGEN);
    newRoute->setSource(this);

    // A route towards a destination that has a routing table entry
    // that is marked as valid.  Only active routes can be used to
    // forward data packets.

    // adding protocol-specific fields
    HeartBeatRouteData *newProtocolData = new HeartBeatRouteData();
    newProtocolData->setIsActive(isActive);
    newProtocolData->setHasValidDestNum(hasValidDestNum);
    newProtocolData->setDestSeqNum(destSeqNum);
    newProtocolData->setLifeTime(lifeTime);
    newRoute->setProtocolData(newProtocolData);

    EV_DETAIL << "Adding new route " << newRoute << endl;
    routingTable->addRoute(newRoute);

    scheduleExpungeRoutes();
    return newRoute;
}

void SatelliteRouting::handleStopOperation(LifecycleOperation *operation)
{
    socket.close();
    clearState();
}

void SatelliteRouting::handleCrashOperation(LifecycleOperation *operation)
{
    socket.destroy();
    clearState();
}

void SatelliteRouting::clearState()
{
    rerrCount = rreqCount = rreqId = sequenceNum = 0;
    addressToRreqRetries.clear();
    for (auto & elem : waitForRREPTimers)
        cancelAndDelete(elem.second);

    // FIXME: Drop the queued datagrams.
    //for (auto it = targetAddressToDelayedPackets.begin(); it != targetAddressToDelayedPackets.end(); it++)
    //    networkProtocol->dropQueuedDatagram(const_cast<const Packet *>(it->second));

    targetAddressToDelayedPackets.clear();

    waitForRREPTimers.clear();
    rreqsArrivalTime.clear();

    if (useHelloMessages)
        cancelEvent(helloMsgTimer);
    if (expungeTimer)
        cancelEvent(expungeTimer);
    if (counterTimer)
        cancelEvent(counterTimer);
//    if (blacklistTimer)
//        cancelEvent(blacklistTimer);
//    if (rrepAckTimer)
//        cancelEvent(rrepAckTimer);
    if (chInfo)
        cancelEvent(chInfo);
    if (chElection)
        cancelEvent(chElection);
    if (cainTrigger)
        cancelEvent(cainTrigger);
    if (conncetedDevTimer)
        cancelEvent(conncetedDevTimer);
    if(endTimer)
        cancelEvent(endTimer);
    if(sendFlWeights)
        cancelEvent(sendFlWeights);
    if(sendFlAvgWeights)
        cancelEvent(sendFlAvgWeights);
    if(leachChDecision)
        cancelEvent(leachChDecision);
}

L3Address SatelliteRouting::getSelfIPAddress() const
{
    return routingTable->getRouterIdAsGeneric();
}

void SatelliteRouting::delayDatagram(Packet *datagram)
{
    const auto& networkHeader = getNetworkProtocolHeader(datagram);
    EV_DETAIL << "Queuing datagram, source " << networkHeader->getSourceAddress() << ", destination " << networkHeader->getDestinationAddress() << endl;
    const L3Address& target = networkHeader->getDestinationAddress();
    targetAddressToDelayedPackets.insert(std::pair<L3Address, Packet *>(target, datagram));
}

void SatelliteRouting::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processPacket(packet);
}

void SatelliteRouting::handleWaitForRREP(WaitForRrep *rrepTimer)
{
    EV_INFO << "We didn't get any Route Reply within RREP timeout" << endl;
    L3Address destAddr = rrepTimer->getDestAddr();

    ASSERT(addressToRreqRetries.find(destAddr) != addressToRreqRetries.end());
    if (addressToRreqRetries[destAddr] == rreqRetries) {
        cancelRouteDiscovery(destAddr);
        EV_WARN << "Re-discovery attempts for node " << destAddr << " reached RREQ_RETRIES= " << rreqRetries << " limit. Stop sending RREQ." << endl;
        return;
    }
    //if(strcmp(this->getParentModule()->getName(),"drone")){//not a drone
        auto rreq = createSnoopMsg();


        // the node MAY try again to discover a route by broadcasting another
        // RREQ, up to a maximum of RREQ_RETRIES times at the maximum TTL value.
        if (rrepTimer->getLastTTL() == netDiameter) // netDiameter is the maximum TTL value
            addressToRreqRetries[destAddr]++;

        sendSnooping(rreq, 0);
}

void SatelliteRouting::cancelRouteDiscovery(const L3Address& destAddr)
{
    ASSERT(hasOngoingRouteDiscovery(destAddr));
    auto lt = targetAddressToDelayedPackets.lower_bound(destAddr);
    auto ut = targetAddressToDelayedPackets.upper_bound(destAddr);
    for (auto it = lt; it != ut; it++)
        networkProtocol->dropQueuedDatagram(const_cast<const Packet *>(it->second));

    targetAddressToDelayedPackets.erase(lt, ut);

    auto waitRREPIter = waitForRREPTimers.find(destAddr);
    ASSERT(waitRREPIter != waitForRREPTimers.end());
    cancelAndDelete(waitRREPIter->second);
    waitForRREPTimers.erase(waitRREPIter);
}

int SatelliteRouting::getDevBatteryPower(){
    return (int)round(unit(energyStorage->getResidualEnergyCapacity()/energyStorage->getNominalEnergyCapacity()).get() * 100);
}

double SatelliteRouting::backoffTimer(){
    int battery = getDevBatteryPower();
    int backoff;
    if(battery > 75)
        backoff = 2;
    else if(battery <= 75 && battery > 50)
        backoff = 4;
    else if(battery <=50 && battery > 25)
        backoff = 8;
    else
        backoff = 16;
    return (rand()%backoff+1);//+(rand()%host->getId()+1);
//    return host->getId();
}

double SatelliteRouting::cainBackoff(){
    int p;
    if(currBackoff > 4)
        p = pow(2,4);
    else
        p = pow(2,currBackoff);
    return rand()%p+1;
}

void SatelliteRouting::updateConnectedDevs(){
//    connectedDevs->clear();
    map<L3Address,pair<int,bool>>::iterator connectedIt = connectedDevs->begin();
    for(; connectedIt != connectedDevs->end(); connectedIt++)
        connectedDevs->operator [](connectedIt->first).second = false;

    map<L3Address,int>::iterator newConnectedIt = newConnectedDevs->begin();
    for(; newConnectedIt != newConnectedDevs->end(); newConnectedIt++)
        connectedDevs->operator [](newConnectedIt->first) = pair<int,bool>(newConnectedIt->second,true);
    newConnectedDevs->clear();
    connectedIt = connectedDevs->begin();
    EV << "Devices connected to " << getSelfIPAddress() << ":" << endl;
    for(; connectedIt != connectedDevs->end(); connectedIt++){
        EV << "Address: " << connectedIt->first << "| Battery: " << connectedIt->second.first <<
                "| Active:" << (connectedIt->second.second ? "True" : "False")  << endl;
    }
    numConnectedDevs = connectedDevs->size();
    emit(connectedDevsSignal, numConnectedDevs);
}

void SatelliteRouting::updateBestHop(L3Address srcAddr){
    scNeighbMap->operator [](srcAddr)++;
    if(scNeighbMap->operator [](srcAddr) > bestHopAddr->second){
        bestHopAddr->first=srcAddr;
        bestHopAddr->second=scNeighbMap->operator [](srcAddr);
    }
}

void SatelliteRouting::updateLarBestHop(L3Address srcAddr, Coord senderCoord){
    Coord thisCoord = baseMobility->getCurrentPosition();
    float dist = thisCoord.distance(senderCoord);
    if(bestLarHopAddr->first.isUnspecified()){
        bestLarHopAddr->first=srcAddr;
        bestLarHopAddr->second=dist;
    }else{
        if(dist < bestLarHopAddr->second){
            bestLarHopAddr->first=srcAddr;
            bestLarHopAddr->second=dist;
        }
    }
}

int SatelliteRouting::get_coverage_state(L3Address cain_dest){
    if(rl_type == "Euclidean1" || rl_type == "Euclidean2"  ||
                rl_type == "Euclidean3"){
        double dist = distMap->at(cain_dest);
        for(int i=0;i<qtd_ranges;i++){
            if(dist<=(i+1)*(com_range/qtd_ranges)){
                return i;
            }
        }
    }else if(rl_type == "Hop1" || rl_type == "Hop2"  ||
            rl_type == "Hop3"){

        long hop = hopMap->at(cain_dest);
        for(int i=0;i<qtd_ranges;i++){
            if(hop<=(i+1)*(hop_range/qtd_ranges)){
                return i;
            }
        }
    }
    return 0;
}

void SatelliteRouting::calculate_coverage_reward(int state,bool decision,L3Address cain_dest){
    double percent;
    if(rl_type == "Euclidean1" || rl_type == "Euclidean2"  ||
                rl_type == "Euclidean3"){
        double dist = distMap->at(cain_dest);
        for(int i=0;i<qtd_ranges;i++){
            if(dist<=(i+1)*(com_range/qtd_ranges)){
                percent=dist/((i+1)*(com_range/qtd_ranges));
                percent*=100;
                break;
            }
        }
    }else if(rl_type == "Hop1" || rl_type == "Hop2"  ||
            rl_type == "Hop3"){

        long hop = hopMap->at(cain_dest);
        for(int i=0;i<qtd_ranges;i++){
            if(hop<=(i+1)*(hop_range/qtd_ranges)){
                percent=hop/((i+1)*(hop_range/qtd_ranges));
                percent*=100;
                break;
            }
        }
    }

    switch (state) {
        case 0:
            stateMatrix[state][decision]->at(0)*=n_s0;
            stateMatrix[state][decision]->at(0)+=percent;
            n_s0++;
            stateMatrix[state][decision]->at(0)/=n_s0;
            break;
        case 1:
            stateMatrix[state][decision]->at(1)*=n_s1;
            stateMatrix[state][decision]->at(1)+=percent;
            n_s1++;
            stateMatrix[state][decision]->at(1)/=n_s1;
            break;
        case 2:
            stateMatrix[state][decision]->at(2)*=n_s2;
            stateMatrix[state][decision]->at(2)+=percent;
            n_s2++;
            stateMatrix[state][decision]->at(2)/=n_s2;
            break;
    }
}


void SatelliteRouting::updatePowerThreshold(int state){
    /*if(state == 0 && powerThresh > 5){
        powerThresh-=5;
    }else if(state == 2 && powerThresh < 95)
        powerThresh+=5;*/
}

bool SatelliteRouting::sendMessageML(int state){
    if(qMatrix[state][0]>=qMatrix[state][1])//state0 (send) is the best option
        return true;
    return false;//state1 (not send) is the best option
    /*double prob=rand()%100+1;
    if(prob <= send_prob)
        return true;
    return false;*/
    /*int selfBattery = getDevBatteryPower();
    if(powerThresh<selfBattery){
        double sendProb=(1-(powerThresh/selfBattery))*100;
        int val = rand()%101;
        if(sendProb <= val)
            return true;
        return false;
    }
    return false;*/
}

void SatelliteRouting::calculate_q_matrix(){
    float discount_rate = 0.95;
    int n_interations = 100;

    for(int i=0; i <= n_interations; i++){
        float q_prev[3][4];

        for(int j=0; j<3; j++)
            for(int k=0; k<4;k++)
                q_prev[j][k]=qMatrix[j][k];
        for(int s=0;s<3;s++){
          for(int a=0; a<4;a++){
                float incr=0;
                for(int sp=0;sp<3;sp++){
                    float max=0;
                      for(int al=0; al<4;al++){
                        if(q_prev[sp][al]>max)
                            max=q_prev[sp][al];
                      }
                      float sMatr=stateMatrix[s][a]->at(sp);
                      float rMatr=rewardMatrix[s][a]->at(sp);
                      if(qtdMsg){
                          double weight = meanDelay.dbl()*pow(10,6);
                          weight = 1/weight;
                          incr+=stateMatrix[s][a]->at(sp)*(rewardMatrix[s][a]->at(sp)*weight+discount_rate*max);
                      }else
                          incr+=stateMatrix[s][a]->at(sp)*(rewardMatrix[s][a]->at(sp)+discount_rate*max);
                }
                qMatrix[s][a]=incr;
            }
        }
    }
}

void SatelliteRouting::calculate_drone_q_matrix(){
    float discount_rate = 0.95;
    int n_interations = 100;

    for(int i=0; i <= n_interations; i++){
        float q_prev[3][4];

        for(int j=0; j<3; j++)
            for(int k=0; k<4;k++)
                q_prev[j][k]=droneQMatrix[j][k];
        for(int s=0;s<3;s++){
          for(int a=0; a<4;a++){
                float incr=0;
                for(int sp=0;sp<3;sp++){
                    float max=0;
                      for(int al=0; al<4;al++){
                        if(q_prev[sp][al]>max)
                            max=q_prev[sp][al];
                      }
                      float sMatr=stateMatrix[s][a]->at(sp);
                      float rMatr=rewardMatrix[s][a]->at(sp);
                      if(qtdMsg){
                          double weight = meanDelay.dbl()*pow(10,6);
                          weight = 1/weight;
                          incr+=stateMatrix[s][a]->at(sp)*(rewardMatrix[s][a]->at(sp)*weight+discount_rate*max);
                      }else
                          incr+=stateMatrix[s][a]->at(sp)*(rewardMatrix[s][a]->at(sp)+discount_rate*max);
                }
                droneQMatrix[s][a]=incr;
            }
        }
    }
}

void SatelliteRouting::calculateDnnDecision(L3Address cainDest){
    for(int i = 0; i<100; i++){
        int state = get_coverage_state(cainDest);
        double dnnDist;
        if(rl_type == "Euclidean1" || rl_type == "Euclidean2" ||
                rl_type == "Euclidean3")
            dnnDist = calculateDnnDist(state, distMap->at(cainDest),rl_type);
        else
            dnnDist = calculateDnnDist(state, hopMap->at(cainDest),rl_type);
        std::vector<bool> *decisionVect = network->calculateDnn(dnnDist, meanDelay.dbl()*pow(10,6),probPhero);
        int decision;

        if(decisionVect->operator [](0)){//true
            if(decisionVect->operator [](1))//true-true
                decision=3;
            else//true-false
                decision=2;
        }else{//false
            if(decisionVect->operator [](1))//false-true
                decision=1;
            else//false-false
                decision=0;
        }
        calculate_coverage_reward(state, decision, cainDest);
        calculate_q_matrix();
        float result = qMatrix[state][decision];
        network->updateDnn(result,decisionVect);
    }
}

double SatelliteRouting::calculateDnnDist(int state, double dist, std::string rl_type){
    if(rl_type == "Euclidean1" || rl_type == "Hop1"){
        //dist-state to normalize the distance
        double distPercentage = (dist-state)/qtd_ranges;
        return distPercentage;
    }
    if(rl_type == "Euclidean2" || rl_type == "Hop2"){
        double avgDistance;
        if(rl_type == "Euclidean2")
            avgDistance = (com_range/qtd_ranges)/2;
        else
            avgDistance = (hop_range/qtd_ranges)/2;
        //dist-state to normalize the distance
        double distPercentage = (dist-state-avgDistance);
        return 1/distPercentage;
    }
    if(rl_type == "Euclidean3" || rl_type == "Hop3"){
        //dist-state to normalize the distance
        return (dist-state)/qtd_ranges;
    }
    return 0.0;
}

void SatelliteRouting::create_reward_matrix(){
    vector<float>* a0;
    vector<float>* a1;
    if(rl_type == "Euclidean1" || rl_type == "Hop1"){
        //higher distance/hop
        //a0 -> send a1 not send
        //s0 -> closer s1 -> median s2 ->further
        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(-100);
        a0->push_back(-50);
        a0->push_back(0);
        a1->push_back(100);
        a1->push_back(50);
        a1->push_back(0);
        rewardMatrix[0][0]=a0;
        rewardMatrix[0][1]=a1;
        rewardMatrix[0][2]=a0;
        rewardMatrix[0][3]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(0);
        a0->push_back(50);
        a0->push_back(100);
        a1->push_back(0);
        a1->push_back(-50);
        a1->push_back(-100);
        rewardMatrix[1][0]=a0;
        rewardMatrix[1][1]=a1;
        rewardMatrix[1][2]=a0;
        rewardMatrix[1][3]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(0);
        a0->push_back(50);
        a0->push_back(100);
        a1->push_back(0);
        a1->push_back(-50);
        a1->push_back(-100);
        rewardMatrix[2][0]=a0;
        rewardMatrix[2][1]=a1;
        rewardMatrix[2][2]=a0;
        rewardMatrix[2][3]=a1;
    } else if(rl_type == "Euclidean2" || rl_type == "Hop2"){
        //higher distance/hop
        //a0 -> send a1 not send
        //s0 -> closer s1 -> median s2 ->further
        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(100);
        a0->push_back(50);
        a0->push_back(0);
        a1->push_back(-100);
        a1->push_back(-50);
        a1->push_back(0);
        rewardMatrix[0][0]=a0;
        rewardMatrix[0][1]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(0);
        a0->push_back(50);
        a0->push_back(100);
        a1->push_back(0);
        a1->push_back(-50);
        a1->push_back(-100);
        rewardMatrix[1][0]=a0;
        rewardMatrix[1][1]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(0);
        a0->push_back(-50);
        a0->push_back(-100);
        a1->push_back(0);
        a1->push_back(50);
        a1->push_back(100);
        rewardMatrix[2][0]=a0;
        rewardMatrix[2][1]=a1;
    }else if(rl_type == "Euclidean3" || rl_type == "Hop3"){
        //higher distance/hop
        //a0 -> send a1 not send
        //s0 -> closer s1 -> median s2 ->further
        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(50);
        a0->push_back(50);
        a0->push_back(0);
        a1->push_back(-50);
        a1->push_back(-50);
        a1->push_back(0);
        rewardMatrix[0][0]=a0;
        rewardMatrix[0][1]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(0);
        a0->push_back(100);
        a0->push_back(100);
        a1->push_back(0);
        a1->push_back(-100);
        a1->push_back(-100);
        rewardMatrix[1][0]=a0;
        rewardMatrix[1][1]=a1;

        a0 = new vector<float>();
        a1 = new vector<float>();

        a0->push_back(0);
        a0->push_back(50);
        a0->push_back(50);
        a1->push_back(0);
        a1->push_back(-50);
        a1->push_back(-50);
        rewardMatrix[2][0]=a0;
        rewardMatrix[2][1]=a1;
    }
}


SatelliteRouting::SatelliteRouting() {
    // TODO Auto-generated constructor stub

}

SatelliteRouting::~SatelliteRouting() {
//    clearState();
//    delete helloMsgTimer;
//    delete expungeTimer;
//    delete counterTimer;
//    delete rrepAckTimer;
//    delete blacklistTimer;
}

} /* namespace SatelliteRouting */
} /* namespace  inet*/
