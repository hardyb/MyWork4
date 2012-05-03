
#ifndef DisableNodeCommand_h
#define DisableNodeCommand_h

#include "Command.h"



class DisableNodeCommand : public Command
{
public:
	DisableNodeCommand(Txc20* _m);
	~DisableNodeCommand(void);
	virtual void execute(cMessage *msg);
};







#endif
