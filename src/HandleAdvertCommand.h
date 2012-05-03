#ifndef HandleAdvertCommand_h
#define HandleAdvertCommand_h


#include "Command.h"
#include "txc20.h"




class HandleAdvertCommand : public Command
{
public:
	HandleAdvertCommand(Txc20* _m);
	~HandleAdvertCommand(void);
	virtual void execute(cMessage *msg);
	bool fibEntryRule();
	bool forwardingEntryRule();
	
};





#endif
