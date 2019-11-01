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

package merrygoround;

//
// TODO auto-generated module
//
simple Entry
{
    parameters:
        volatile double meanInterArrival @unit(s) = default(1.5s);
        volatile double Q @unit(s) = default(4s);
        volatile bool burstArrival = default(false);
        @signal[generated](type="int");
        @statistic[number_of_child](title="children at once"; source="generated"; record=vector, stats; intepolationmode=none);
    gates: 
        output out;
}
