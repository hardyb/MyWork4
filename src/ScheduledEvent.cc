



#include "ScheduledEvent.h"
#include "MessageHelper.h"



ScheduledEvent::ScheduledEvent(std::string _fromModulePath, simtime_t _absoluteTime, int _kind, int _data, int _mPathCon, int _hopCount) :
absoluteTime(_absoluteTime),
kind(_kind),
data(_data),
mPathCon(_mPathCon),
hopCount(_hopCount)
{
	fromModulepath = _fromModulePath;
	cSimulation* sim = cSimulation::getActiveSimulation();
	fromModule = check_and_cast<Txc20 *>(sim->getModuleByPath(_fromModulePath.c_str()));
	fromModuleId = fromModule->getId();
	fromModuleIndex = fromModule->getIndex();
	
}

//TODO consider improving the way this knows which module
void ScheduledEvent::start()
{
	TicTocMsg20* msg = MessageHelper::newMessage(kind, data, hopCount, mPathCon);
	
	fromModule->scheduleAt(absoluteTime, msg);
	
	
}





