
#ifndef SendAdvertCommand_h
#define SendAdvertCommand_h

#include "Command.h"



class SendAdvertCommand : public Command
{
public:
	SendAdvertCommand(Txc20* _m);
	~SendAdvertCommand(void);
	virtual void execute(cMessage *msg);
};







#endif
