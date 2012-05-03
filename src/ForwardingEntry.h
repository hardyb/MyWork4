//#pragma once
#ifndef ForwardingEntry_h
#define ForwardingEntry_h


#include <string>

#define ANY_STATE 0
#define SELF_INTERFACE -1
#define UNKNOWN_INTERFACE -2



class ForwardingEntry
{
public:
	ForwardingEntry();
	ForwardingEntry(int current, int incoming, int outgoing, int interface, int _instance, int value = 0, 	int _interfaceModuleIndex = -1, bool _reinforced = false);
	~ForwardingEntry(void);
	// Sorting only on currentState, incomingState, outgoingState, outgoingInterface
	bool operator< ( const ForwardingEntry& _right ) const;
	bool operator== ( const ForwardingEntry& _right ) const;
	void reinforce(); 
	std::string getString() const;
	static std::string getFullHeaders();
	std::string getFullString() const;
	static std::string outgoingInterfaceText(int _outgoingInterface);
	static std::string stateText(int _state);

	
	int currentState;
	int incomingState;
	int outgoingState;
	int instance;
	int outgoingInterface;
	int pathValue;
	int interfaceModuleIndex;
	static const int lowestInterface;
	bool reinforced;
};


#endif
