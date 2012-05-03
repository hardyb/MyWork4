

#include "HandleRoleAdvertCommand.h"
#include "MessageHelper.h"



HandleRoleAdvertCommand::HandleRoleAdvertCommand(Txc20* _m)
: Command(_m)
{
	
}



void HandleRoleAdvertCommand::execute(cMessage *msg)
{
	TicTocMsg20 *ttmsg = check_and_cast<TicTocMsg20 *>(msg);
	if ( ttmsg->isSelfMessage() )
	{
	    EV << "Message kind " << ttmsg->getKind() << " is not a self message, but WAS sent to self\n";
		return;
	    //exit(-1);
	}
	
	SoftMessage sm(ttmsg, m);
	
	// not used though at the moment
	DataCache dc(0, sm.data, sm.data, sm.interface, 0, sm.msgMinPathConstraint, sm.senderModuleIndex, 0, 0, sm.hopCount);
	
	
	int newBestPositionValue = sm.data;
	
	if ( !m->goodPositionValueSet )
	{
		setGoodPositionValue(sm);
		if ( newBestPositionValue < m->bestPositionValue )
		{
			m->bestPositionValue = newBestPositionValue; 
			m->bestPositionIsMe = false;
		}
		TicTocMsg20* msg = MessageHelper::newMessage(ROLE_ADVERT, m->bestPositionValue, 0, 0, sm.t);  // hopCount & pathValue not used just now
		SendCopyToAllInterfaces(msg);
		delete msg;
	}
	else
	{
		if ( newBestPositionValue < m->bestPositionValue )
		{
			m->bestPositionValue = newBestPositionValue; 
			m->bestPositionIsMe = false;
			TicTocMsg20* msg = MessageHelper::newMessage(ROLE_ADVERT, m->bestPositionValue, 0, 0, sm.t);  // hopCount & pathValue not used just now
			SendCopyToAllInterfaces(msg);
			delete msg;
		}
		
	}
	
    char buf[100];
    char* buf_i = buf;
    sprintf(buf_i, "ME: %d(%d) BEST: %d\n", m->goodPositionValue, m->bestPositionIsMe, m->bestPositionValue);
    m->getDisplayString().setTagArg("t",0,buf);
	
	return;
	
	//==========================================
	
	
	
	
	
	

	int bestPath;
	if ( !m->dcs.BestPathValue(0, sm.data, sm.data, bestPath) )
	{
		// first ever insert, fib was empty
		m->dcs.insert(dc);  
		TicTocMsg20* msg = MessageHelper::newMessage(ROLE_ADVERT, sm.data, 0, sm.msgMinPathConstraint+m->simpleNodeConstraintValue, sm.t);  // param 3 hopCount not used
		SendCopyToAllInterfaces(msg);
		delete msg;
	}
	else
	{
		// at least one fib entry, lowest pv obtained
		DataCacheSet::iterator i = m->dcs.find(dc);
		if ( i != m->dcs.end() )
		{
			// existing fib entry for message interest and interface
			if ( sm.msgMinPathConstraint < i->pathValue)
			{
				// incoming message has better pv than existing fib entry, so overwrite
				m->dcs.insert(dc);  
			}
		}
		else
		{
			// NO existing fib entry for message interest and interface
			m->dcs.insert(dc);  
			
		}
		
		if ( sm.msgMinPathConstraint < bestPath )
		{
			TicTocMsg20* msg = MessageHelper::newMessage(ROLE_ADVERT, sm.data, 0, sm.msgMinPathConstraint+m->simpleNodeConstraintValue, sm.t);
			SendCopyToAllInterfaces(msg);
			delete msg;
		}

	}
	
	
	
	
	
	
	
}

bool HandleRoleAdvertCommand::fibEntryRule()
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

bool HandleRoleAdvertCommand::forwardingEntryRule()
{
	
	return false;
}

void HandleRoleAdvertCommand::setGoodPositionValue(SoftMessage &sm)
{
	// early code to create suitability value
	// this is actually WRONG for at least two reasons:
	// 1. We may count the best path to the same source/sink twice, eg: in the case here of '3' { {0,3,1}, {1,4,2}, {1,3,0} }
	// 2. Where a high value means high cost, a failure to have any path to a source/sink would (wrongly) 'improve' the suitability!
	//
	// SOLUTIONS FOR ?
	// 2. Make the higher the value, the lower the cost & visa versa - This may still be no good
	//    because we may get some high value for other sources.
	// 2. Looks like for sources we need some basic boolean suitability test and/or some level of functional suitability
	//    before looking at performance suitability.  It may be that we CAN however cope with not all the sinks, since 
	//    the current state is still important for the FSM even if it is not notified any where.
	//
	// 1. Maybe we should add the datanames (we are counting best path for) into a set, so there are no duplicates, or maybe
	//    we should assign the value to mapping and then add them up.
	
	/*
	If we have paths to all the sources then we can respond.
	Make a list of all the source data names
	For all the data names (not each occurance of each data name) compile a minimum path sum value
	Make a list of all the sink data names
	For all the data names (not each occurance of each data name) compile a minimum path sum value
	
	Another idea: have a weighting for value based on whether sources for all interests are known or just a subset
	eg *50.  So for example all nodes may be 100 or 150 and so on then small values to fine adjust.  If a node for
	some reason does not have a path value for all interests/sources then it's suitability will be greatly reduced.
	 
	*/
	
	
	// value for transition trigger index 0
	int in0 = sm.t[0].getInStateTrigger();
	int bestIn0 = 0;
	m->dcs.BestPathValue(0, in0, in0, bestIn0);
	
	// value for transition trigger index 1
	int in1 = sm.t[1].getInStateTrigger();
	int bestIn1 = 0;
	m->dcs.BestPathValue(0, in1, in1, bestIn1);
	
	// value for transition trigger index 2
	int in2 = sm.t[2].getInStateTrigger();
	int bestIn2 = 0;
	m->dcs.BestPathValue(0, in2, in2, bestIn2);
	
	//==========================================
	
	// value for transition trigger index 0
	int out0 = sm.t[0].getOutState();
	int bestOut0 = 0;
	m->fib.BestPathValue(0, out0, out0, bestOut0);
	
	// value for transition trigger index 1
	int out1 = sm.t[1].getOutState();
	int bestOut1 = 0;
	m->fib.BestPathValue(0, out1, out1, bestOut1);
	
	// value for transition trigger index 2
	int out2 = sm.t[2].getOutState();
	int bestOut2 = 0;
	m->fib.BestPathValue(0, out2, out2, bestOut2);
	
	//==========================================
	m->goodPositionValue = bestIn0 + bestIn1 + bestIn2 + bestOut0 + bestOut1 + bestOut2 + m->simpleNodeConstraintValue;
	m->bestPositionValue = m->goodPositionValue; 
	m->bestPositionIsMe = true;
	m->goodPositionValueSet = true;
	
	
}



/*
SoftMessage sm(ttmsg, m);
DataCache dc(0, sm.data, sm.data, sm.interface, 0, sm.msgMinPathConstraint, sm.senderModuleIndex, 0, 0);

int bestPath;	
if ( !m->dcs.BestPathValue(0, sm.data, sm.data, bestPath) )
{
	// first ever insert, fib was empty
	m->dcs.insert(dc);  
	TicTocMsg20* msg = MessageHelper::newMessage(ADVERTISE, sm.data, 0, sm.msgMinPathConstraint+m->simpleNodeConstraintValue);  // param 3 hopCount not used
	SendCopyToAllInterfaces(msg);
	delete msg;
}
else
{
	// at least one fib entry, lowest pv obtained
	DataCacheSet::iterator i = m->dcs.find(dc);
	if ( i != m->dcs.end() )
	{
		// existing fib entry for message interest and interface
		if ( sm.msgMinPathConstraint < i->pathValue)
		{
			// incoming message has better pv than existing fib entry, so overwrite
			m->dcs.insert(dc);  
		}
	}
	else
	{
		// NO existing fib entry for message interest and interface
		m->dcs.insert(dc);  
		
	}
	
	if ( sm.msgMinPathConstraint < bestPath )
	{
		TicTocMsg20* msg = MessageHelper::newMessage(ADVERTISE, sm.data, 0, sm.msgMinPathConstraint+m->simpleNodeConstraintValue);
		SendCopyToAllInterfaces(msg);
		delete msg;
	}

}
*/
