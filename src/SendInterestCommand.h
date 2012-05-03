
#ifndef SendInterestCommand_h
#define SendInterestCommand_h

#include "Command.h"



class SendInterestCommand : public Command
{
public:
	SendInterestCommand(Txc20* _m);
	~SendInterestCommand(void);
	virtual void execute(cMessage *msg);
};







#endif
