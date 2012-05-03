
#ifndef SendDataCommand_h
#define SendDataCommand_h

#include "Command.h"



class SendDataCommand : public Command
{
public:
	SendDataCommand(Txc20* _m);
	~SendDataCommand(void);
	virtual void execute(cMessage *msg);
};







#endif
