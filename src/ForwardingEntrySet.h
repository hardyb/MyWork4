#ifndef ForwardingEntrySet_h
#define ForwardingEntrySet_h


#include <set>
#include <string>
#include "ForwardingEntry.h"



class ForwardingEntrySet : public std::set<ForwardingEntry>
{
public:
	ForwardingEntrySet();
	~ForwardingEntrySet();
	bool Contains(int _current, int _in, int _out);
	bool BestPathValue(int _current, int _in, int _out, int &_best);
	std::set<ForwardingEntry> OutInterfaceSet(int _out, int _interface);
	std::set<ForwardingEntry> CurrentInSet(int _current, int _in);
	std::set<ForwardingEntry> InSet(int _out);
	std::set<ForwardingEntry> OutSet(int _out);
	std::string getString();
	std::string getFullString();
	static std::string getFullHeaders();

	
};






#endif
