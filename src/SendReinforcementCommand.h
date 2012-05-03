
#ifndef SendReinforcementCommand_h
#define SendReinforcementCommand_h

#include "Command.h"



class SendReinforcementCommand : public Command
{
public:
	SendReinforcementCommand(Txc20* _m);
	~SendReinforcementCommand(void);
	virtual void execute(cMessage *msg);
};







#endif
