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

package energysimulation;

import ned.IBidirectionalChannel;
import ned.DelayChannel;
import energysimulation.Txc20;
import energysimulation.Tictoc20;
import energysimulation.Channel;


//
// TODO documentation
//
// @author Andrew Hardy
//
network MyNetwork
{
    parameters:
        int PROPERTY1 = 1;
        int ROOM1 = 4;
        int UTILITY1 = 16;
        @display("bgb=793,602,white,#400040");
    types:
        channel Unnamed
        {
        }

    submodules:
        wash: Txc20 {
            @display("p=432,96;i=appliances/Washing-Machine");
            cost = 2;
        }
        monitor: Txc20 {
            @display("p=626,30;i=appliances/displayUnit");
            cost = 4;
            nodetype = "sink";
            datatype = "RECORD";
            dataname = 5;
        }
        ocsens: Txc20 {
            @display("p=83,249;i=appliances/sensor");
            scope = PROPERTY1 | ROOM1;
            cost = 12;
            nodetype = "source";
            datatype = "PUBLICATION";
            datascope = PROPERTY1 | ROOM1;
            dataname = 71;
        }
        TV: Txc20 {
            @display("p=20,276;i=appliances/tv");
            scope = PROPERTY1 | ROOM1;
            cost = 4;
            nodetype = "source";
            datatype = "RECORD";
            dataname = 5;
        }
        kett: Txc20 {
            @display("p=539,96;i=appliances/ecokettle");
            cost = 3;
        }
        Radio: Txc20 {
            @display("p=519,455;i=appliances/Radio");
            scope = PROPERTY1 | ROOM1;
            cost = 6;
            nodetype = "sink";
            datatype = "PUBLICATION";
            datascope = PROPERTY1 | ROOM1;
            dataname = 71;
        }
        heater: Txc20 {
            @display("p=451,541;i=appliances/fanHeater");
            cost = 8;
            nodetype = "source";
            datatype = "RECORD";
            dataname = 5;
        }
        bulb: Txc20 {
            @display("p=52,141;i=appliances/EF-Light-Bulbs");
            cost = 1;
        }
        switch: Txc20 {
            @display("p=390,433;i=appliances/LightSwitches");
            scope = PROPERTY1 | ROOM1;
            cost = 1;
        }
        switch1: Txc20 {
            @display("p=91,408;i=appliances/LightSwitches");
            scope = PROPERTY1 | ROOM1;
            cost = 1;
        }
        switch2: Txc20 {
            @display("p=155,204;i=appliances/LightSwitches");
            scope = PROPERTY1 | ROOM1;
            cost = 1;
        }
        switch3: Txc20 {
            @display("p=558,179;i=appliances/LightSwitches");
            cost = 4;
        }
        switch4: Txc20 {
            @display("p=377,238;i=appliances/LightSwitches");
            cost = 1;
        }
        txc3: Txc20 {
            @display("p=500,167;i=appliances/fridge");
            cost = 2;
        }
        iron: Txc20 {
            @display("p=265,486;i=appliances/iron");
            scope = PROPERTY1 | ROOM1;
            cost = 12;
        }
        meter: Txc20 {
            @display("p=286,321;i=appliances/electricity-meter");
            scope = PROPERTY1 | ROOM1;
            cost = 1;
        }
        tdryer: Txc20 {
            @display("p=305,167;i=appliances/tumbleDryer");
            cost = 3;
            nodetype = "source";
            datatype = "RECORD";
            dataname = 5;
        }
        dish: Txc20 {
            @display("p=354,96;i=appliances/dishwasher");
            cost = 3;
            nodetype = "source";
            datatype = "RECORD";
            dataname = 5;
        }
        micro: Txc20 {
            @display("p=609,140;i=appliances/microwave");
            cost = 2;
        }
        freezer: Txc20 {
            @display("p=595,238;i=appliances/Freezer");
            cost = 2;
        }
        ocsens1: Txc20 {
            @display("p=338,541;i=appliances/sensor");
            scope = PROPERTY1 | ROOM1;
            cost = 12;
            nodetype = "source";
            datatype = "PUBLICATION";
            datascope = PROPERTY1 | ROOM1;
            dataname = 71;
        }
    connections:
        switch2.gate++ <--> Channel <--> switch4.gate++;
        wash.gate++ <--> Channel <--> kett.gate++;
        kett.gate++ <--> Channel <--> monitor.gate++;
        wash.gate++ <--> Channel <--> switch4.gate++;
        kett.gate++ <--> Channel <--> switch4.gate++;
        kett.gate++ <--> Channel <--> txc3.gate++;
        monitor.gate++ <--> Channel <--> switch3.gate++;
        txc3.gate++ <--> Channel <--> switch3.gate++;
        switch4.gate++ <--> Channel <--> switch3.gate++;
        switch2.gate++ <--> Channel <--> iron.gate++;
        iron.gate++ <--> Channel <--> switch.gate++;
        switch4.gate++ <--> Channel <--> switch.gate++;
        switch3.gate++ <--> Channel <--> switch.gate++;
        switch.gate++ <--> Channel <--> heater.gate++;
        switch.gate++ <--> Channel <--> Radio.gate++;
        TV.gate++ <--> Channel <--> switch1.gate++;
        switch1.gate++ <--> Channel <--> switch2.gate++;
        heater.gate++ <--> Channel <--> Radio.gate++;
        meter.gate++ <--> Channel <--> switch2.gate++;
        meter.gate++ <--> Channel <--> switch.gate++;
        tdryer.gate++ <--> Channel <--> switch2.gate++;
        tdryer.gate++ <--> Channel <--> dish.gate++;
        dish.gate++ <--> Channel <--> switch4.gate++;
        switch3.gate++ <--> Channel <--> micro.gate++;
        monitor.gate++ <--> Channel <--> micro.gate++;
        switch3.gate++ <--> Channel <--> freezer.gate++;
        micro.gate++ <--> Channel <--> freezer.gate++;
        iron.gate++ <--> Channel <--> ocsens1.gate++;
        ocsens1.gate++ <--> Channel <--> heater.gate++;
        bulb.gate++ <--> Channel <--> switch2.gate++;
        TV.gate++ <--> Channel <--> bulb.gate++;
        bulb.gate++ <--> Channel <--> ocsens.gate++;
        TV.gate++ <--> Channel <--> ocsens.gate++;
        ocsens.gate++ <--> Channel <--> switch2.gate++;
        ocsens.gate++ <--> Channel <--> switch1.gate++;
        dish.gate++ <--> Channel <--> wash.gate++;
}

