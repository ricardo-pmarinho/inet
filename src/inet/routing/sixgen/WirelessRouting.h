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

#ifndef INET_ROUTING_SIXGEN_WIRELESSROUTING_H_
#define INET_ROUTING_SIXGEN_WIRELESSROUTING_H_

#include <map>
#include "inet/common/INETDefs.h"
#include "inet/common/oracle/Oracle.h"
#include "inet/common/sixgenCommon/SixgenCommon.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/contract/INetfilter.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/routing/sixgen/heartBeat_m.h"
//#include "inet/routing/sixgen/WirelessRoutingRouteData.h"
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
namespace wirelessrouting {

using namespace power;

class INET_API WirelessRouting : public RoutingProtocolBase, public NetfilterBase::HookBase, public UdpSocket::ICallback, public cListener
{
private:

    BonnMotionMobility* baseMobility = nullptr;
    MassMobility* droneMobility = nullptr;
    SimpleEpEnergyStorage* energyStorage = nullptr;
    SimpleEpEnergyManagement* energyManagement = nullptr;
    Oracle *oracle_ = nullptr;
    L3Address chAddr;
    L3Address newChAddr = L3Address("0.0.0.0");
    pair<L3Address,int> *bestHopAddr;
    map<L3Address,int> *scNeighbMap;
    pair<L3Address,float> *bestLarHopAddr;
    vector<L3Address>* sprayNWaitNeighb;
    std::string rl_type=getModuleByPath("simpleNetwork")->par("rl_type");
    double alpha = getModuleByPath("simpleNetwork")->par("alphaRl");
    dnn* network;
    dnn* droneNetwork;
    int chBattery = 0;
    int newChBattery = 0;
    int index=0;
    Coord chCoord;
    int powerThresh;
    int batteryThresh;
    int fwdSeqNum = 0;
    int reqSeqNum = 0;
    int repSeqNum = 0;
    int hopSeqNum = 0;
    int scSeqNum = 0;
    int n_s0=0; //number of times a node chosen for communication was in state 0 (closer)
    int n_s1=0; //number of times a node chosen for communication was in state 1 (median)
    int n_s2=0; //number of times a node chosen for communication was in state 2 (further)
    int currState = 0; //RL states 0-> decrease battery tresh; 1->maintain battery tresh; 2->increase battery tresh
    int qtdMessArrived = 0; //stores the number of different reply messages arrived
    double averageHop = 0; //average number of hops for the reply
    vector<float>* stateMatrix[3][4];
    vector<float>* rewardMatrix[3][4];
    float qMatrix[3][4];
    float droneQMatrix[3][4];
    /*map to store the addresses and battery from devices responding a cain request
     * first pair: message source address and battery
     * secon pair: ch address and battery*/
    map<pair<L3Address,int>,pair<L3Address,int>> *respMap;
    /**
     * map for the RL algorithm using the Euclidean distance metric
     * This map stores the distance between the node and its neighbors
     *  -------------------------
     * |neighbAddr|distNodeNeighb|
     *  -------------------------
     * */
    map<L3Address,double> *distMap;
    map<L3Address,double> *droneDistMap; //map for the RL algorithm: distance for drones when a host receives it and
                                         //distance from satellite when drone receives it
    map<L3Address,long> *hopMap;//map for the RL algorithm using the hop count metric
    map<L3Address,int> *centralityMap;
    /**
     * This map stores the distance between the neighbor and its CH
     *  -----------------------
     * |neighbAddr|neighbCHDist|
     *  -----------------------
     * */
    map<L3Address,double> *neighCHDistMap;
    map<L3Address,int> *neighbMap; //neighbors wit their battery level
    map<L3Address,pair<int,bool>> *connectedDevs; //if device is a CH, stores the connected devices to it
    map<L3Address,int> *newConnectedDevs; //a backup for the case that the connected devices map is not update
    map<L3Address,std::string> *recFwdMessages; //stores the received messages' id
    list<std::string> *sentMessages; //stores the sent messages' id
    vector<int> *fwdAck; //vector to store the sequence number of the fwd messages that were not acked yet
    vector<int> *reqAck; //vector to store the sequence number of the req messages that were not acked yet
    vector<int> *hopAck; //vector to store the sequence number of the hop messages that were not acked yet
    bool cainReq = false; //true in case that the device sent a CAINREQ message
    int currBackoff = 0;    //backoff index for not ack cain message (max 4)
    int numNodes;
    int com_range;//alpha threshold for the RL Euclidean distance
    int qtd_ranges;//beta threshold for the RL algorithms
    int send_prob;//probability to send a message
    int hop_range;//delta threshold for the RL hop count
    int timeCounter=0;//counter to reset the distance and hop thresholds
    unsigned int weightMsgCounter=0;//counter to know how many weight messages this CH has received
    bool chCandidate = true; //node can be a CH candidate for LEACH
    double neighBatteryMean = 0.0;
    int higherNeighBattery = 0; //for the leach ch election process
    double neighDistMean = 0.0;
    std::vector<L3Address> *leachNeigh;
    int chNum;
    /**
     * Stores the distance to the node's CH
     * */
    double chDist;

    map<pair<L3Address,L3Address>,pair<L3Address,int>> *routes;//<<originator,destination>,<next_hop,battery>>
    map<pair<L3Address,L3Address>,L3Address> *revRoute;//<<originator,destination>,prev_hop>

//    std::string netType;

    simsignal_t cainMsgSignal;
    simsignal_t connectedDevsSignal;
    simsignal_t recCainFwdMsgSignal;
    simsignal_t sentCainFwdMsgSignal;
    simsignal_t recCainReqMsgSignal;
    simsignal_t sentCainReqMsgSignal;
    simsignal_t recCainRespMsgSignal;
    simsignal_t sentCainRespMsgSignal;
    simsignal_t recCainHopMsgSignal;
    simsignal_t sentCainHopMsgSignal;
    simsignal_t recCainErrMsgSignal;
    simsignal_t sentCainErrMsgSignal;
    simsignal_t sentCainRREQMsgSignal;
    simsignal_t recCainRREQMsgSignal;
    simsignal_t sentCainRREPMsgSignal;
    simsignal_t recCainRREPMsgSignal;
    simsignal_t recCainRREQFwdMsgSignal;
    simsignal_t sentCainRREQFwdMsgSignal;
    simsignal_t recLarMsgSignal;
    simsignal_t sentLarMsgSignal;
    simsignal_t distSignal;
    simsignal_t timeSignal;
    simsignal_t powerThreshSignal;
    simsignal_t batteryDecaySignal;
    simsignal_t recSprMsgSignal;
    simsignal_t sentSprMsgSignal;
    simsignal_t recBrapMsgSignal;
    simsignal_t sentBrapMsgSignal;
    simsignal_t nodeEndingSignal;
    simsignal_t hopCountSignal;
    simsignal_t sendProbSignal;
    simsignal_t distMapSizeSignal;
    simsignal_t respMapSizeSignal;
    simsignal_t recWeightMsgSignal;
    simsignal_t recAntennaMsgSignal;
    simsignal_t sentAntennaMsgSignal;
    simsignal_t recFwdAntennaMsgSignal;
    simsignal_t recDroneMsgSignal;
    simsignal_t recSatMsgSignal;
    simsignal_t droneDistSignal;
    simsignal_t satDistSignal;
    long numConnectedDevs = 0;
    long cainMsg = 0;
    long recCainFwdMsg = 0;
    long sentCainFwdMsg = 0;
    long recCainReqMsg = 0;
    long sentCainReqMsg = 0;
    long recCainRespMsg = 0;
    long sentCainRespMsg = 0;
    long recCainHopMsg = 0;
    long sentCainHopMsg = 0;
    long recCainErrMsg = 0;
    long sentCainErrMsg = 0;
    long sentCainRREQMsg = 0;
    long recCainRREQMsg = 0;
    long sentCainRREPMsg = 0;
    long recCainRREPMsg = 0;
    long recCainRREQFwdMsg = 0;
    long sentCainRREQFwdMsg = 0;
    long sentLarMsg = 0;
    long recLarMsg = 0;
    long recSprMsg = 0;
    long sentSprMsg = 0;
    long recBrapMsg = 0;
    long sentBrapMsg = 0;
    double dist = 0;
    simtime_t delay = 0;
    long powerThreshSig=0;
    long batteryDecay=0;
    long nodeEnd=0;
    long msgHops=0;
    long sendProb=0;
    long distMapSize=0;
    long respMapSize=0;
    long recWeightMsg=0;
    long recAntennaMsg=0;
    long sentAntennaMsg=0;
    long recFwdAntennaMsg=0;
    long recDroneMsg=0;
    long recSatMsg=0;
    double droneDist = 0;
    double satDist = 0;

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

    double calculateDnnDist(int state, double dist, std::string rl_type);

    // context
    IL3AddressType *addressType = nullptr;    // to support both Ipv4 and v6 addresses.

    // environment
    cModule *host = nullptr;
    IRoutingTable *routingTable = nullptr;
    IInterfaceTable *interfaceTable = nullptr;
    INetfilter *networkProtocol = nullptr;
    UdpSocket socket;
    bool usingIpv6 = false;

    //ch definition
    simtime_t chTimer; //timer for sending ch info message
    simtime_t chDef; //timer for electing the CH
    simtime_t routingStart; //timer for start the routing protocol

    // WirelessRouting parameters: the following parameters are configurable, see the NED file for more info.
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

    std::map<L3Address, int>* neighborBattery;
    L3Address antennaAddr; //address from the antenna
    L3Address droneAddr; //address from last drone in range
    L3Address satelliteAddr; //address from last satellite in range

    // self messages
    cMessage *helloMsgTimer = nullptr;    // timer to send hello messages (only if the feature is enabled)
    cMessage *expungeTimer = nullptr;    // timer to clean the routing table out
    cMessage *counterTimer = nullptr;    // timer to set rrerCount = rreqCount = 0 in each second
    cMessage *rrepAckTimer = nullptr;    // timer to wait for RREP-ACKs (RREP-ACK timeout)
    cMessage *blacklistTimer = nullptr;    // timer to clean the blacklist out
    cMessage *chInfo = nullptr;        //timer to exchange CH information
    cMessage *chElection = nullptr;     //timer to start ch election
    cMessage *chReset = nullptr;     //timer to reset the ch addres due to inactivity
    cMessage *cainTrigger = nullptr;    //timer to start cain messages
    cMessage *cainNotAck = nullptr;     //resend a not acked message
    cMessage *cainFwdTimer = nullptr;  //timer to wait for check which device to send a fwd message
    cMessage *conncetedDevTimer = nullptr; //timer to update the connected device to a ch
    cMessage *cainAck = nullptr;
    cMessage *endTimer = nullptr;    // timer to check simulations end
    cMessage *antennaTimer = nullptr; //timer for antenna start operating
    cMessage *droneTimer = nullptr; //timer for antenna start operating
    cMessage *sendFlWeights = nullptr; //timer for send the FL weights for CH or antenna
    cMessage *sendFlAvgWeights = nullptr; //timer for send the FL weights by CH or antenna
    cMessage *leachChDecision = nullptr; //timer for the nodes to start the CH decision

    // lifecycle
    simtime_t rebootTime;    // the last time when the node rebooted

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
//
//    /* Control packet creators */
    const Ptr<SNOOPHB> createSnoopMsg();
    const Ptr<RESPHB> createRespHBMsg(L3Address dest);
    const Ptr<CAINMSG> createCainMsg();
    const Ptr<CAINMSG> createCainRespMsg(L3Address dest, L3Address originator);
    const Ptr<CAINMSG> createCainFwdMsg(L3Address dest);
    const Ptr<CAINMSG> createCainReqMsg(L3Address dest);
    const Ptr<CAINMSG> createCainHopMsg(L3Address dest);
    const Ptr<CAINMSG> createCainErrMsg(L3Address dest, L3Address originator);
    const Ptr<CAINMSG> createCainAck(L3Address dest,heartBeatType cainMsgType,int seqNum);
    const Ptr<CAINMSG> createAckTimer(heartBeatType cainMsgType,int seqNum);
    const Ptr<CAINMSG> createCainRREQ();
    const Ptr<CAINMSG> createSCMSG();
    const Ptr<CAINMSG> createCainRREP(L3Address nextHop,L3Address rreqDest,L3Address cainSource
            ,int battery);
    const Ptr<CAINMSG> createLARMSG();
    const Ptr<CAINMSG> createSPRAYMSG(int numNodes);
    const Ptr<CAINMSG> createBRAPMSG();
    const Ptr<DRONEMSG> createDroneMsg();
    const Ptr<ANTENNA> createAntennaMsg();
    const Ptr<FLWEIGHT> createWeightMsg(std::vector<float>* weights);
//    const Ptr<RrepAck> createRREPACK();
    const Ptr<SNOOPHB> createHelloMessage();
//    const Ptr<Rreq> createRREQ(const L3Address& destAddr);
//    const Ptr<Rrep> createRREP(const Ptr<Rreq>& rreq, IRoute *destRoute, IRoute *originatorRoute, const L3Address& sourceAddr);
//    const Ptr<Rrep> createGratuitousRREP(const Ptr<Rreq>& rreq, IRoute *originatorRoute);
    const Ptr<Rerr> createRERR(const std::vector<UnreachableNode>& unreachableNodes);
    L3Address findHopRL();
    const Ptr<CHDEF> createChDefMsg();
//
    /* Control Packet handlers */
    void handleSnooping(const Ptr<SNOOPHB>& snoop, const L3Address& sourceAddr);
    void handleLeachMsg(const Ptr<CHDEF>& leach);
    void handleResp(const Ptr<RESPHB>& resp);
    void handleCainFWD(const Ptr<CAINMSG>& cainmsg);
    void handleCainREQ(const Ptr<CAINMSG>& cainmsg);
    void handleCainRESP(const Ptr<CAINMSG>& cainmsg);
    void handleCainHOP(const Ptr<CAINMSG>& cainmsg);
    void handleCainERR(const Ptr<CAINMSG>& cainmsg);
    void handleCainACK(const Ptr<CAINMSG>& cainmsg);
    void handleFwdTimer();
    void handleCainRREQ(const Ptr<CAINMSG>& cainmsg);
    void handleCainRREP(const Ptr<CAINMSG>& cainmsg);
    void handleSCMSG(const Ptr<CAINMSG>& cainmsg);
    void handleCainLAR(const Ptr<CAINMSG>& cainmsg);
    void handleCainSPR(const Ptr<CAINMSG>& cainmsg);
    void handleCainBRAP(const Ptr<CAINMSG>& cainmsg);
    void handleCainReply(const Ptr<CAINMSG>& cainmsg);
    void handleCainHopCount(const Ptr<CAINMSG>& cainmsg);
    void handleAntennaMsg(const Ptr<ANTENNA>& antennaMsg);
    void handleDroneMsg(const Ptr<DRONEMSG>& droneMsg);
    void handleWeightMsg(const Ptr<FLWEIGHT>& antennaMsg);
    void recLeachMsg(L3Address neighAddr, const Ptr<SNOOPHB>& snoop);
    void recLeachRespMsg(const Ptr<RESPHB>& respMsg);
    void chDecision();
    void resetLeachCalculation();
//    void handleRREQ(const Ptr<Rreq>& rreq, const L3Address& sourceAddr, unsigned int timeToLive);
//    void handleRERR(const Ptr<const Rerr>& rerr, const L3Address& sourceAddr);
//    void handleHelloMessage(const Ptr<Rrep>& helloMessage);
//    void handleRREPACK(const Ptr<const RrepAck>& rrepACK, const L3Address& neighborAddr);
//
//    /* Control Packet sender methods */
    void sendSnooping(const Ptr<SNOOPHB>& snoop, unsigned int timeToLive);
    void sendResp(const Ptr<RESPHB>& resp, const L3Address& destAddr, unsigned int timeToLive);
    void sendCainMsg(const Ptr<CAINMSG>& cainmsg, unsigned int timeToLive,double delay);
    void sendSprayMsg(const Ptr<CAINMSG>& cainMsg);
//    void sendRREPACK(const Ptr<RrepAck>& rrepACK, const L3Address& destAddr);
//    void sendRREP(const Ptr<Rrep>& rrep, const L3Address& destAddr, unsigned int timeToLive);
//    void sendGRREP(const Ptr<Rrep>& grrep, const L3Address& destAddr, unsigned int timeToLive);
//
//    /* Control Packet forwarders */
//    void forwardRREP(const Ptr<Rrep>& rrep, const L3Address& destAddr, unsigned int timeToLive);
//    void forwardRREQ(const Ptr<Rreq>& rreq, unsigned int timeToLive);

    void updateBestHop(L3Address srcAddr);
    void updateLarBestHop(L3Address srcAddr, Coord senderCoord);

    void calcDelayMean(simtime_t msgInit);
//
    void updateConnectedDevs();
    int getState(int currState,bool reward);
    int get_coverage_state(L3Address cain_dest);
    int get_drone_coverage_state(L3Address cain_dest);
    void calculate_coverage_reward(int state,bool decision,L3Address cain_dest);
    void calculate_drone_coverage_reward(int state,bool decision,L3Address cain_dest);
    void updateState(int currState, int newState, bool decision);
    void updatePowerThreshold(int state);
    bool sendMessageML(int state);
    void create_reward_matrix();
    void calculate_q_matrix();
    void calculate_drone_q_matrix();
    int calculateDnnDecision(L3Address cainDest);
    bool calculateDroneDecision(L3Address cainDest);

    double backoffTimer();
    double cainBackoff();
    bool findFwdDest(L3Address cainDestAddr);

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
    WirelessRouting();
    virtual ~WirelessRouting();
};

} /* namespace wirelessrouting */
} /* namespace  inet*/
#endif /* INET_ROUTING_SIXGEN_WIRELESSROUTING_H_ */
