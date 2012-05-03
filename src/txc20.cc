//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <unistd.h>
#include <dos.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <map>
#include <set>
#include <string>
#include "txc20.h"
#include "SendInterestCommand.h"
#include "HandleInterestCommand.h"
#include "HandleNeighborCommand.h"
#include "NodeStartupCommand.h"
#include "SendAdvertCommand.h"
#include "SendDataCommand.h"
#include "DisableNodeCommand.h"
#include "HandleDataCommand.h"
#include "HandleAdvertCommand.h"
#include "SendReinforcementCommand.h"
#include "HandleReinforcementCommand.h"
#include "SendRoleAdvertCommand.h"
#include "SetRoleCommand.h"
#include "HandleRoleAdvertCommand.h"
#include "HandleMoveModuleCommand.h"

#include "CheckForEventsCommand.h"

#include "RoutingMessage_m.h"

#include "MessageHelper.h"

#include "EventManager.h"


#include "RoutingAndAggregation.h"


static void cb_send_message(unsigned short _interface, unsigned char* _msg);
static void cb_bcast_message(unsigned char* _msg);
static void cb_handle_application_data(unsigned char* _msg);

static void handle_dishwasher_data(unsigned char* _msg);




static char query_demand_current[] = {DEMAND^QUERYBASED, CURRENT, 0};
static char collaboration_demand_bid[] = {DEMAND^COLLABORATIONBASED, BID, 0};
static char event_environmental_occupancy[] = {ENVIRONMENTAL^EVENTBASED, OCCUPANCY, 0};



static char messageName[9][24] =
{
"ADVERT                 ",
"INTEREST               ",
"REINFORCE              ",
"DATA                   ",
"NEIGHBOR_BCAST         ",
"NEIGHBOR_UCAST         ",
"REINFORCE_INTEREST     ",
"COLLABORATION          ",
"REINFORCE_COLLABORATION"
};





// originally length 13 - now I am adding currentstate into the role at position 8
// starting state zero
// this may work ok while we just have the forwarding role only, but when we use this
// mechanism for regular aggregation we may need to check that all the segments line up correctly
static unsigned char forwardingRole[14] = {14, 4, 4, 8, 2, 3, 0, 0, 0, 0, 9, 4, 6, 0};



int nodeConstraint;
char nodeScope;

unsigned char rMessage[MESSAGE_SIZE];
//static Txc20* currentModule;
static int currentModuleId;
//static int tester = 5;

bool Txc20::justStartedInitialising = true;
unsigned char* Txc20::state = 0;
bool Txc20::ObtainGradients = false;
bool Txc20::obtainCost = false;
bool Txc20::bestObtainGradient = false;
bool Txc20::reinforceObtain = false;
bool Txc20::deliverGradients = false;
bool Txc20::deliveryCost = false;
bool Txc20::bestDeliverGradient = false;
bool Txc20::ReinforceDelivery = false;
bool Txc20::nodeValue = false;
bool Txc20::ClearPresentation = false;


pair<multimap<string,char*>::iterator,multimap<string,char*>::iterator> Txc20::ret;
multimap<string,char*>::iterator Txc20::it;
multimap<std::string,char*> Txc20::sink;
multimap<std::string,char*> Txc20::source;
multimap<std::string,char*> Txc20::collaborator;
multimap<std::string,char*> Txc20::collaborator_initiator;
map<std::string,std::string> Txc20::stateNames;
bool Txc20::sourceAndSinkData_Initialised = false;


const int Txc20::constraintValues[9] = {10, 30, 5, 45, 20, 15, 60, 10, 5};

Define_Module(Txc20);

void Txc20::initialize()
{
	if (!sourceAndSinkData_Initialised)
	{
		Initialise_sourceAndSinkData();
	}
    // Initialize variables
    //numSent = 0;
    //numReceived = 0;
    //WATCH(numSent);
    //WATCH(numReceived);
    //WATCH(fib);
	started = false;
	goodPositionValueSet = false;
	//sourceData = 0;
	//sinkData = 0;
	// TODO - Improve this or pos this is unknown state and always start in unknown??
	this->currentState = 1;
	moduleRD.grTree = NULL;
	moduleRD.interfaceTree = NULL;
	moduleRD.stateTree = NULL;
	moduleRD.kdRoot = NULL;
	moduleRD.role[0] = NULL;
	moduleRD.role[1] = NULL;
	moduleRD.role[2] = NULL;
	moduleRD.role[3] = NULL;
	moduleRD.top_context = trie_new();
	moduleRD.top_state = trie_new();
	rd = &(moduleRD);
	rd->role[0] = (unsigned char*)malloc(forwardingRole[0]);
	memcpy(rd->role[0], forwardingRole, forwardingRole[0]);

	
	
    // set node constraint and scope(old style)
	SetSimpleNodeValues();

	string s = getName();
    EV << "###############  -  Name is: " << s << "\n";







    //std::string nodetype = par("nodetype");
    //std::string datatype = par("datatype");
    //char datascope = par("datascope");
    ///int dataname = par("dataname");
    //int xxx = dataname & 128;
    //int data = par("data");

    //dataname_struct _data;
    //_data._dataname_struct1.the_dataname = 0;
    //_data._dataname_struct2.type = (unsigned char)dataname;
    //_data._dataname_struct2.type = (unsigned char)data;
    //_data._dataname_struct2.scope = datascope;

    //if ( nodetype == "source" && datatype == "PUBLICATION" )
	//if ( nodetype == "source" )
    //{
        //_data._dataname_struct2.type &= PUBLICATION;
		//weAreSourceFor(_data);
    //}

    //if ( nodetype == "sink" && datatype == "RECORD" )
	//if ( nodetype == "sink" )
    //{
		//weAreSinkFor(_data);
    //}

    populateCommands();
    
    //this->getName();
    EV << "###############  -  Name is: " << getName() << "\n";


    std::string fp = getFullPath();
    cModule *pm = getParentModule();
    std::string pfp = getParentModule()->getFullPath();
    std::string nedName = getNedTypeName();
    std::string parentNedName = pm->getNedTypeName();
    
    char buf[100];
    char* buf_i = buf;
    //sprintf(buf_i, "%s\n%s\n", fp.c_str(), pfp.c_str());
    sprintf(buf_i, "%s\n%s [%d]\n", nedName.c_str(), parentNedName.c_str(), getIndex());
    //getDisplayString().setTagArg("t",0,buf);

    
    
    // Try setting position
    //if ( getIndex() == 0)
    //{
		//char p[10];
		//char* p_i = p;
		//sprintf(p_i, "%d", getIndex()*50);
		//getDisplayString().setTagArg("p",0,p_i);
		//getDisplayString().setTagArg("p",1,p_i);
    //}
    
    
    
    
    EV << "Initialising " << getFullPath() << "\n";
   
    //EventManager::Instance().StartEventsForModule(getId());
    
    if ( justStartedInitialising )
    {
    	remove(".\\ModuleList.txt");
    	justStartedInitialising = false;
    }
    std::ofstream myfile;
    myfile.open (".\\ModuleList.txt", std::ios::app);
    myfile << "NODE" << std::endl;
    myfile << fp << std::endl;
    
    char image[100];
    char* image_i = image;
    sprintf(image_i, "%s", getDisplayString().getTagArg("i", 0));
    myfile << "IMAGE" << std::endl;
    myfile << IMAGEPATH << image_i << ".png" << std::endl;

    char x[10];
    char y[10];
    char* x_i = x;
    char* y_i = y;
    sprintf(x_i, "%s", getDisplayString().getTagArg("p", 0));
    sprintf(y_i, "%s", getDisplayString().getTagArg("p", 1));
    myfile << "POSITION" << std::endl;
    myfile << x_i << std::endl;
    myfile << y_i << std::endl;
    
    
    
    int n = gateSize("gate");
    for ( int i = 0; i < n; i++ )
    {
        cGate* g = gate("gate$o",i);
        cGate*  ng = g->getNextGate();
        cModule* connectedMod = ng->getOwnerModule();
        std::string connectedModFullPath = connectedMod->getFullPath();
        myfile << "CONNECTION" << std::endl;
        myfile << fp << std::endl;
        myfile << connectedModFullPath << std::endl;
    }
    
    if ( getIndex() == 5)
    {
        int n = gateSize("gate");
        char buf[200];
        char* buf_i = buf;
        sprintf(buf_i, "red");
        char buf2[200];
        char* buf2_i = buf2;
        sprintf(buf2_i, "3");
        //getDisplayString().setTagArg("tt",0,buf);

        //cGate* g = gate("gate$o",0);
        //cChannel *chan  = g->getChannel();
        //chan->getDisplayString().setTagArg("ls",0,buf);
        //chan->getDisplayString().setTagArg("ls",1,buf2);
        
        
        
        //chan->setDisplayString("ls=red,3");
        
        n=0;
        for ( int i = 0; i < n; i++ )
        {
            cGate* g = gate("gate$o",i);
            cChannel *chan  = g->getChannel();
            //chan->getDisplayString().setTagArg("ls",0,buf);
            cGate*  ng = g->getNextGate();
            cModule* connectedMod = ng->getOwnerModule();
            std::string connectedModFullPath = connectedMod->getFullPath();
            char buf[200];
            char* buf_i = buf;
            sprintf(buf_i, "%d", chan);
    	    EV << "Setting channel addressed: " << buf << "\n";
    	    EV << "Setting channel of gate: " << i << "\n";
    	    EV << "Setting channel of gate connected to: " << connectedModFullPath << "\n";
            chan->setDisplayString("ls=red,3");
        }
    
    }
    
    
    
    myfile.close();
    
	setMessageCallBack(cb_send_message);
	setBroadcastCallBack(cb_bcast_message);
	setApplicationCallBack(cb_handle_application_data);

	//StartUp();

    
	TicTocMsg20* msg = MessageHelper::newMessage(CHECK_FOR_EVENTS, 0, 0, 0);
	scheduleAt(simTime()+2.0, msg);
    

}


void Txc20::handleMessage(cMessage *msg)
{
	// set the global values from this module for access from the c call backs
	currentModuleId = this->getId();
	nodeConstraint = simpleNodeConstraintValue;
	nodeScope = simpleNodeScopeValue;
	rd = &(moduleRD);

    //EV << "Txc20::handleMessage PROCESSING\n";
	int kind = msg->getKind();
	// If we are not started, then there are only certain messages which can get through
	// CHECK_FOR_EVENTS:	Is needed to look for any instrumentation from the VS Application
	//						including startup and context (using SET_CONTEXT message)
	// NODE_STARTUP:		Instrumentation sent from the VS Application to start the node
	// SET_CONTEXT:			Using old omnet interest code to action context setting.
    if ( !started && kind != NODE_STARTUP && kind != CHECK_FOR_EVENTS && kind != SET_CONTEXT)
    {
        //EV << "Not started and not startup and not check\n";
    	return;
    }

    if ( started && kind == NODE_STARTUP )
    {
        return;
    }

    // improve this condition and that above
    if ( kind != ROUTING_MESSAGE )
    {
        //EV << "check or node startup\n";
    	Command *c = cmd[kind];
		cmd[kind]->execute(msg);
		if ( kind == SET_CONTEXT || kind == NODE_STARTUP)
		{
		    if (ev.isGUI())
		        updateDisplay();
		}
    	return;
    }

    EV << "OTHER\n";
    //currentModule = this;

	//unsigned short interface = NULL == ttmsg->getArrivalGate() ? -1 : ttmsg->getArrivalGate()->getIndex();
	unsigned short inf = msg->getArrivalGate()->getIndex();
	RoutingMessage *rmsg = check_and_cast<RoutingMessage *>(msg);
	for( unsigned i = 0; i < MESSAGE_SIZE; i++ )
	{
		rMessage[i] = rmsg->getData(i);
	}

    // Framework call
	rpacket p;
	memcpy(p.packet_bytes, rMessage, MESSAGE_SIZE);
	EV << "Received: " << messageName[p.the_message.message_type] << "\n";
	handle_message(rMessage, inf);





	/*
    Command *c = cmd[kind];
	if ( c )
	{
	    EV << "CALLING EXECUTE FOR: " << kind << "\n";
	    EV << "Item 1: " << msg->getArrivalGateId() << "\n";
	    EV << "Item 2: " << msg->getSenderGateId() << "\n";
	    if ( msg->getArrivalGate() )
	    {
		    EV << "Item 3: " << msg->getArrivalGate()->getIndex() << "\n";
	    
	    }
	    //EV << "Item 4: " << msg->getArrivalGateId() << "\n";
		cmd[kind]->execute(msg);
	}
	else
	{
	    EV << "NO COMMAND FOR: " << kind << "\n";
	    char buf[100];
	    char* buf_i = buf;
	    sprintf(buf_i, "No such command\n");
	    getDisplayString().setTagArg("t",0,buf);
	}
	*/
    

    if (ev.isGUI())
        updateDisplay();
    
}


void Txc20::forwardInterestMessage(TicTocMsg20 *ttmsg)
{
}

TicTocMsg20 *Txc20::generateInterestMessage(int interest, int minPathConstraint)
{
	return NULL;
}

TicTocMsg20 *Txc20::generateNotificationMessage(int notification)
{
	return NULL;
}



void Txc20::updateDisplay()
{
    
    if ( false )
    {
		//getDisplayString().setTagArg("tt",0,fib.getString().c_str());
		char buf[1000];
		char* buf_i = buf;
		sprintf(buf_i, "%d\n%s============\n%s", this->currentState, fib.getString().c_str(), dcs.getString().c_str());

		//getDisplayString().setTagArg("tt",0,fib.getString().c_str());
		getDisplayString().setTagArg("tt",0,buf);
		return;
    }




    // DISPLAY TO FILE
	std::string fp = getFullPath();
	std::ofstream infile;
    std::string filename = "./display/"+fp+".txt";
    EV << "Opening file: " << filename << "\n";
    //remove(filename.c_str());
	infile.open (filename.c_str());

	//if ( infile.is_open() && !infile.eof() )
	if ( infile.is_open() )
	{
		//DisplayKDGradientTree(&(moduleRD.grTree), infile);
		DisplayNodeDetails(infile);
		infile << std::endl << std::endl;
		//DisplayKDGradientTree(&(moduleRD.grTree), infile);  //???????????


		/*
		infile << "CURR:" << "\t" << this->currentState << std::endl;
		infile << "Entries pointing to: SINK" << std::endl;
		infile << ForwardingEntrySet::getFullHeaders();
		infile << fib.getFullString();
		infile << std::endl;
		infile << "Entries pointing back to: SOURCE" << std::endl;
		infile << DataCacheSet::getFullHeaders();
		infile << dcs.getFullString();
		*/

	    EV << "Reading file to create generic message...\n";
	}
	
	infile.close();
    EV << "File closed.\n";







    
	
}

void Txc20::Red(int gateIndex)
{
	// set the two channels between the two nodes to red for reinforced
	// this seems to work, seem to need to set from both ends
	//int gateIndex = ttmsg->getArrivalGate()->getIndex();

	cGate* g = gate("gate$o", gateIndex);
    cGate* ig = gate("gate$i", gateIndex);
    if ( g && ig )
    {
        cDelayChannel *chan1  = check_and_cast<cDelayChannel *>(g->getChannel());
    	chan1->setDisplayString("ls=red,3");
        cGate*  ng = ig->getPreviousGate();
        cDelayChannel *chan2  = check_and_cast<cDelayChannel *>(ng->getChannel());
	    chan2->setDisplayString("ls=red,3");
    }

}


bool Txc20::AlreadyForwardingThisInterest(int _interest)
{
	return false;
}


void Txc20::SetSimpleNodeValues()
{
	//int theIndex = getIndex();
	simpleNodeConstraintValue = par("cost");//constraintValues[theIndex];
	simpleNodeScopeValue = par("scope");

	//context
}

void Txc20::populateCommands()
{
	cmd[SEND_INTEREST]       = new SendInterestCommand(this);
	cmd[SEND_ADVERTISE]      = new SendAdvertCommand(this); 
	cmd[SEND_DATA]           = new SendDataCommand(this);
	cmd[DISABLE_NODE]        = new DisableNodeCommand(this);
	cmd[ENABLE_NODE]         = new Command(this); // EbableNodeCommand(this);
	// THIS HandleInterestCommand IS NOW USED FOR CONTEXT!!!!
	cmd[SET_CONTEXT]            = new HandleInterestCommand(this);
	cmd[ADVERTISE]           = new HandleAdvertCommand(this);
	cmd[DATA]                = new HandleDataCommand(this); // DataCommand(this);
	cmd[SEND_REINFORCE]      = new SendReinforcementCommand(this);
	cmd[REINFORCE]           = new HandleReinforcementCommand(this);
	cmd[CHECK_FOR_EVENTS]    = new CheckForEventsCommand(this);
	cmd[ADVERTISE_ROLE]      = new SendRoleAdvertCommand(this);
	cmd[ROLE_ADVERT]         = new HandleRoleAdvertCommand(this);
	cmd[MOVE_MODULE]         = new HandleMoveModuleCommand(this);
	cmd[SET_ROLE]            = new SetRoleCommand(this);
	cmd[NODE_STARTUP]        = new NodeStartupCommand(this);
	cmd[NEIGHBOR_BROADCAST]  = new HandleNeighborCommand(this);
	cmd[NEIGHBOR_MESSAGE]    = new HandleNeighborCommand(this);
	
	
	
	
	
}



void Txc20::processPresentationSettings()
{
	rd = &(moduleRD);
    int gs = gateSize("gate");
    for ( int inf = 0; inf < gs; inf++ )
    {
    	setDisplayString(inf);
    }


	/*
    g->costToDeliver;
	g->costToObtain;
	State* s = g->key1;
	Interface* i = g->key2;
	struct StateNode* n = FindStateNode(rd->stateTree, Txc20::state);
	struct InterfaceNode* i = FindInterfaceNode(rd->interfaceTree, 0);
	struct KDGradientNode* g = SearchForKDGradientNode(Txc20::state, 0, rd->grTree);
	n->s->bestGradientToDeliver;
	n->s->bestGradientToObtain;
	n->s->deliveryInterfaces;
	n->s->obtainInterface;
	TraversStateNodes(rd->stateTree, processState);
	*/





}


void Txc20::setDisplayString(int inf)
{
	std::string displayString;
	std::ostringstream displayStream(displayString);

	struct KDGradientNode* g = SearchForKDGradientNode1(Txc20::state, inf, rd->grTree);
	if ( !g )
	{
		return;
	}
	State* st = g->key1;
	Interface* i = g->key2;

	if ( Txc20::ClearPresentation )
	{
		std::string clrString = "";
		setDisplayStringBothChannels(inf, clrString);
		this->getDisplayString().setTagArg("t",0,"");
		return;
	}
	if ( Txc20::ObtainGradients )
	{
		if ( 9999 > g->costToObtain > 0 )
		{
			displayStream << "ls=red,3";
			std::string s = displayStream.str();
			setDisplayStringBothChannels(inf, s);
		}
	}
	if ( Txc20::obtainCost )
	{
		if ( (g->costToObtain < 9999) && (g->costToObtain > 0) )
		{
			displayStream << "t=" << g->costToObtain;
			std::string s = displayStream.str();
			setDisplayStringInChannel(inf, s);
		}
	}
	if ( Txc20::deliveryCost )
	{
		if ( (g->costToDeliver < 9999) && (g->costToDeliver > 0) )
		{
			displayStream << "t=" << g->costToDeliver;
			std::string s = displayStream.str();
			setDisplayStringInChannel(inf, s);

		}
	}
	if ( Txc20::bestObtainGradient )
	{
		if ( g == st->bestGradientToObtain )
		{
			displayStream << "ls=red,3";
			std::string s = displayStream.str();
			setDisplayStringBothChannels(inf, s);
		}

	}
	if ( Txc20::reinforceObtain )
	{
		InterfaceList* temp = st->obtainInterfaces;
		while( temp !=NULL )
		{
			if ( temp->i->iName == inf )
			{
				displayStream << "ls=red,3";
				std::string s = displayStream.str();
				setDisplayStringBothChannels(inf, s);
				break;
			}
			temp = temp->link;
		}
	}
	if ( Txc20::deliverGradients )
	{
		if ( 9999 > g->costToDeliver > 0 )
		{
			displayStream << "ls=red,3";
			std::string s = displayStream.str();
			setDisplayStringBothChannels(inf, s);
		}
	}
	if ( Txc20::bestDeliverGradient )
	{
		if ( g == st->bestGradientToDeliver )
		{
			displayStream << "ls=red,3";
			std::string s = displayStream.str();
			setDisplayStringBothChannels(inf, s);
		}

	}
	if ( Txc20::ReinforceDelivery )
	{
		InterfaceList* temp = st->deliveryInterfaces;
		while( temp !=NULL )
		{
			if ( temp->i->iName == inf )
			{
				displayStream << "ls=red,3";
				std::string s = displayStream.str();
				std::string fp = this->getFullPath();
				setDisplayStringBothChannels(inf, s);
				break;
			}
			temp = temp->link;
		}
	}
	if ( Txc20::nodeValue )
	{
	    char buf[100];
	    char* buf_i = buf;
	    sprintf(buf_i, "cost: %d", this->simpleNodeConstraintValue);
		this->getDisplayString().setTagArg("t",0,buf);
	}





}


void Txc20::setDisplayStringInChannel(int gateIndex, std::string &ds)
{
	cGate* og = gate("gate$o", gateIndex);
    cGate* ig = gate("gate$i", gateIndex);
    if ( ig )
    {
    	//cChannel* c = og->getChannel();
    	//if ( c )
    	//{
            //cDelayChannel *chan1  = check_and_cast<cDelayChannel *>(g->getChannel());
        	//chan1->setDisplayString(ds.c_str());
          //  cDelayChannel *chan1  = check_and_cast<cDelayChannel *>(c);
        //	chan1->setDisplayString(ds.c_str());

    	//}
        cGate*  ng = ig->getPreviousGate();
        cDelayChannel *chan2  = check_and_cast<cDelayChannel *>(ng->getChannel());
		chan2->setDisplayString(ds.c_str());

    }
}


void Txc20::setDisplayStringOutChannel(int gateIndex, std::string &ds)
{
	cGate* og = gate("gate$o", gateIndex);
    cGate* ig = gate("gate$i", gateIndex);
    if ( og )
    {
    	cChannel* c = og->getChannel();
    	if ( c )
    	{
            //cDelayChannel *chan1  = check_and_cast<cDelayChannel *>(g->getChannel());
        	//chan1->setDisplayString(ds.c_str());
            cDelayChannel *chan1  = check_and_cast<cDelayChannel *>(c);
        	chan1->setDisplayString(ds.c_str());

    	}
        //cGate*  ng = ig->getPreviousGate();
        //cDelayChannel *chan2  = check_and_cast<cDelayChannel *>(ng->getChannel());
		//chan2->setDisplayString(ds.c_str());

    }
}




void Txc20::setDisplayStringBothChannels(int gateIndex, std::string &ds)
{
	cGate* og = gate("gate$o", gateIndex);
    cGate* ig = gate("gate$i", gateIndex);
    if ( og && ig )
    {
        cDelayChannel *chan1  = check_and_cast<cDelayChannel *>(og->getChannel());
    	chan1->setDisplayString(ds.c_str());
    	chan1->getDisplayString().setTagArg("m",0,"s");
        cGate*  ng = ig->getPreviousGate();
        cDelayChannel *chan2  = check_and_cast<cDelayChannel *>(ng->getChannel());
	    chan2->setDisplayString(ds.c_str());

    }

}


void Txc20::Initialise_sourceAndSinkData()
{
    stateNames[query_demand_current] = "query_demand_current";
    stateNames[collaboration_demand_bid] = "collaboration_demand_bid";
    stateNames[event_environmental_occupancy] = "event_environmental_occupancy";

    collaborator_initiator.insert(pair<string,char*>("wash",collaboration_demand_bid));
    collaborator.insert(pair<string,char*>("tdryer",collaboration_demand_bid));
    collaborator.insert(pair<string,char*>("dish",collaboration_demand_bid));
    collaborator.insert(pair<string,char*>("kett",collaboration_demand_bid));
    collaborator.insert(pair<string,char*>("micro",collaboration_demand_bid));


/*
	sink.insert(pair<string,char*>("monitor",query_demand_current));
	source.insert(pair<string,char*>("TV",query_demand_current));
	source.insert(pair<string,char*>("heater",query_demand_current));
	source.insert(pair<string,char*>("tdryer",query_demand_current));
    source.insert(pair<string,char*>("dish",query_demand_current));
    source.insert(pair<string,char*>("kett",query_demand_current));
    source.insert(pair<string,char*>("micro",query_demand_current));

    source.insert(pair<string,char*>("ocsens",event_environmental_occupancy));
    source.insert(pair<string,char*>("ocsens1",event_environmental_occupancy));
    sink.insert(pair<string,char*>("Radio",event_environmental_occupancy));
    sink.insert(pair<string,char*>("iron",event_environmental_occupancy));
    sink.insert(pair<string,char*>("TV",event_environmental_occupancy));
    sink.insert(pair<string,char*>("bulb",event_environmental_occupancy));
*/

	sourceAndSinkData_Initialised = true;
}






/*
void processState(State* s)
{


	unsigned char Txc20::state = 255;
	bool Txc20::ObtainGradients = false;
	bool Txc20::obtainCost = false;
	bool Txc20::bestObtainGradient = false;
	bool Txc20::reinforceObtain = false;
	bool Txc20::deliverGradients = false;
	bool Txc20::deliveryCost = false;
	bool Txc20::bestDeliverGradient = false;
	bool Txc20::ReinforceDelivery = false;
	bool Txc20::nodeValue = false;













	int temp = dataRate;

	if ( s->action == SINK_ACTION )
	{
		if ( s->bestGradientToObtain && !s->obtainInterface )
		{
			// received at least one advertisement
			// but consider some try next regular check mechanism
			// to enable the arrival of further advertisements
			handle_reinforce(SELF_INTERFACE);
		}
	}

	// some of this data stuff probably ought
	// to be inside the application layer
	if ( s->action == SOURCE_ACTION )
	{
		dataRate++;
		if ( s->deliveryInterfaces && dataRate > 150)
		{
			dataRate = 0;
			handle_data(SELF_INTERFACE);
		}
	}


}
*/








static void cb_send_message(unsigned short _interface, unsigned char* _msg)
{
	/*
	 * This is a generic call back for the data centric routing framework
	 * It's implementation in this case is specifically tailored to Omnet++
	 */
	cSimpleModule* currentModule = check_and_cast<cSimpleModule *>(cSimulation::getActiveSimulation()->getModule(currentModuleId));

	char msgname[20];
	sprintf(msgname, "%s", messageName[*_msg]);
	RoutingMessage *msg = new RoutingMessage(msgname);
	msg->setKind(ROUTING_MESSAGE);
	unsigned int messageSize = _msg[1] + 4;
	for( unsigned i = 0; i < messageSize; i++ )
	{
		msg->setData(i, _msg[i]);
	}
	currentModule->send(msg, "gate$o", _interface);
}

static void cb_bcast_message(unsigned char* _msg)
{
	/*
	 * This is a generic call back for the data centric routing framework
	 * It's implementation in this case is specifically tailored to Omnet++
	 */
//check_and_cast<Txc20 *>
	//static cSimulation* cSimulation::getActiveSimulation()->getModule(currentModuleId)

	cSimpleModule* currentModule = check_and_cast<cSimpleModule *>(cSimulation::getActiveSimulation()->getModule(currentModuleId));
	int n = currentModule->gateSize("gate");
	char msgname[20];
	sprintf(msgname, "%s", messageName[*_msg]);

    for ( int i = 0; i < n; i++ )
    {
    	RoutingMessage *msg = new RoutingMessage(msgname);
    	msg->setKind(ROUTING_MESSAGE);
    	for( unsigned i = 0; i < MESSAGE_SIZE; i++ )
    	{
    		msg->setData(i, _msg[i]);
    	}
	    EV << "Send to gate " << i << " \n";
	    currentModule->send(msg, "gate$o",i);
    }


}


static void cb_handle_application_data(unsigned char* _msg)
{
	// work still to do here
	// packetbuf_copyto(_msg, MESSAGE_SIZE);
	cSimpleModule* currentModule = check_and_cast<cSimpleModule *>(cSimulation::getActiveSimulation()->getModule(currentModuleId));

	char bubbleText[40];
	char* bubbleTextPtr = bubbleText;
	while (*_msg)
	{
        int numChar = sprintf(bubbleTextPtr, "%d-", (unsigned int)*_msg);
	    bubbleTextPtr += numChar;
	    _msg++;
	}
    currentModule->bubble(bubbleText);
    //currentModule->bubble("Data received");



}



static void handle_dishwasher_data(unsigned char* _msg)
{

}








//##################################################

/*
 * Notes
 * ======
 * 
 * At some point the interface values in the fib should maybe better represent the destination
 * 
 * 
 * 
 * 
 * 
 */

 
