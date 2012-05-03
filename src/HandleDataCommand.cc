

#include "HandleDataCommand.h"
#include "SoftMessage.h"
#include "MessageHelper.h"
#include "txc20.h"
#include "RoutingAndAggregation.h"




void ForwardData(int interface);
void HandleData();



Txc20* tempModule;

void ForwardData(int interface)
{

}

void HandleData()
{

}





HandleDataCommand::HandleDataCommand(Txc20* _m)
: Command(_m)
{
	
}



void HandleDataCommand::execute(cMessage *msg)
{
	TicTocMsg20 *ttmsg = check_and_cast<TicTocMsg20 *>(msg);
	if ( ttmsg->isSelfMessage() )
	{
	    EV << "Message kind " << ttmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	    //exit(-1);
	}
	
	rd = &(m->moduleRD);

	SoftMessage sm(ttmsg, m);
	
	// an entry pointing to self interface (-1) indicates this is the source
	//ForwardingEntry selfEntry(0, sm.data, sm.data, -1, 0, 0, -1, 0);
	//ForwardingEntrySet::iterator i = m->fib.find(selfEntry);
	//if ( i != m->fib.end() )
	//{
	//	m->bubble("DATA RECEIVED!!");
	//	return; // if a sink can also forward to others then possibly remove this and improve condition below
	//}

    // a reinforced deliver gradient to self indicates this is the sink
	// that sent out the reinforcement, so stop
    //KDGradientNode* gn;
	//if ( (gn = SearchForKDGradientNode(sm.data, SELF_INTERFACE, m->moduleRD.grTree)) )
	//{
	//	m->bubble("DATA RECEIVED!!");
	//	return; // if a sink can also forward to others then possibly remove this and improve condition below
	//}
	

	//StateNode* sn = FindStateNode(rd->stateTree, sm.data);
	// not quite right 'cos we just using the best interest gradient
	// rather than the reinforced one

	TicTocMsg20* newmsg = MessageHelper::newMessage(DATA, sm.data, 0, 0);
	InterfaceList* temp = 0;//sn->s->deliveryInterfaces;
	while( temp !=NULL )
	{
		// we have temporarily made some assumptions in the above and below code
		if ( temp->i->iName == SELF_INTERFACE )
		{
			m->bubble("DATA RECEIVED!!");
		}
		else
		{
			SendCopyTo(newmsg, temp->i->iName);
		}
		temp = temp->link;
	}
	delete newmsg;

	return;

    


	/*
	 * What's this doing?
	 *
	 * iterates the fib
	 *
	 * where the entry is either for no current state or for same as current state
	 * PLUS same as incoming data
	 *
	 * then we we set the current state as the new outgoing state
	 * and if its reinforced we send that new state out
	 *
	 * ELSE we iterate to the next fib entry
	 *
	 *
	 * So....
	 * Basically we want to know whether to transform and forward or just forward
	 *
	 *
	 */
	//TicTocMsg20* newmsg = MessageHelper::newMessage(DATA, sm.data, 0, 0);
	int moduleStateOnEntry = m->currentState;
	for ( std::set<ForwardingEntry>::iterator i = m->fib.begin(); i != m->fib.end(); i++ )
	{
		if (    ( i->currentState  == ANY_STATE ||
				  i->currentState  == moduleStateOnEntry ) &&
				i->incomingState == sm.data                   )
		{
			m->currentState = i->outgoingState;
			if ( i->reinforced )
			{
				newmsg->setData(i->outgoingState);
				SendCopyTo(newmsg, i->outgoingInterface);
			}
		}
	}
	delete newmsg;
	
}


