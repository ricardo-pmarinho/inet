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

package inet.common.oracle;

simple Oracle{
    parameters:
        @display("i=block/cogwheel");
        string name="Oracle module";
        
        int searchTimes = default(3); //number of times to search for a cain dest
        
        
        @signal[numChSignal](type=long);
        @statistic[numChSignal](title="Number of elected CH";record=vector,count,max,last;interpolationmode=none);
        
        @signal[numSemiChSignal](type=long);
        @statistic[numSemiChSignal](title="Number of semi CH";record=vector,count,max,last;interpolationmode=none);
       
        @signal[numActiveChSignal](type=long);
        @statistic[numActiveChSignal](title="Number of actives CH";record=vector,count,max,last;interpolationmode=none);
        
        @signal[numActiveSemiChSignal](type=long);
        @statistic[numActiveSemiChSignal](title="Number of actives semi CH";record=vector,count,max,last;interpolationmode=none);
        @signal[numActiveFullChSignal](type=long);
        @statistic[numActiveFullChSignal](title="Number of actives full CH";record=vector,count,max,last;interpolationmode=none);
        @signal[numNoChSignal](type=long);
        @statistic[numNoChSignal](title="Number devices not connected to a CH";record=vector,count,max,last;interpolationmode=none);
        
        
        @signal[chUpgradeSignal](type=long);
        @statistic[chUpgradeSignal](title="Number of upgraded CH";record=vector,count,max,last;interpolationmode=none);
        @signal[chDowngradeSignal](type=long);
        @statistic[chDowngradeSignal](title="Number of downgraded CH";record=vector,count,max,last;interpolationmode=none);
        
        @signal[simulationEndSignal](type=long);
        @statistic[simulationEndSignal](title="Time that the simulation ended";record=last;interpolationmode=none);
        
        @signal[startNodeSignal](type=long);
        @statistic[startNodeSignal](title="Number of nodes that started";record=last;interpolationmode=none);
        
}	
