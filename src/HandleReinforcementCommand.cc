

#include "HandleReinforcementCommand.h"
#include "SoftMessage.h"
#include "MessageHelper.h"


HandleReinforcementCommand::HandleReinforcementCommand(Txc20* _m)
: Command(_m)
{
	
}



void HandleReinforcementCommand::execute(cMessage *msg)
{
	TicTocMsg20 *ttmsg = check_and_cast<TicTocMsg20 *>(msg);
	if ( ttmsg->isSelfMessage() )
	{
	    EV << "Message kind " << ttmsg->getKind() << " is not a self message, but WAS sent to self\n";
		return;
	}
	
	rd = &(m->moduleRD);

	m->Red(ttmsg->getArrivalGate()->getIndex());
	
    SoftMessage sm(ttmsg, m);

	// NEW EMULATION CODE
    //KDGradientNode* g = reinforceDeliverGradient(sm.data, sm.interface);

    // a reinforced obtain gradient to self indicates this is the source, so stop
    //KDGradientNode* gn;
	//if ( (gn = SearchForKDGradientNode(sm.data, SELF_INTERFACE, m->moduleRD.grTree)) )
			//&& gn->key1->obtainInterface == gn->key2 )
	//{
	//	return;
	//}

	//if ( g->key1->bestGradientToObtain )
	{
		// already reinforced so stop here
		//if ( g->key1->bestGradientToObtain->obtainReinforcement )
			//return;

		// otherwise prepare and forward the reinforcement on this next entry interface
		//int interface = g->key1->bestGradientToObtain->key2->iName;
        //int instance = 0;
        //reinforceObtainGradient(sm.data, interface);
		//TicTocMsg20* newmsg = MessageHelper::newMessage(REINFORCE, sm.data, instance, 0);
    	//SendCopyTo(newmsg, interface);
    	//delete msg;

	}

	return;

    // BELOW FOR REMOVAL - ABOVE IS NEW EMULATION CODE

    // we are currently using the fib (has interests in it) to reinforce
	/*
	 * Create a new interest fib entry from the incoming reinforcement message
	 * See whether an interest fib entry for this state and outgoing interface already exist
	 * if one does then reinforce it by setting reinforced in a copy and overwriting
	 * if one doesn't, then reinforce this one and insert it
	 */

	// what is this doing?
    /*
     * creates a subset of fib entries for a given outgoing (could be forwarders or state change)
     *
     * for each
     * if the interface is the same it sets reinforcement
     * if its unknown it sets reinforcement AND interface
     *
     * if its a different interface then it trys to insert a new entry with the new i/f
     *  I think this only works by good fortune.
     *  ie if we are trying to insert one with the same interface as one we haven't iterated to yet
     *  then the C++ set insert simply fails, otherwise the new entry is rightly inserted
     *
     *
     */
    std::set<ForwardingEntry> outIFSet = m->fib.OutSet(sm.data);
	for ( std::set<ForwardingEntry>::iterator i = outIFSet.begin(); i != outIFSet.end(); i++ )
	{
		if ( i->outgoingInterface == UNKNOWN_INTERFACE ||
				i->outgoingInterface == sm.interface )
		{
			ForwardingEntry new_fe = *i;
			m->fib.erase(new_fe);
			new_fe.outgoingInterface = sm.interface;
			new_fe.reinforce();
			new_fe.instance = sm.hopCount;
			m->fib.insert(new_fe);

		}
		else
		{
			ForwardingEntry new_fe = *i;
			new_fe.outgoingInterface = sm.interface;
			new_fe.reinforce();
			new_fe.instance = sm.hopCount;
			m->fib.insert(new_fe);
		}
	}

	/*
	 * If there were no entries with this output then we simply insert a new fib entry
	 */
	if ( outIFSet.empty() )
	{
		ForwardingEntry fe(0, sm.data, sm.data, sm.interface, 0, 0, sm.senderModuleIndex);
		fe.reinforce();
		fe.instance = sm.hopCount;
		m->fib.insert(fe);
	}



	
    
	
	// an entry pointing to self indicates this is the source
	DataCache selfEntry(0, sm.data, sm.data, -1, 0, 0, -1, 0, 0, 0);
	DataCacheSet::iterator it = m->dcs.find(selfEntry);
	if ( it != m->dcs.end() )
	{
		return;
	}
    
	/*
	 * Get the best advert entry for the data to be reinforced
	 */
	std::set<DataCache>::iterator bestEntry;
    if ( m->dcs.BestPathEntry(0, sm.data, sm.data, bestEntry) )
    {
		if ( bestEntry->reinforced )
			return; // entry is already reinforced, so stop

		// otherwise prepare and forward the reinforcement on this next entry interface
		int interface = bestEntry->outgoingInterface;
        int instance = bestEntry->instance;

        DataCache new_de = *bestEntry;
		new_de.reinforce();
		m->dcs.erase(new_de);
		m->dcs.insert(new_de);

		TicTocMsg20* newmsg = MessageHelper::newMessage(REINFORCE, sm.data, instance, 0);
    	SendCopyTo(newmsg, interface);
    	delete msg;
    }
	
}

bool HandleReinforcementCommand::fibEntryRule()
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

bool HandleReinforcementCommand::forwardingEntryRule()
{
	
	return false;
}
