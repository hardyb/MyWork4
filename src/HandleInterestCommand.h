#ifndef HandleInterestCommand_h
#define HandleInterestCommand_h


#include "Command.h"
#include "txc20.h"




class HandleInterestCommand : public Command
{
public:
	HandleInterestCommand(Txc20* _m);
	~HandleInterestCommand(void);
	virtual void execute(cMessage *msg);
	bool fibEntryRule();
	bool forwardingEntryRule();
	
};





#endif
