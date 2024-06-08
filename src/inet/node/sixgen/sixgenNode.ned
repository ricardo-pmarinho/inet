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

package inet.node.sixgen;

import inet.node.inet.WirelessHost;
import inet.routing.sixgen.wirelessRouting;

module sixgenNode extends WirelessHost{
    parameters:
        @display("i=device/cellphone");
        wlan[*].mgmt.typename = default("Ieee80211MgmtAdhoc");
        wlan[*].agent.typename = default("");
        forwarding = default(true);
	submodules:
		routing : wirelessRouting{
            @display("p=50,50");
        }
    connections:
        routing.socketOut --> at.in++;
        routing.socketIn <-- at.out++;
}