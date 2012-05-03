

#include "HandleNeighborCommand.h"
#include "SoftMessage.h"
#include "MessageHelper.h"
#include "RoutingAndAggregation.h"

void process(State* s);


void process(State* s)
{
//	HandleNeighborCommand* command = (HandleNeighborCommand*)c;
//	TicTocMsg20* msg = MessageHelper::newMessage(ADVERTISE, s->dataName, 0,
//			s->bestGradientToObtain->costToObtain + command->m->simpleNodeConstraintValue);
//	command->SendCopyTo(msg, command->newNeighbor);
//	delete msg;

}



HandleNeighborCommand::HandleNeighborCommand(Txc20* _m)
: Command(_m)
{
	
}




void HandleNeighborCommand::execute(cMessage *msg)
{
	TicTocMsg20 *ttmsg = check_and_cast<TicTocMsg20 *>(msg);
	if ( ttmsg->isSelfMessage() )
	{
	    EV << "Message kind " << ttmsg->getKind() << " is not a self message, but WAS sent to self\n";
		return;
	    //exit(-1);
	}
	SoftMessage sm(ttmsg, m);
	newNeighbor = sm.interface;
	rd = &(m->moduleRD);
	InsertInterfaceNode(&(rd->interfaceTree), sm.interface);
	
	// IF NEIGHBOUR MESSAGE SENT IN ERROR
	// ie we already have the neighbour, then MAYBE we shouldn't do all the stuff???

	// send our best advertisements (initially just advertisements) to the new neighbour
	bool statesFound = 0;//TraversStateNodes(rd->stateTree, process);//HandleNeighborCommand::process);

	// If the new neighbour broadcasted to us because they did not have us
	// in their interface list and we have not identified ourselves through
	// forwarding the neighbour our best interests and advertisements
	//
	// THEN send a neighbour message so they know who we are
	if ( sm.kind == NEIGHBOR_BROADCAST && !statesFound )
	{
		int myInterface = m->getId();
		TicTocMsg20* msg = MessageHelper::newMessage(NEIGHBOR_MESSAGE, myInterface, 0, 0);
		SendCopyTo(msg, sm.interface);
	}

}

//void HandleNeighborCommand::process(State* s)
//{
//	TicTocMsg20* msg = MessageHelper::newMessage(ADVERTISE, s->dataName, 0,
//			s->bestGradientToObtain->costToObtain+m->simpleNodeConstraintValue);
//	SendCopyTo(msg, newNeighbor);
//	delete msg;

//}
