

/*


string name;
string rent;

ifstream infile;
infile.open ("names.txt");
infile >> name >> rent;

cout << name << rent << endl;

infile.close();






*/


#include "EventManager.h"

#include <fstream>
//#include <iostream>
#include <string>
//#include <conio.h>



//getModuleByPath

// cSimulation* sim = cSimulation::getActiveSimulation();
 
 
 //"Tictoc20.tic[2]"


EventManager::EventManager()
{
    EV << "Constructing EventManager\n";
	sim = cSimulation::getActiveSimulation();
	std::ifstream infile;
	infile.open("TheEvents.txt");

	while ( !infile.eof() )
	{
		std::string modulePath;
		simtime_t absoluteTime;
		float absoluteTimeInput;
		int kind;
		int data;
		int mPathCon;
		int hopCount;
		
	    EV << "Reading a file line\n";
		infile >> modulePath >> absoluteTimeInput >> kind >> data >> mPathCon >> hopCount;
		absoluteTime = absoluteTimeInput;
	    EV << "Inserting a scheduled event\n";
		eventSet.insert(new ScheduledEvent(modulePath, absoluteTime, kind, data, mPathCon, hopCount));
	}
	
	infile.close();
	
}



EventManager& EventManager::Instance()
{
	static EventManager em;
	return em;
}


//TODO consider improving the way this knows which module
void EventManager::StartEventsForModule(int id)
{
    EV << "StartEventsForModule for: " << cSimulation::getActiveSimulation()->getModule(id)->getFullPath() << "\n";
	for ( std::set<ScheduledEvent*>::iterator i = eventSet.begin(); i != eventSet.end(); i++ )
	{
	    EV << "Checking module " << (*i)->fromModuleIndex << "\n";
		if (    (*i)->fromModuleId  == id )
		{
		    EV << "Starting module " << (*i)->fromModuleIndex << "\n";
			(*i)->start();
		}
	}
	
}

//cSimulation::getActiveSimulation()->getModuleByPath();

