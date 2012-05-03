#ifndef HandleRoleAdvertCommand_h
#define HandleRoleAdvertCommand_h


#include "Command.h"
#include "txc20.h"
#include "SoftMessage.h"




class HandleRoleAdvertCommand : public Command
{
public:
	HandleRoleAdvertCommand(Txc20* _m);
	~HandleRoleAdvertCommand(void);
	virtual void execute(cMessage *msg);
	void setGoodPositionValue(SoftMessage &sm);
	bool fibEntryRule();
	bool forwardingEntryRule();
	
};





#endif
