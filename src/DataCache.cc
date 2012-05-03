

#include <sstream>



#include "DataCache.h"

DataCache::DataCache() :
currentState(0),
incomingState(0),
outgoingState(0),
instance(0),
outgoingInterface(0),
gradientValue(0),
pathValue(0),
broken(0),
reinforced(0)
{
}





DataCache::DataCache(int current, int incoming, int outgoing, int theInterface, int value, int _pathvalue, int _interfaceModuleIndex, int _broken, int _reinforced, int _instance) :
currentState(current),
incomingState(incoming),
outgoingState(outgoing),
instance(_instance),
outgoingInterface(theInterface),
gradientValue(value),
pathValue(_pathvalue),
interfaceModuleIndex(_interfaceModuleIndex),
broken(_broken),
reinforced(_reinforced)
{
	
	
}

DataCache::~DataCache(void)
{
}

bool DataCache::operator< ( const DataCache& _right ) const
{
	static int n = 4;
	static int theseEntryElements[4];
	static int thoseEntryElements[4];
	theseEntryElements[0] = currentState;
	theseEntryElements[1] = incomingState;
	theseEntryElements[2] = outgoingState;
	theseEntryElements[3] = outgoingInterface;
	//theseEntryElements[4] = gradientValue;
	//theseEntryElements[5] = pathValue;
	//theseEntryElements[6] = broken;
	//theseEntryElements[7] = reinforced;
	thoseEntryElements[0] = _right.currentState;
	thoseEntryElements[1] = _right.incomingState;
	thoseEntryElements[2] = _right.outgoingState;
	thoseEntryElements[3] = _right.outgoingInterface;
	//thoseEntryElements[4] = _right.gradientValue;

	// ForwardingEntry f3(1,2,7,8);
	// ForwardingEntry f4(1,3,0,0);
	// std::cout << (f3 < f4) << std::endl; // not true!!


	for ( int i = 0; i < n; i++ )
	{
		if ( theseEntryElements[i] < thoseEntryElements[i] )
		{
			return true;
		}

		if ( theseEntryElements[i] > thoseEntryElements[i] )
		{
			return false;
		}

		if ( theseEntryElements[i] == thoseEntryElements[i] )
		{
			continue;
		}
	}

	return false;

}

bool DataCache::operator== ( const DataCache& _right ) const
{
	static int n = 4;
	static int theseEntryElements[4];
	static int thoseEntryElements[4];
	theseEntryElements[0] = currentState;
	theseEntryElements[1] = incomingState;
	theseEntryElements[2] = outgoingState;
	theseEntryElements[3] = outgoingInterface;
	//theseEntryElements[4] = gradientValue;
	thoseEntryElements[0] = _right.currentState;
	thoseEntryElements[1] = _right.incomingState;
	thoseEntryElements[2] = _right.outgoingState;
	thoseEntryElements[3] = _right.outgoingInterface;
	//thoseEntryElements[4] = _right.gradientValue;

	for ( int i = 0; i < n; i++ )
	{
		if ( theseEntryElements[i] < thoseEntryElements[i] )
		{
			return false;
		}

		if ( theseEntryElements[i] > thoseEntryElements[i] )
		{
			return false;
		}

		if ( theseEntryElements[i] == thoseEntryElements[i] )
		{
			continue;
		}
	}

	return true;

}


void DataCache::reinforce() 
{
	reinforced = 1;
	
}


std::string DataCache::getString() const
{
	std::stringstream ss;
	//ss << currentState << " " << incomingState << " " << outgoingState << " " << interfaceModuleIndex << " " << pathValue << " " << reinforced;
	ss << incomingState << " " << instance << " " << interfaceModuleIndex << " " << pathValue << " " << reinforced;
	return ss.str();
	
}

std::string DataCache::getFullHeaders()
{
	std::stringstream ss;
	ss << "CURR" << "\t" << "INCO" << "\t" << "OUTG" << "\t" << "INST" << "\t"
			<< "INTF" << "\t" << "GRAD" << "\t" << "PATH" << "\t" << "MODU" << "\t"
			<< "BROK" << "\t" << "REIN" << std::endl;
	return ss.str();
}

std::string DataCache::getFullString() const
{
	std::stringstream ss;
	ss << currentState << "\t" << incomingState << "\t" << outgoingState << "\t"
			<< instance << "\t" << DataCache::outgoingInterfaceText(outgoingInterface)
			<< "\t" << gradientValue << "\t" << pathValue << "\t" << interfaceModuleIndex
			<< "\t" << broken << "\t" << reinforced
			<< std::endl;
	return ss.str();
}


std::string DataCache::outgoingInterfaceText(int _outgoingInterface)
{
	std::string text;
	switch ( _outgoingInterface )
	{
		case -1:
			text = "SELF";
			break;
		case -2:
			text = "UNKN";
			break;
		default:
			std::stringstream out;
			out << _outgoingInterface;
			text = out.str();
	}
	return text;
}

