package energysimulation;

@license(LGPL);

//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


channel Channel extends ned.DelayChannel
{
    delay = 100ms;
}



simple Txc20
{
    parameters:
		int scope = default(0);
		int cost = default(0);
		string nodetype = default (""); // "source" or "sink"
		string datatype = default (""); // "RECORD" or "PUBLICATION"
		int datascope = default(0); // use an ORing of PROPERTY1, ROOM1, UTILITY1 above
		
		int dataname = default(-1); // 0 to 127
		int data = datatype == "PUBLICATION" ? dataname | 128: dataname;
		
		//bool source = default(false);
		//bool sink = default(false);
		//int advert = default(-1);
		//int interest = default(-1);
        //int count @prompt("Enter count:");
        @display("i=block/routing");
    gates:
        inout gate[];  // declare two way connections
}



network Tictoc20
{
    parameters:
		int PROPERTY =1;
		int ROOM = 4;
		int UTILITY = 16;
    
    @display("bgb=393,195");
    //types:
        //channel Channel extends ned.DelayChannel
        //{
        //    delay = 100ms;
        //}
    
    submodules:
        //tic[9]: Txc20;
        tic[9]: Txc20 {
            @display("is=l");
            //@display("p=133,110;is=l");
            //@display("p=133,110,m,3,50,50;is=l");
        }
    connections:
        tic[0].gate++ <--> Channel <--> tic[1].gate++;
        tic[1].gate++ <--> Channel <--> tic[2].gate++;
        tic[1].gate++ <--> Channel <--> tic[4].gate++;
        tic[3].gate++ <--> Channel <--> tic[4].gate++;
        tic[4].gate++ <--> Channel <--> tic[5].gate++;
        tic[4].gate++ <--> Channel <--> tic[0].gate++;





        tic[6].gate++ <--> Channel <--> tic[4].gate++;
        tic[6].gate++ <--> Channel <--> tic[2].gate++;
        tic[7].gate++ <--> Channel <--> tic[5].gate++;
        //tic[6].gate++ <--> Channel <--> tic[7].gate++;
        tic[8].gate++ <--> Channel <--> tic[1].gate++;
        tic[8].gate++ <--> Channel <--> tic[7].gate++;

















}









