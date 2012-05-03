

#include <sstream>

#include "ForwardingEntry.h"


const int ForwardingEntry::lowestInterface = 0;

ForwardingEntry::ForwardingEntry() :
currentState(0),
incomingState(0),
outgoingState(0),
outgoingInterface(0),
pathValue(0),
interfaceModuleIndex(0),
reinforced(false)
{
}

ForwardingEntry::ForwardingEntry(int current, int incoming, int outgoing, int theInterface, int _instance, int value, 	int _interfaceModuleIndex, bool _reinforced) :
currentState(current),
incomingState(incoming),
outgoingState(outgoing),
instance(_instance),
outgoingInterface(theInterface),
pathValue(value),
interfaceModuleIndex(_interfaceModuleIndex),
reinforced(_reinforced)
{
}

ForwardingEntry::~ForwardingEntry(void)
{
}

bool ForwardingEntry::operator< ( const ForwardingEntry& _right ) const
{
	static int n = 4;
	static int theseEntryElements[4];
	static int thoseEntryElements[4];
	theseEntryElements[0] = currentState;
	theseEntryElements[1] = incomingState;
	theseEntryElements[2] = outgoingState;
	theseEntryElements[3] = outgoingInterface;
	thoseEntryElements[0] = _right.currentState;
	thoseEntryElements[1] = _right.incomingState;
	thoseEntryElements[2] = _right.outgoingState;
	thoseEntryElements[3] = _right.outgoingInterface;

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

bool ForwardingEntry::operator== ( const ForwardingEntry& _right ) const
{
	static int n = 4;
	static int theseEntryElements[4];
	static int thoseEntryElements[4];
	theseEntryElements[0] = currentState;
	theseEntryElements[1] = incomingState;
	theseEntryElements[2] = outgoingState;
	theseEntryElements[3] = outgoingInterface;
	thoseEntryElements[0] = _right.currentState;
	thoseEntryElements[1] = _right.incomingState;
	thoseEntryElements[2] = _right.outgoingState;
	thoseEntryElements[3] = _right.outgoingInterface;

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


void ForwardingEntry::reinforce() 
{
	reinforced = true;
	
}


std::string ForwardingEntry::getString() const
{
	std::stringstream ss;
	//ss << currentState << " " << incomingState << " " << outgoingState << " " << interfaceModuleIndex << " " << pathValue;
	//ss << currentState << " " << incomingState << " " << outgoingState << " " << interfaceModuleIndex << " " << pathValue << " " << reinforced;
	//ss << incomingState << " " << instance << " " << interfaceModuleIndex << " " << pathValue << " " << reinforced;
	
	
	ss << currentState << " " << incomingState << " " << outgoingState << " " << interfaceModuleIndex << " " << pathValue << reinforced;
	
	
	
	return ss.str();
	
}

std::string ForwardingEntry::getFullHeaders()
{
	std::stringstream ss;

	ss << "CURR" << "\t" << "INCO" << "\t" << "OUTG" << "\t" << "INST" << "\t"
			<< "INTF" << "\t" << "PATH" << "\t" << "MODU" << "\t" << "REIN" << std::endl;

	return ss.str();
}


std::string ForwardingEntry::getFullString() const
{
	std::stringstream ss;

	ss << ForwardingEntry::stateText(currentState) << "\t" << incomingState << "\t" <<
			outgoingState << "\t"
			<< instance << "\t" << ForwardingEntry::outgoingInterfaceText(outgoingInterface)
			<< "\t" << pathValue << "\t" << interfaceModuleIndex << "\t" << reinforced
			<< std::endl;

	return ss.str();
}

std::string ForwardingEntry::outgoingInterfaceText(int _outgoingInterface)
{
	std::string text;
	switch ( _outgoingInterface )
	{
		case SELF_INTERFACE:
			text = "SELF";
			break;
		case UNKNOWN_INTERFACE:
			text = "UNKN";
			break;
		default:
			std::stringstream out;
			out << _outgoingInterface;
			text = out.str();
	}

	return text;
}

std::string ForwardingEntry::stateText(int _state)
{
	std::string text;
	switch ( _state )
	{
		case ANY_STATE:
			text = "ANY";
			break;
		default:
			std::stringstream out;
			out << _state;
			text = out.str();
	}

	return text;
}
