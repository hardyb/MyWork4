
#include <sstream>

#include "ForwardingEntrySet.h"


ForwardingEntrySet::ForwardingEntrySet()
{
	
}

ForwardingEntrySet::~ForwardingEntrySet()
{
	
}


std::set<ForwardingEntry> ForwardingEntrySet::OutInterfaceSet(int _out, int _interface)
{
	std::set<ForwardingEntry> x;

	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		if ( i->outgoingState == _out &&
				i->outgoingInterface == _interface )
		{
			x.insert(*i);
		}
	}

	return x;

}




std::set<ForwardingEntry> ForwardingEntrySet::CurrentInSet(int _current, int _in)
{
	std::set<ForwardingEntry> x;

	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		if ( i->incomingState == _in &&
				i->currentState == _current )
		{
			x.insert(*i);
		}
	}

	return x;

}



std::set<ForwardingEntry> ForwardingEntrySet::InSet(int _in)
{
	std::set<ForwardingEntry> x;

	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		if ( i->incomingState == _in )
		{
			x.insert(*i);
		}
	}

	return x;

}



std::set<ForwardingEntry> ForwardingEntrySet::OutSet(int _out)
{
	std::set<ForwardingEntry> x;

	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		if ( i->outgoingState == _out )
		{
			x.insert(*i);
		}
	}

	return x;

}

bool ForwardingEntrySet::Contains(int _current, int _in, int _out)
{
	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		if (    i->currentState  == _current &&
				i->incomingState == _in      &&
				i->outgoingState == _out         )
		{
			return true;
		}
	}
	
	return false;
	
}
	
bool ForwardingEntrySet::BestPathValue(int _current, int _in, int _out, int &_best)
{
	bool found = false;
	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		if (    i->currentState  == _current &&
				i->incomingState == _in      &&
				i->outgoingState == _out         )
		{
			if ( !found || i->pathValue < _best )
			{
				found = true;
				_best = i->pathValue;
			}
		}
	}
	
	return found;
	
}


std::string ForwardingEntrySet::getString()
{
	std::stringstream ss;
	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		ss << i->getString() << std::endl;
	}
	
	return ss.str();
	
}

std::string ForwardingEntrySet::getFullString()
{
	std::stringstream ss;
	for ( std::set<ForwardingEntry>::iterator i = begin(); i != end(); i++ )
	{
		ss << i->getFullString();
	}

	return ss.str();

}


std::string ForwardingEntrySet::getFullHeaders()
{
	return ForwardingEntry::getFullHeaders();

}
