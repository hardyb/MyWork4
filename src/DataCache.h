//#pragma once
#ifndef DataCache_h
#define DataCache_h

#include <string>


class DataCache
{
public:
	DataCache();
	DataCache(int current, int incoming, int outgoing, int interface, int value, int _pathvalue, int _interfaceModuleIndex, int _broken, int _reinforced, int instance);
	~DataCache(void);
	bool operator< ( const DataCache& _right ) const;
	bool operator== ( const DataCache& _right ) const;
	void reinforce(); 
	std::string getString() const;
	static std::string getFullHeaders();
	std::string getFullString() const;
	static std::string outgoingInterfaceText(int _outgoingInterface);
	
	int currentState;
	int incomingState;
	int outgoingState;
	int instance;
	int outgoingInterface;
	int gradientValue;
	int pathValue;
	int interfaceModuleIndex;
	int broken;
	int reinforced;
};




#endif
