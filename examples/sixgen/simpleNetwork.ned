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

package inet.examples.sixgen;

import inet.node.sixgen.sixgenNode;
import inet.node.sixgen.droneNode;
import inet.node.sixgen.satelliteNode;
import inet.node.sixgen.AntennaNode;
import inet.node.sixgen.CentralNode;
import inet.node.sixgen.irsNode;

import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.physicallayer.unitdisk.UnitDiskRadioMedium;
import inet.visualizer.integrated.IntegratedVisualizer;
import inet.common.oracle.Oracle;
import inet.environment.common.PhysicalEnvironment;
import ned.DatarateChannel;

network simpleNetwork
{
    parameters:
        int numOfSats = default(2); // Number of satellites
        int numHost = default(2);
        int numDrone = default(2);
        int numIrs = default(2);
        int numAntenna = default(1);
        int sprayFraction = default(10);
        string networkType;
        bool backoffEnabled;
        bool mlEnable;
        bool gatEnable = default(true);
        string rl_type;
        int mlThreshold = default(300);
        double alphaRl = default(0.5);
        bool irsEnable = default(false);
    types:
        channel Ether1000m extends DatarateChannel
        {
            datarate = 1000Mbps;
            delay = 0.1us;
        }
    submodules:
        irs[numIrs]: irsNode {
            parameters:
                @display("p=316,269");
        }
        host[numHost]: sixgenNode {
            parameters:
                @display("p=429,269");
        }
        antenna[numAntenna]: AntennaNode {
            parameters:
                @display("p=282,183;i=device/antennatower");
        }
        satellite[numOfSats]: satelliteNode {
            parameters:
                @display("p=430,43;r=10,,#707070;i=device/satellite_l");
        }
        drone[numDrone]: droneNode {
            @display("i=misc/drone;p=430,166");
        }
        //        central: CentralNode { // Adicionando o centralNode
        //            @display("p=150,183;i=device/server");
        //        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=580,425");
        }
        Oracle: Oracle {
            parameters:
                @display("p=100,269;is=s");
        }
        visualizer: IntegratedVisualizer {
            parameters:
                @display("p=100,30;is=s");
        }
        radioMedium: UnitDiskRadioMedium {
            parameters:
                @display("p=99,128;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                addDefaultRoutes = false;
                addStaticRoutes = false;
                addSubnetRoutes = false;
                //config = xml("<config><interface hosts='*' address='145.236.x.x' netmask='255.255.0.0'/></config>");
                @display("p=100,83;is=s");
        }
        routingTableRecorder: RoutingTableRecorder {
            parameters:
                @display("p=100,175;is=s");
        }
        scenarioManager: ScenarioManager {
            parameters:
                script = default(xml("<scenario/>"));
                @display("p=100,221;is=s");
        }
}
