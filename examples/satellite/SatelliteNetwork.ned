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
package inet.examples.satellite;

import inet.node.inet.StandardHost;
import inet.mobility.single.ConstSpeedMobility;
import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.physicallayer.common.packetlevel.RadioMedium;

network SatelliteNetwork
{
    parameters:
        int numSatellites = default(3);
        int numGroundStations = default(2);

    submodules:
        radioMedium: RadioMedium {
            @display("p=100,100");
        }

        groundStation[numGroundStations]: StandardHost {
            @display("p=200,300+100*i");
        }

        satellite[numSatellites]: StandardHost {
            @display("p=400,100+100*i");
        }
}