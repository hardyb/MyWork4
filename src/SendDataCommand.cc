

#include "SendDataCommand.h"
#include "MessageHelper.h"
#include "txc20.h"


SendDataCommand::SendDataCommand(Txc20* _m)
: Command(_m)
{
	
}



void SendDataCommand::execute(cMessage *msg)
{
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
	if ( !gmsg->isSelfMessage() )
	{
	    EV << "Message kind " << gmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	    //exit(-1);
	}

	rd = &(m->moduleRD);

	std::string  s = gmsg->getData();
	std::stringstream ss(s);
	int data;
	ss >> data;
    
	//StateNode* sn = FindStateNode(rd->stateTree, data);
	// not quite right 'cos we just using the best interest gradient
	// rather than the reinforced one
	//int interface = sn->s->deliveryInterface->iName;

	// we have temporarily made some assumptions in the above and below code
	//TicTocMsg20* newmsg = MessageHelper::newMessage(DATA, data, 0, 0);
	//SendCopyTo(newmsg, interface);
	//delete newmsg;

	TicTocMsg20* newmsg = MessageHelper::newMessage(DATA, data, 0, 0);
	InterfaceList* temp = 0;//sn->s->deliveryInterfaces;
	while( temp !=NULL )
	{
		// we have temporarily made some assumptions in the above and below code
		SendCopyTo(newmsg, temp->i->iName);
		temp = temp->link;
	}
	delete newmsg;

	return;



	/*
	 * SO...
	 * AT PRESENT
	 * We are not sending to more than one sink.  We need to deal with this in our data
	 * structures
	 */

	for ( std::set<ForwardingEntry>::iterator i = m->fib.begin(); i != m->fib.end(); i++ )
	{
		if (    i->currentState  == 0 &&
				i->incomingState == data &&
				i->outgoingState == data &&
				i->reinforced               )
		{
			SendCopyTo(newmsg, i->outgoingInterface);
		    m->getDisplayString().setTagArg("i",0,"block/source");
		}
	}
	delete newmsg;
	
}


