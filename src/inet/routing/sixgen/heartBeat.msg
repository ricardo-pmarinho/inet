//
// Copyright (C) 2014 OpenSim Ltd.
// Author: Benjamin Seregi
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

import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import inet.common.packet.Packet;
import inet.networklayer.common.L3Address;
import inet.common.geometry.Geometry;

cplusplus{{
//#include "inet/common/Units.h"
#include "inet/common/geometry/common/Coord.h"
}}

namespace inet::wirelessrouting;

//class noncobject Coord;

enum heartBeatType
{
    SNP = 1;
    RESP = 2;
    CAINREQ = 3;
    CAINRESP = 4;
    CAINFWD = 5;
    CAINHOP = 6;
    CAINERR = 7;
    CAINACK = 8;
    RREQ = 9;
    RREP = 10;
    SCMSG = 11;
    LAR = 12;
    SPR = 13;
    BRAP = 14;
    NEWFWD= 15;
    CAINREPLY = 16;
    HOPCOUNT = 17;
    ANTN = 18;
    WGHT = 19;
    LEACH = 20;
    DRONE = 21;
    SNP_IPv6 = 101;
    RESP_IPv6 = 102;
    CAINREQ_IPv6 = 103;
    CAINRESP_IPv6 = 104;
    CAINFWD_IPv6 = 105;
    CAINHOP_IPv6 = 106;
    CAINERR_IPv6 = 107;
    CAINACK_IPv6 = 108;
    RREQ_IPv6 = 109;
    RREP_IPv6 = 110;
    SCMSG_IPv6 = 111;
    LAR_IPv6 = 112;
    SPR_IPv6 = 113;
    BRAP_IPv6 = 114;
    NEWFWD_IPv6= 115;
    CAINREPLY_IPv6 = 116;
    HOPCOUNT_IPv6 = 117;
    ANTN_IPv6 = 118;
    WGHT_IPv6 = 119;
    LEACH_IPv6 = 120;
    DRONE_IPv6 = 121;
    def = 99;
};

class HeartBeat extends FieldsChunk{
    heartBeatType packetType = static_cast<heartBeatType>(-1);       // packet type, stored in one byte
}

class SNOOPHB extends HeartBeat{
    // chunkLength = B(24) or B(48)
    // packetType = RREQ or RREQ_IPv6
    bool joinFlag;    // Join flag; reserved for multicast.
    bool repairFlag;    // Repair flag; reserved for multicast.
    bool gratuitousRREPFlag;    // Gratuitous RREP flag; indicates whether a gratuitous RREP should be unicast to the node specified in the Destination IP Address field
    bool twoHop;    // Flag for the node to know if the message is a two hop message in CH election
    bool unknownSeqNumFlag;    // Unknown sequence number; indicates the destination sequence number is unknown
    uint16_t reserved = 0;    // Sent as 0; ignored on reception.
    unsigned int hopCount;    // The number of hops from the Originator IP Address to the node handling the request.
    uint32_t rreqId;    // A sequence number uniquely identifying the particular RREQ when taken in conjunction with the originating node's IP address.
    L3Address destAddr;    // The IP address of the destination for which a route is desired.
    uint32_t destSeqNum;    // The latest sequence number received in the past by the originator for any route towards the destination.
    L3Address originatorAddr;    // The IP address of the node which originated the Route Request.
    uint32_t originatorSeqNum;    // The current sequence number to be used in the route entry pointing towards the originator of the route request.
    Coord msgCoord;
    uint32_t batteryPercent;
    L3Address neighbAddr; //address from the two hop node
    Coord neighbMsgCoord; //Coordinate from the two hop node
    uint32_t neighbBatteryPercent; //battery from the two hop node
    double chDist;//stores the distance between sender its CH
    string nodeName;
}

class FLWEIGHT extends HeartBeat{
    L3Address destAddr;
    L3Address sourceAddr;
    float w11;
    float w12;
    float w13;
    float w21;
    float w22;
    float w23;
    float w31;
    float w32;
    float w33;
    float wo1;
    float wo2;
    float wo3;
}

class DRONEMSG extends HeartBeat{
    unsigned int hopCount;
    L3Address destAddr;
    L3Address sourceAddr;
    Coord senderCoord;
}

class ANTENNA extends HeartBeat{
    unsigned int hopCount;
    L3Address destAddr;
    L3Address sourceAddr;
}

class CHDEF extends HeartBeat{
    L3Address sourceAddr;
    Coord senderCoord;
}

class RESPHB extends HeartBeat{
    unsigned int hopCount;
    L3Address destAddr;
    L3Address sourceAddr;
    L3Address chAddr;
    L3Address originatorAddr;
    uint32_t batteryPercent;
    Coord senderCoord;
}

class CAINMSG extends HeartBeat{
    unsigned int hopCount;
    L3Address destAddr;
    L3Address cainDestAddr;
    L3Address originatorAddr;
    L3Address sourceAddr;
    L3Address chAddr;
    L3Address lastAddr;
    L3Address rrepSource;
    heartBeatType ackType = static_cast<heartBeatType>(-1); 
    uint32_t ackSeqNum;
    uint32_t seqNum;
    uint32_t batteryPercent;
    uint32_t chBattery;
    Coord senderCoord;
    uint32_t sprayQtdNeigh;
    uint32_t centrality;
    unsigned int hops;
    string msgId;
    double distance;//stores the distance between sender and receiver (necessary?)
    simtime_t timeInit;
}

class Rrep extends HeartBeat{
    unsigned int heartBeatType = 99;
    unsigned int hopCount;
    unsigned int rreqId;
    L3Address destAddr;
    unsigned int destSeqNum;
    L3Address originatorAddr;
    unsigned int originatorSeqNum;    
}

class Rreq extends HeartBeat{
    unsigned int heartBeatType = 99;
    unsigned int hopCount;
    unsigned int rreqId;
    L3Address destAddr;
    unsigned int destSeqNum;
    L3Address originatorAddr;
    unsigned int originatorSeqNum;    
}

//
// Represents an AODV Route Error
//
class Rerr extends HeartBeat
{
    // chunkLength = B(4 + N * (4+4)) or B(4 + N * (4+16))
    // packetType = RERR or RERR_IPv6
    bool noDeleteFlag;    // No delete flag; set when a node has performed a local repair of a link, and upstream nodes should not delete the route.
    uint16_t reserved = 0;    // Sent as 0; ignored on reception.
    UnreachableNode unreachableNodes[];    // The unreachable destinations included in the message; MUST be at least 1.
}

class RrepAck extends HeartBeat{
    unsigned int heartBeatType = 99;
    unsigned int hopCount;
    unsigned int rreqId;
    L3Address destAddr;
    unsigned int destSeqNum;
    L3Address originatorAddr;
    unsigned int originatorSeqNum;    
}

//
// Represents an internal timer for a Route Reply packet in Aodv module
//
message WaitForRrep
{
    L3Address destAddr;
    unsigned int lastTTL;
    bool fromInvalidEntry;
}


//
// Represents a timer for delayed sending
//
message PacketHolderMessage
{
    Packet *ownedPacket @owned;
}
struct UnreachableNode
{
    L3Address addr;    // The IP address of the destination that has become unreachable due to a link break.
    uint32_t seqNum;    // The sequence number in the route table entry for the destination listed in the previous Unreachable Destination IP Address field.
};
