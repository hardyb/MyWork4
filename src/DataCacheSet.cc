
#include <sstream>

#include "DataCacheSet.h"


DataCacheSet::DataCacheSet()
{
	
}

DataCacheSet::~DataCacheSet()
{
	
}



bool DataCacheSet::Contains(int _current, int _in, int _out)
{
	for ( std::set<DataCache>::iterator i = begin(); i != end(); i++ )
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

bool DataCacheSet::BestPathInterface(int _current, int _in, int _out, int &_interface)
{
	std::set<DataCache>::iterator bestEntry;
	bool found;
	
	found = BestPathEntry(_current, _in, _out, bestEntry);
	if ( found )
	{
		_interface = bestEntry->outgoingInterface;
	}
	
	return found;
}


	
bool DataCacheSet::BestPathValue(int _current, int _in, int _out, int &_best)
{
	std::set<DataCache>::iterator bestEntry;
	bool found;
	
	found = BestPathEntry(_current, _in, _out, bestEntry);
	if ( found )
	{
		_best = bestEntry->pathValue;
	}
	
	return found;
}


bool DataCacheSet::BestPathEntry(int _current, int _in, int _out, std::set<DataCache>::iterator &_bestentry)
{
	bool found = false;
	int bestValue;
	for ( std::set<DataCache>::iterator i = begin(); i != end(); i++ )
	{
		if (    i->currentState  == _current &&
				i->incomingState == _in      &&
				i->outgoingState == _out         )
		{
			if ( !found || i->pathValue < bestValue )
			{
				found = true;
				bestValue = i->pathValue;
				_bestentry = i;
			}
		}
	}
	
	return found;
}


std::string DataCacheSet::getString()
{
	std::stringstream ss;
	for ( std::set<DataCache>::iterator i = begin(); i != end(); i++ )
	{
		ss << i->getString() << "\n";
	}
	
	return ss.str();
	
}

std::string DataCacheSet::getFullString()
{
	std::stringstream ss;
	for ( std::set<DataCache>::iterator i = begin(); i != end(); i++ )
	{
		ss << i->getFullString();
	}

	return ss.str();

}


std::string DataCacheSet::getFullHeaders()
{
	return DataCache::getFullHeaders();

}
