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

#ifndef INET_ROUTING_SIXGEN_ANTENNAROUTING_H_
#define INET_ROUTING_SIXGEN_ANTENNAROUTING_H_

#include <map>
#include "inet/common/INETDefs.h"
#include "inet/common/oracle/Oracle.h"
#include "inet/common/sixgenCommon/SixgenCommon.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/contract/INetfilter.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/routing/sixgen/heartBeat_m.h"
#include "inet/routing/base/RoutingProtocolBase.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "inet/transportlayer/udp/UdpHeader_m.h"
#include "inet/mobility/single/BonnMotionMobility.h"
#include "inet/mobility/single/MassMobility.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/power/storage/SimpleEpEnergyStorage.h"
#include "inet/power/management/SimpleEpEnergyManagement.h"
#include <omnetpp.h>
#include "inet/dnn/dnn.h"

namespace inet {
namespace antennarouting {

using namespace power;
using namespace wirelessrouting;

class INET_API AntennaRouting : public RoutingProtocolBase, public NetfilterBase::HookBase, public UdpSocket::ICallback, public cListener
{
private:

    BonnMotionMobility* baseMobility = nullptr;
    MassMobility* droneMobility = nullptr;
    SimpleEpEnergyStorage* energyStorage = nullptr;
    SimpleEpEnergyManagement* energyManagement = nullptr;
    std::string rl_type=getModuleByPath("simpleNetwork")->par("rl_type");
    dnn* network;
    int index=0;
    vector<float>* stateMatrix[3][4];
    vector<float>* rewardMatrix[3][4];
    float qMatrix[3][4];
    /**
     * map for the RL algorithm using the Euclidean distance metric
     * This map stores the distance between the node and its neighbors
     *  -------------------------
     * |neighbAddr|distNodeNeighb|
     *  -------------------------
     * */
    map<L3Address,double> *distMap;
    map<L3Address,std::string> *recFwdMessages; //stores the received messages' id
    list<std::string> *sentMessages; //stores the sent messages' id
    int numNodes;
    int com_range;//alpha threshold for the RL Euclidean distance
    int qtd_ranges;//beta threshold for the RL algorithms
    int send_prob;//probability to send a message
    int timeCounter=0;//counter to reset the distance and hop thresholds
    map<pair<L3Address,L3Address>,pair<L3Address,int>> *routes;//<<originator,destination>,<next_hop,battery>>
    map<pair<L3Address,L3Address>,L3Address> *revRoute;//<<originator,destination>,prev_hop>

//    std::string netType;

    simsignal_t recCainFwdMsgSignal;
    simsignal_t distSignal;
    simsignal_t timeSignal;
    simsignal_t sendProbSignal;
    simsignal_t distMapSizeSignal;
    simsignal_t sentAntennaMsgSignal;
    simsignal_t recDroneMsgSignal;
    simsignal_t recSatMsgSignal;
    simsignal_t antennaDistSignal;
    long numConnectedDevs = 0;
    long recCainFwdMsg = 0;
    double dist = 0;
    simtime_t delay = 0;
    long nodeEnd=0;
    long sendProb=0;
    long distMapSize=0;
    long sentAntennaMsg=0;
    long recDroneMsg=0;
    long recSatMsg=0;
    double antennaDist = 0;

    simtime_t meanDelay=0;
    unsigned int qtdMsg=0;

    int debug=0;

    int getDevBatteryPower();

    protected:
    /*
     * It implements a unique identifier for an arbitrary RREQ message
     * in the network. See: rreqsArrivalTime.
     */
    class RreqIdentifier
    {
      public:
        L3Address originatorAddr;
        unsigned int rreqID;
        RreqIdentifier(const L3Address& originatorAddr, unsigned int rreqID) : originatorAddr(originatorAddr), rreqID(rreqID) {};
        bool operator==(const RreqIdentifier& other) const
        {
            return this->originatorAddr == other.originatorAddr && this->rreqID == other.rreqID;
        }
    };

    class RreqIdentifierCompare
    {
    public:
        bool operator()(const RreqIdentifier& lhs, const RreqIdentifier& rhs) const
        {
            if (lhs.originatorAddr < rhs.originatorAddr)
                return true;
            else if (lhs.originatorAddr > rhs.originatorAddr)
                return false;
            else
                return lhs.rreqID < rhs.rreqID;
        }
    };


    // context
    IL3AddressType *addressType = nullptr;    // to support both Ipv4 and v6 addresses.

    // environment
    cModule *host = nullptr;
    IRoutingTable *routingTable = nullptr;
    IInterfaceTable *interfaceTable = nullptr;
    INetfilter *networkProtocol = nullptr;
    UdpSocket socket;
    UdpSocket centralSocket;
    bool usingIpv6 = false;

    //ch definition
    simtime_t routingStart; //timer for start the routing protocol

    // AntennaRouting parameters: the following parameters are configurable, see the NED file for more info.
    unsigned int rerrRatelimit = 0;
    unsigned int WirelessRoutingUDPPort = 0;
    bool askGratuitousRREP = false;
    bool useHelloMessages = false;
    bool destinationOnlyFlag = false;
    simtime_t maxJitter;
    simtime_t activeRouteTimeout;
    simtime_t helloInterval;
    unsigned int netDiameter = 0;
    unsigned int rreqRetries = 0;
    unsigned int rreqRatelimit = 0;
    unsigned int timeoutBuffer = 0;
    unsigned int ttlStart = 0;
    unsigned int ttlIncrement = 0;
    unsigned int ttlThreshold = 0;
    unsigned int localAddTTL = 0;
    unsigned int allowedHelloLoss = 0;
    unsigned int nNeigh = 0;
    simtime_t nodeTraversalTime;
    cPar *jitterPar = nullptr;
    cPar *periodicJitter = nullptr;

    // the following parameters are calculated from the parameters defined above
    // see the NED file for more info
    simtime_t deletePeriod;
    simtime_t myRouteTimeout;
    simtime_t blacklistTimeout;
    simtime_t netTraversalTime;
    simtime_t nextHopWait;
    simtime_t pathDiscoveryTime;

    // state
    unsigned int rreqId = 0;    // when sending a new RREQ packet, rreqID incremented by one from the last id used by this node
    unsigned int sequenceNum = 0;    // it helps to prevent loops in the routes (RFC 3561 6.1 p11.)
    std::map<L3Address, WaitForRrep *> waitForRREPTimers;    // timeout for Route Replies
    std::map<RreqIdentifier, simtime_t, RreqIdentifierCompare> rreqsArrivalTime;    // maps RREQ id to its arriving time
    L3Address failedNextHop;    // next hop to the destination who failed to send us RREP-ACK
    std::map<L3Address, simtime_t> blacklist;    // we don't accept RREQs from blacklisted nodes
    unsigned int rerrCount = 0;    // num of originated RERR in the last second
    unsigned int rreqCount = 0;    // num of originated RREQ in the last second
    simtime_t lastBroadcastTime;    // the last time when any control packet was broadcasted
    std::map<L3Address, unsigned int> addressToRreqRetries;    // number of re-discovery attempts per address

    L3Address droneAddr; //address from last drone in range
    L3Address satelliteAddr; //address from last satellite in range

    // self messages
    cMessage *helloMsgTimer = nullptr;    // timer to send hello messages (only if the feature is enabled)
    cMessage *expungeTimer = nullptr;    // timer to clean the routing table out
    cMessage *counterTimer = nullptr;    // timer to set rrerCount = rreqCount = 0 in each second
    cMessage *rrepAckTimer = nullptr;    // timer to wait for RREP-ACKs (RREP-ACK timeout)
    cMessage *blacklistTimer = nullptr;    // timer to clean the blacklist out
    cMessage *endTimer = nullptr;    // timer to check simulations end
    cMessage *antennaTimer = nullptr; //timer for antenna start operating

    // lifecycle
    simtime_t rebootTime;    // the last time when the node rebooted

    double calculateDnnDist(int state, double dist, std::string rl_type);
    // internal
    std::multimap<L3Address, Packet *> targetAddressToDelayedPackets;    // queue for the datagrams we have no route for

  protected:
    void handleMessageWhenUp(cMessage *msg) override;
    void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }

//    /* Route Discovery */
    void startRouteDiscovery(const L3Address& target, unsigned int timeToLive = 0);
    void completeRouteDiscovery(const L3Address& target);
    bool hasOngoingRouteDiscovery(const L3Address& destAddr);
    void cancelRouteDiscovery(const L3Address& destAddr);
//
//    /* Routing Table management */
    void updateRoutingTable(IRoute *route, const L3Address& nextHop, unsigned int hopCount, bool hasValidDestNum, unsigned int destSeqNum, bool isActive, simtime_t lifeTime);
    IRoute *createRoute(const L3Address& destAddr, const L3Address& nextHop, unsigned int hopCount, bool hasValidDestNum, unsigned int destSeqNum, bool isActive, simtime_t lifeTime);
    bool updateValidRouteLifeTime(const L3Address& destAddr, simtime_t lifetime);
    void scheduleExpungeRoutes();
    void expungeRoutes();
//    void sendToCentralNode(const char *message);
//
//    /* Control packet creators */
    const Ptr<SNOOPHB> createSnoopMsg();
    const Ptr<ANTENNA> createAntennaMsg();
    const Ptr<Rerr> createRERR(const std::vector<UnreachableNode>& unreachableNodes);
    const Ptr<SNOOPHB> createHelloMessage();
//
    /* Control Packet handlers */
    void handleSnooping(const Ptr<SNOOPHB>& snoop, const L3Address& sourceAddr);
    void handleCainFWD(const Ptr<CAINMSG>& cainmsg);
    void handleAntennaMsg(const Ptr<ANTENNA>& antennaMsg);
    void handleDroneMsg(const Ptr<DRONEMSG>& droneMsg);
    void handleSatelliteMsg(const Ptr<SATMSG>& satMsg);
//
//    /* Control Packet sender methods */
    void sendSnooping(const Ptr<SNOOPHB>& snoop, unsigned int timeToLive);
    void sendResp(const Ptr<RESPHB>& resp, const L3Address& destAddr, unsigned int timeToLive);
    void sendCainMsg(const Ptr<CAINMSG>& cainmsg, unsigned int timeToLive,double delay);

    void calcDelayMean(simtime_t msgInit);
//
    int get_coverage_state(L3Address cain_dest);
    void calculate_coverage_reward(int state,bool decision,L3Address cain_dest);
    bool sendMessageML(int state);
    void create_reward_matrix();
    void calculate_q_matrix();
    void calculateDnnDecision(L3Address cainDest);

    /* Self message handlers */
    void handleRREPACKTimer();
    void handleBlackListTimer();
    void sendHelloMessagesIfNeeded();
    void handleWaitForRREP(WaitForRrep *rrepTimer);
//
//    /* General functions to handle route errors */
    void sendRERRWhenNoRouteToForward(const L3Address& unreachableAddr);
    void handleLinkBreakSendRERR(const L3Address& unreachableAddr);
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

    /* Netfilter hooks */
    Result ensureRouteForDatagram(Packet *datagram);
    virtual Result datagramPreRoutingHook(Packet *datagram) override { Enter_Method("datagramPreRoutingHook"); return ensureRouteForDatagram(datagram); }
    virtual Result datagramForwardHook(Packet *datagram) override;
    virtual Result datagramPostRoutingHook(Packet *datagram) override { return ACCEPT; }
    virtual Result datagramLocalInHook(Packet *datagram) override { return ACCEPT; }
    virtual Result datagramLocalOutHook(Packet *datagram) override { Enter_Method("datagramLocalOutHook"); return ensureRouteForDatagram(datagram); }
    void delayDatagram(Packet *datagram);

    /* Helper functions */
    L3Address getSelfIPAddress() const;
    void sendHeartBeatpkg(const Ptr<HeartBeat>& packet, const L3Address& destAddr, unsigned int timeToLive, double delay);
    void processPacket(Packet *pk);
    void clearState();
//    void checkIpVersionAndPacketTypeCompatibility(WirelessRoutingControlPacketType packetType);
//
    /* UDP callback interface */
    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    virtual void socketClosed(UdpSocket *socket) override;

    /* Lifecycle */
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;


    void updateChCandidate(L3Address candidate, int batteryPercent, Coord senderCoord);
public:
    AntennaRouting();
    virtual ~AntennaRouting();
};

} /* namespace AntennaRouting */
} /* namespace  inet*/
#endif /* INET_ROUTING_SIXGEN_AntennaRouting_H_ */
