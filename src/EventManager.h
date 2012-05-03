#ifndef EventManager_h
#define EventManager_h



#include <set>
#include "ScheduledEvent.h"
#include "txc20.h"


//eventSet.insert(ScheduledEvent(2, 0.0, SEND_INTEREST, 2, 0, 0));


//ScheduledEvent e1 = {2, 0.0, SEND_INTEREST, 2, 0, 0};




class EventManager
{
private:
	EventManager();
	std::set<ScheduledEvent*> eventSet;
	cSimulation* sim;
	
public:
	static EventManager& Instance();
	void StartEventsForModule(int id);
	
	
	
};









#endif
