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

package inet.routing.sixgen;

import inet.applications.contract.IApp;

simple wirelessRouting like IApp
{
    parameters:
        @class("wirelessrouting::WirelessRouting");
        @display("i=block/network2");
        string routingTableModule = default("^.ipv4.routingTable");
        string interfaceTableModule = default("^.interfaceTable");
        string networkProtocolModule = default("^.ipv4.ip");
        bool askGratuitousRREP = default(false); // see RFC 3561: 6.6.3
        bool useHelloMessages = default(false); // see RFC 3561: 6.9
        bool useLocalRepair = default(false); // see RFC 3561: 6.12 *not implemented yet*
        bool destinationOnlyFlag = default(false); // see RFC 3561: 5.1
        int udpPort = default(654);
        string interface = default("wlan0");

        double maxPeriodicJitter @unit(s) = default(helloInterval / 4); // it MUST NOT be negative; it MUST NOT be greater than MESSAGE_INTERVAL/2; it SHOULD NOT be greater than MESSAGE_INTERVAL/4.
        volatile double periodicJitter @unit(s) = default(uniform(0s, maxPeriodicJitter)); // jitter for externally triggered message generation and message forwarding

        // RFC 5148:
        // need more revise: As well as the decision as to whether
        // to use jitter being dependent on the medium access control and
        // lower layers, the selection of the MAXJITTER parameter SHOULD
        // be appropriate to those mechanisms.
        double maxJitter @unit(s) = default(5ms);
        volatile double jitter @unit(s) = default(uniform(0ms, maxJitter)); // jitter for broadcasts

        double helloInterval @unit(s) = default(1s); // every helloInterval seconds a node broadcasts Hello messages (if it is necessary)
        int allowedHelloLoss = default(2); // allowedHelloLoss * helloInterval is the lifetime value for Hello messages
        double activeRouteTimeout @unit(s) = default(3s); // the timeout value for cached routes If Hello messages are used, then the
                                                            // ACTIVE_ROUTE_TIMEOUT parameter value MUST be more than the value
                                                            // (ALLOWED_HELLO_LOSS * HELLO_INTERVAL).
		double chTimer @unit(s) = default(2s);
		double chDef @unit(s) = default(chTimer+0.5s);
		int powerThresh = default(10);
		int batteryThresh = default(70);
		
        int netDiameter = default(35); // the maximum possible number of hops between two nodes in the network
        double nodeTraversalTime @unit(s) = default(0.04s); // an estimation of the average one-hop traversal time
        int rerrRatelimit = default(10); // maximum number of RERR messages that the AODV may originate in 1s.
        int rreqRetries = default(2); // specifies the number of times AODV will repeat an expanded ring search for a destination
        int rreqRatelimit = default(10); // maximum number of RREQ messages that the AODV may originate in 1s.
        int timeoutBuffer = default(2); // plus time to wait for a delayed RREP (due to congestion) (to omit this buffer set it to 0)
        int ttlStart = default(2); // specifies the TTL value when initiating a route request
        int ttlIncrement = default(2); // specifies the value by which the TTL will be incremented each time a RREQ is retransmitted
        int ttlThreshold = default(7); // the maximum value of TTL over which NET_DIAMETER value will be used to broadcast any RREQ
        int localAddTTL = default(2); // it is used by the formula which calculates the initial TTL of the RREQ for a local repair

        double myRouteTimeout @unit(s) = default(2 * activeRouteTimeout); // the value of the lifetime field that a destination node places in RREPs
        double deletePeriod @unit(s) = default(5 * max(activeRouteTimeout, helloInterval)); // the time after which an expired route is deleted
        double blacklistTimeout @unit(s) = default(rreqRetries * netTraversalTime); // the time after which a blacklisted node is removed from the blacklist
        double netTraversalTime @unit(s) = default(2 * nodeTraversalTime * netDiameter); // an estimation of the traversal time for the complete network
        double nextHopWait @unit(s) = default(nodeTraversalTime + 0.01s); // timeout for a RREP-ACK
        double pathDiscoveryTime @unit(s) = default(2 * netTraversalTime); // buffer timeout for each broadcasted RREQ message
       
        @signal[connectedDevsSignal](type=long);
        @statistic[connectedDevsSignal](title="Number of connected devices to a CH";record=vector,count,max,last;interpolationmode=none);
        
        @signal[cainMsgSignal](type=long);
        @statistic[cainMsgSignal](title="Number of CAIN messages received";record=count,max,last;interpolationmode=none);
        
        @signal[recCainFwdMsgSignal](type=long);
        @statistic[recCainFwdMsgSignal](title="Number of CAIN FWD message received";record=mean,vector,count,max,last;interpolationmode=none);
        @signal[sentCainFwdMsgSignal](type=long);
        @statistic[sentCainFwdMsgSignal](title="Number of CAIN FWD message sent";record=vector,count,max,last;interpolationmode=none);
        
        @signal[sentCainReqMsgSignal](type=long);
        @statistic[sentCainReqMsgSignal](title="Number of CAIN REQ messages sent";record=vector,count,max,last;interpolationmode=none);
        @signal[recCainReqMsgSignal](type=long);
        @statistic[recCainReqMsgSignal](title="Number of CAIN REQ messages received";record=vector,count,max,last;interpolationmode=none);
        
        @signal[sentCainRespMsgSignal](type=long);
        @statistic[sentCainRespMsgSignal](title="Number of CAIN RESP messages sent";record=vector,count,max,last;interpolationmode=none);
        @signal[recCainRespMsgSignal](type=long);
        @statistic[recCainRespMsgSignal](title="Number of CAIN RESP messages received";record=vector,count,max,last;interpolationmode=none);
        
        @signal[sentCainHopMsgSignal](type=long);
        @statistic[sentCainHopMsgSignal](title="Number of CAIN HOP messages sent";record=vector,count,max,last;interpolationmode=none);
        @signal[recCainHopMsgSignal](type=long);
        @statistic[recCainHopMsgSignal](title="Number of CAIN HOP messages received";record=vector,count,max,last;interpolationmode=none);
        
        @signal[sentCainErrMsgSignal](type=long);
        @statistic[sentCainErrMsgSignal](title="Number of CAIN ERR messages sent";record=vector,count,max,last;interpolationmode=none);
        @signal[recCainErrMsgSignal](type=long);
        @statistic[recCainErrMsgSignal](title="Number of CAIN ERR messages received";record=vector,count,max,last;interpolationmode=none);
        
        @signal[sentCainRREQMsgSignal](type=long);
        @statistic[sentCainRREQMsgSignal](title="Number of CAIN RREQ messages sent";record=count,max,last;interpolationmode=none);
        @signal[recCainRREQMsgSignal](type=long);
        @statistic[recCainRREQMsgSignal](title="Number of CAIN RREQ messages received";record=count,max,last;interpolationmode=none);
        
        @signal[sentCainRREPMsgSignal](type=long);
        @statistic[sentCainRREPMsgSignal](title="Number of CAIN RREP messages sent";record=count,max,last;interpolationmode=none);
        @signal[recCainRREPMsgSignal](type=long);
        @statistic[recCainRREPMsgSignal](title="Number of CAIN RREP messages received";record=count,max,last;interpolationmode=none);
           
        @signal[recCainRREQFwdMsgSignal](type=long);
        @statistic[recCainRREQFwdMsgSignal](title="Number of CAIN RREQFWD messages received";record=count,max,last;interpolationmode=none);
        
        @signal[sentCainRREQFwdMsgSignal](type=long);
        @statistic[sentCainRREQFwdMsgSignal](title="Number of CAIN RREQFWD messages sent";record=count,max,last;interpolationmode=none);
        
        @signal[recLarMsgSignal](type=long);
        @statistic[recLarMsgSignal](title="Number of CAIN LAR messages received";record=count,max,last;interpolationmode=none);
        
        @signal[sentLarMsgSignal](type=long);
        @statistic[sentLarMsgSignal](title="Number of CAIN LAR messages sent";record=count,max,last;interpolationmode=none);
        
        @signal[recSprMsgSignal](type=long);
        @statistic[recSprMsgSignal](title="Number of CAIN SPRAY messages received";record=count,max,last;interpolationmode=none);
        
        @signal[sentSprMsgSignal](type=long);
        @statistic[sentSprMsgSignal](title="Number of CAIN SPRAY messages sent";record=count,max,last;interpolationmode=none);
        
        @signal[recBrapMsgSignal](type=long);
        @statistic[recBrapMsgSignal](title="Number of CAIN BRAP messages received";record=count,max,last;interpolationmode=none);
        
        @signal[sentBrapMsgSignal](type=long);
        @statistic[sentBrapMsgSignal](title="Number of CAIN BRAP messages sent";record=count,max,last;interpolationmode=none);
        
        @signal[distSignal](type=double);
        @statistic[distSignal](title="Distance from sender to destination";record=count,max,last;interpolationmode=none);
        
        @signal[timeSignal](type=double);
        @statistic[timeSignal](title="delay";record=count,max,last;interpolationmode=none);
        
        @signal[powerThreshSignal](type=long);
        @statistic[powerThreshSignal](title="Power thresh";record=count,max,last;interpolationmode=none);
        
        @signal[batteryDecaySignal](type=long);
        @statistic[batteryDecaySignal](title="Battery decay";record=vector,count,max,last;interpolationmode=none);
        
        @signal[nodeEndingSignal](type=long);
        @statistic[nodeEndingSignal](title="Node end";record=vector,count,max,last;interpolationmode=none);
        
        @signal[hopCountSignal](type=long);
        @statistic[hopCountSignal](title="hop count";record=vector,count,max,last;interpolationmode=none);
        
        @signal[sendProbSignal](type=long);
        @statistic[sendProbSignal](title="Send probability";record=vector,count,max,last;interpolationmode=none);
        
        @signal[distMapSizeSignal](type=long);
        @statistic[distMapSizeSignal](title="distMapSizeSignal";record=vector,count,max,last;interpolationmode=none);
        
        @signal[respMapSizeSignal](type=long);
        @statistic[respMapSizeSignal](title="respMapSizeSignal";record=vector,count,max,last;interpolationmode=none);
        
        @signal[recWeightMsgSignal](type=long);
        @statistic[recWeightMsgSignal](title="received weight message";record=vector,count,max,last;interpolationmode=none);
        
        @signal[recAntennaMsgSignal](type=long);
        @statistic[recAntennaMsgSignal](title="received antenna message";record=vector,count,max,last;interpolationmode=none);
        @signal[sentAntennaMsgSignal](type=long);
        @statistic[sentAntennaMsgSignal](title="sent antenna message";record=vector,count,max,last;interpolationmode=none);
        
        @signal[recFwdAntennaMsgSignal](type=long);
        @statistic[recFwdAntennaMsgSignal](title="sent antenna message";record=vector,count,max,last;interpolationmode=none);
        
        @signal[recDroneMsgSignal](type=long);
        @statistic[recDroneMsgSignal](title="received fwd drone message";record=vector,count,max,last;interpolationmode=none);
        
        @signal[recSatMsgSignal](type=long);
        @statistic[recSatMsgSignal](title="received fwd sat message";record=vector,count,max,last;interpolationmode=none);
        
        @signal[droneDistSignal](type=double);
        @statistic[droneDistSignal](title="Distance from sender to drone";record=count,max,last;interpolationmode=none);
        
        @signal[satDistSignal](type=double);
        @statistic[satDistSignal](title="Distance from sender to satellite";record=count,max,last;interpolationmode=none);
    gates:
        input socketIn;
        output socketOut;
}