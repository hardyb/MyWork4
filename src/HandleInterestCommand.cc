

#include "HandleInterestCommand.h"
#include "SoftMessage.h"
#include "MessageHelper.h"
#include "RoutingAndAggregation.h"


HandleInterestCommand::HandleInterestCommand(Txc20* _m)
: Command(_m)
{
	
}


// THIS IS NOW USED FOR CONTEXT!!!!
void HandleInterestCommand::execute(cMessage *msg)
{
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
	if ( !gmsg->isSelfMessage() )
	{
	    EV << "Message kind " << gmsg->getKind() << " is NOT a self message, but was sent to self\n";
		return;
	}

	std::string  s = gmsg->getData();
	std::stringstream ss(s);

	// so we are getting the context here
	// this will essentially consist of a series of bytes
	// so will be a text file with a series of integer values in text
	// from the C# app'.
	//
	// Here's something from the setrole command to get us started.

	unsigned char packet[200];
	int i = 0;
	while ( !ss.eof() )
	{
		unsigned int temp;
		ss >> temp;
		//if ( (ss.rdstate() & std::stringstream::goodbit ) )
		//{
			packet[i++] = (unsigned char)temp;
		//}
	}
	packet[i] = 0;

	trie_add(rd->top_context, (const char *)packet, CONTEXT);

	//struct RoutingData* rd2 = rd;
	//struct RoutingData* rd3 = rd;

	return;









/*
	SoftMessage sm(ttmsg, m);

	// an entry pointing to self interface (-1) indicates this is the source
	ForwardingEntry selfEntry(0, sm.data, sm.data, -1, 0, 0, -1, 0);
	ForwardingEntrySet::iterator i = m->fib.find(selfEntry);
	if ( i != m->fib.end() )
	{
		return;
	}
	
	
	ForwardingEntry fe(0, sm.data, sm.data, sm.interface, 0, sm.msgMinPathConstraint, sm.senderModuleIndex);

	
	int bestPath;	
	if ( !m->fib.BestPathValue(0, sm.data, sm.data, bestPath) )
	{
		// first ever insert, fib was empty
		m->fib.insert(fe);  
		TicTocMsg20* msg = MessageHelper::newMessage(INTEREST, sm.data, 0, sm.msgMinPathConstraint+m->simpleNodeConstraintValue);  // param 3 hopCount not used
		SendCopyToAllInterfaces(msg);
		delete msg;
	}
	else
	{
		// at least one fib entry, lowest pv obtained
		ForwardingEntrySet::iterator i = m->fib.find(fe);
		if ( i != m->fib.end() )
		{
			// existing fib entry for message interest and interface
			if ( sm.msgMinPathConstraint < i->pathValue)
			{
				// incoming message has better pv than existing fib entry, so overwrite
				m->fib.insert(fe);  
			}
		}
		else
		{
			// NO existing fib entry for message interest and interface
			m->fib.insert(fe);  
			
		}
		
		if ( sm.msgMinPathConstraint < bestPath )
		{
			TicTocMsg20* msg = MessageHelper::newMessage(INTEREST, sm.data, 0, sm.msgMinPathConstraint+m->simpleNodeConstraintValue);
			SendCopyToAllInterfaces(msg);
			delete msg;
		}
	
	}
*/
	
}

bool HandleInterestCommand::fibEntryRule()
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

bool HandleInterestCommand::forwardingEntryRule()
{
	
	return false;
}
