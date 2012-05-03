
#ifndef NodeStartupCommand_h
#define NodeStartupCommand_h

#include "Command.h"



class NodeStartupCommand : public Command
{
public:
	NodeStartupCommand(Txc20* _m);
	~NodeStartupCommand(void);
	virtual void execute(cMessage *msg);
};







#endif
