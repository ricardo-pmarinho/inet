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

package inet.mobility.single;

import inet.mobility.base.MovingMobilityBase;
//
// Controls all movement related things of a host
//
// ~ConstSpeedMobility does not use one of the standard mobility approaches.
// The user can define a velocity for each Host and an update interval. If
// the velocity is greater than zero (i.e. the Host is not stationary) the
// ~ConstSpeedMobility module calculates a random target position for the Host.
// Every update interval ~ConstSpeedMobility calculates the new position on its
// way to the target position and updates the display. Once the target position
// is reached ~ConstSpeedMobility calculates a new target position.
//
// This component has been taken over from Mobility Framework 1.0a5.
//
// @author Steffen Sroka, Marc Loebbers, Daniel Willkomm
//
simple ConstSpeedMobility extends MovingMobilityBase
{
    parameters:
        double speed @unit(mps); // speed of the host
        double initialX @unit(m) = default(uniform(constraintAreaMinX, constraintAreaMaxX));
        double initialY @unit(m) = default(uniform(constraintAreaMinY, constraintAreaMaxY));
        double initialZ @unit(m) = default(nanToZero(uniform(constraintAreaMinZ, constraintAreaMaxZ)));
        bool initFromDisplayString = default(true);
        @class(ConstSpeedMobility);
}