#ifndef DataCacheSet_h
#define DataCacheSet_h


#include <set>
#include <string>
#include "DataCache.h"



class DataCacheSet : public std::set<DataCache>
{
public:
	DataCacheSet();
	~DataCacheSet();
	bool Contains(int _current, int _in, int _out);
	bool BestPathValue(int _current, int _in, int _out, int &_best);
	bool BestPathInterface(int _current, int _in, int _out, int &_interface);
	std::string getString();
	bool BestPathEntry(int _current, int _in, int _out, std::set<DataCache>::iterator &_bestentry);
	std::string getFullString();
	static std::string getFullHeaders();
	
};






#endif
