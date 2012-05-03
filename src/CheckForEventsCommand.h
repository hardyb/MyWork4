
#ifndef CheckForEventsCommand_h
#define CheckForEventsCommand_h

#include "Command.h"



class CheckForEventsCommand : public Command
{
public:
	std::ifstream infile;
	CheckForEventsCommand(Txc20* _m);
	~CheckForEventsCommand(void);
	virtual void execute(cMessage *msg);
	void processModuleInstrumentation();
	void processPresentation();
};







#endif
