

#include "SendAdvertCommand.h"
#include "MessageHelper.h"
#include "txc20.h"
#include "RoutingAndAggregation.h"


SendAdvertCommand::SendAdvertCommand(Txc20* _m)
: Command(_m)
{
	
}



void SendAdvertCommand::execute(cMessage *msg)
{
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
	if ( !gmsg->isSelfMessage() )
	{
	    EV << "Message kind " << gmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	    //exit(-1);
	}
	rd = &(m->moduleRD);

    m->getDisplayString().setTagArg("i",0,"block/source");

	std::string  s = gmsg->getData();
	std::stringstream ss(s);
	int data;
	ss >> data;
    
	// currently hopcount zero (3rd param) use zero mpe to start (4th param)
	//cRNG *rng1 = m->getRNG(1);
	//int advertInstance = rng1->intrand(255);
	int advertInstance = intrand(255);
	TicTocMsg20* newmsg = MessageHelper::newMessage(ADVERTISE, data, advertInstance, 0);
	SendCopyToAllInterfaces(newmsg);
	
	// add an advert data cache entry pointing to interface self
	// REPLACE WITH EMULATION CODE
	//DataCache dc(0, data, data, -1, 0, 0, -1, 0, 0, advertInstance);
	/*
	DataCache(int current, int incoming, int outgoing,
	int interface, int value, int _pathvalue, int _interfaceModuleIndex,
	int _broken, int _reinforced, int instance);
	*/
	//m->dcs.erase(dc);
	//m->dcs.insert(dc);
	// REPLACE WITH EMULATION CODE

	//setObtainGradient(data, SELF_INTERFACE, COST_ZERO);
	// or maybe that below

    //reinforceObtainGradient(data, SELF_INTERFACE);







	
	delete newmsg;
	
}


