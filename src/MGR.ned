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

module MGR
{
    @display("bgb=339,287");
    gates:
        input child_in;
        output child_out;
    submodules:
        in_mgr: IN_MGR {
            @display("p=183,104");
        }
        owner: Owner {
            @display("p=183,206");
        }
    connections:
        child_in --> in_mgr.in;
        in_mgr.out --> child_out;
        in_mgr.notify --> owner.in;
        owner.out --> in_mgr.command;
}
