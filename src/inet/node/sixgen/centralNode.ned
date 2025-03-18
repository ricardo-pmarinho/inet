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

import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.ethernet.EtherMac; // Importação necessária

module CentralNode extends StandardHost {
    parameters:
        @class(CentralNode);
        @display("p=150,150");
        eth[*].typename = default("EthernetInterface");
        eth[*].mac.typename = default("EtherMac");
        eth[*].queue.typename = default("DropTailQueue");
        routing.typename = default("Ipv4Routing");
        forwarding = default(true);
    gates:
        input socketIn;  // Porta de entrada para mensagens
    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,50");
        }
}