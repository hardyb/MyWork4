#ifndef ScheduledEvent_h
#define ScheduledEvent_h


#include <omnetpp.h>
#include <string>
#include "txc20.h"


class ScheduledEvent
{
public:
	ScheduledEvent();
	ScheduledEvent(std::string _fromModulePath, simtime_t _absoluteTime, int _kind, int _data, int _mPathCon, int _hopCount);
	void start();
	int fromModuleIndex;
	std::string fromModulepath;
	int fromModuleId;
	Txc20* fromModule;
	simtime_t absoluteTime;
	int kind;
	int data;
	int mPathCon;
	int hopCount;
};



#endif
