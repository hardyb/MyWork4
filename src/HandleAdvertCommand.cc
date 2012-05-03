

#include "HandleAdvertCommand.h"
#include "SoftMessage.h"
#include "MessageHelper.h"
#include "RoutingAndAggregation.h"


HandleAdvertCommand::HandleAdvertCommand(Txc20* _m)
: Command(_m)
{
	
}




void HandleAdvertCommand::execute(cMessage *msg)
{
	TicTocMsg20 *ttmsg = check_and_cast<TicTocMsg20 *>(msg);
	if ( ttmsg->isSelfMessage() )
	{
	    EV << "Message kind " << ttmsg->getKind() << " is not a self message, but WAS sent to self\n";
		return;
	    //exit(-1);
	}
	SoftMessage sm(ttmsg, m);
	rd = &(m->moduleRD);
	
	// NEW EMULATION CODE
	// an entry pointing to self indicates this is the source
	//DataCache selfEntry(0, sm.data, sm.data, -1, 0, 0, -1, 0, 0, 0);
	//DataCacheSet::iterator i = m->dcs.find(selfEntry);
	//if ( i != m->dcs.end() )
	//{
	//	return;
	//}
	// NEW EMULATION CODE
	// a gradient to self indicates this is the source
	//if ( SearchForKDGradientNode(sm.data, SELF_INTERFACE, m->moduleRD.grTree) )
	//{
	//	return;
	//}




	
	// TEMPORARY CODE TO TEST
    /*
     * We have received an advertisement that may replace a preceding advertisement
     * We will know this if the data is the same but the instance value differs
     * We should remove all regular forwarding entries for the old advertisement
     * We should not remove any role entries
     */
	for ( DataCacheSet::iterator i = m->dcs.begin(); i != m->dcs.end(); )
	{
		DataCacheSet::iterator toDelete = i;
		++i;   // increment before erasing!
		if ( toDelete->incomingState == sm.data &&
				toDelete->outgoingState == sm.data &&
				toDelete->instance  != sm.hopCount )
		{
			m->dcs.erase(toDelete);
		}
	}
	
    /*
     * We have received an advertisement that may replace a preceding advertisement
     * reinforced interests are associated with a corresponding advertisement
     * by having the same instance value
     * Therefore if the data is the same but the instance value differs
     * We should remove all regular forwarding entries for the old interest
     * We should not remove any role entries
     */
	for ( ForwardingEntrySet::iterator i = m->fib.begin(); i != m->fib.end(); )
	{
		ForwardingEntrySet::iterator toDelete = i;
		++i;   // increment before erasing!
		if ( toDelete->incomingState == sm.data &&
				toDelete->outgoingState == sm.data &&
				toDelete->instance  != sm.hopCount )
		{
			// TEMPORARY - Ought possibly only to negatively reinforce
			m->fib.erase(toDelete);
		}
	}
	
	


	// NEW EMULATION CODE
	// creates new states, new interfaces and new gradients where they do not
	// yet exist
	//setObtainGradient(sm.data, sm.interface, sm.msgMinPathConstraint);

	StateNode* n;
	//if ( (n = FindStateNode(m->moduleRD.stateTree, sm.data)) )
	{
		if ( n->s->bestGradientToObtainUpdated )
		{
			n->s->bestGradientToObtainUpdated = false;
			TicTocMsg20* msg = MessageHelper::newMessage(ADVERTISE, sm.data, sm.hopCount, sm.msgMinPathConstraint+m->simpleNodeConstraintValue);
			SendCopyToAllInterfaces(msg, sm.interface); // to all except sm.interface
			delete msg;
		}
	}
	




/*
 * We also need to forward advertise messages when we get a new neighbor
 *
 * so we need to iterate the states in this current module
 * and send the best cost + cost of ourselves
 *
 *
 */










}

bool HandleAdvertCommand::fibEntryRule()
{
#ifdef NOTDEFINED
	// first every fib entry
	if ( m->fib.empty() )
	{
		return true;
	}
	
	// first entry for these interest and interface
	if ( m->fib.find(fe) == m->fib.end() )
	{
		retrun true;
	}
	
	// existing fib entry for interest and interface, but message path value is better
	if ( m->fib.find(fe) != m->fib.end() && sm.msgMinPathConstraint < m->fib.find(fe)->pathValue)
	{
		return true;
	}
#endif
	return false;
}

bool HandleAdvertCommand::forwardingEntryRule()
{
	
	return false;
}
