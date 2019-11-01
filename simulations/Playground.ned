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

package merrygoround.simulations;

import merrygoround.Entry;
import merrygoround.Exit;
import merrygoround.MGR;

network Playground
{
    @display("bgb=369,261");
    submodules:
        entry: Entry {
            @display("p=40,132");
        }
        exit: Exit {
            @display("p=300,132");
        }
        mgr: MGR {
            @display("p=165,132");
        }
    connections:
        entry.out --> {  delay = 100ms; } --> mgr.child_in;
        mgr.child_out --> {  delay = 100ms; } --> exit.in;
}

