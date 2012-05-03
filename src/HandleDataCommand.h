
#ifndef HandleDataCommand_h
#define HandleDataCommand_h

#include "Command.h"



class HandleDataCommand : public Command
{
public:
	HandleDataCommand(Txc20* _m);
	~HandleDataCommand(void);
	virtual void execute(cMessage *msg);
};







#endif
