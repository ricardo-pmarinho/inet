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
import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.physicallayer.unitdisk.UnitDiskRadioMedium;
import inet.visualizer.integrated.IntegratedVisualizer;
//import inet.visualizer.integrated.IntegratedCanvasVisualizer;
//import inet.visualizer.base.SceneOsgVisualizerBase;
import inet.common.oracle.Oracle;
import inet.environment.common.PhysicalEnvironment;
//import inet.mobility.spatial.SpatialMobilityShowcase;


network simpleNetwork
{
    parameters:
        int numOfSats = default(2); // Number of satellites
        int numHost = default(2);
        int numDrone = default(2);
        int numAntenna = default(2);
        int sprayFraction = default(10);
        string networkType;
        bool backoffEnabled;
        bool mlEnable;
        string rl_type;
        int mlThreshold = default(300);
        double alphaRl = default(0.5);
    submodules:
        satellite[numOfSats]: sixgenNode {
            parameters:
                @display("p=430,43;r=10,,#707070;i=device/satellite_l");
        }
        //showcase: SpatialMobilityShowcase {
        //    @display("p=100,381");
        //}
        drone[numDrone]: sixgenNode {
            @display("i=misc/node_vs");
        }
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
//        visualizer: IntegratedCanvasVisualizer {
//            parameters:
//                @display("p=100,30;is=s");
//        }
        radioMedium: UnitDiskRadioMedium {
            parameters:
                @display("p=99,128;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                addDefaultRoutes = false;
                addStaticRoutes = false;
                addSubnetRoutes = false;
                config = xml("<config><interface hosts='*' address='145.236.x.x' netmask='255.255.0.0'/></config>");
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
        host[numHost]: sixgenNode {
            parameters:
                @display("p=300,300");
        }
        antenna[numAntenna]: sixgenNode {
            parameters:
                @display("p=300,150");
        }
    //        host0: sixgenNode {
    //            parameters:
    //                @display("p=175,300");
    //        }
    //        host1: sixgenNode {
    //            parameters:
    //                @display("p=300,500");
    //        }
    //        host2: sixgenNode {
    //            parameters:
    //                @display("p=300,100");
    //        }
    //        host3: sixgenNode {
    //            parameters:
    //                @display("p=500,300");
    //        }
    //        host4: sixgenNode {
    //            parameters:
    //                @display("p=700,300");
    //        }
    connections allowunconnected:
}
