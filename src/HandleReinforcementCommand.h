#ifndef HandleReinforcementCommand_h
#define HandleReinforcementCommand_h


#include "Command.h"
#include "txc20.h"




class HandleReinforcementCommand : public Command
{
public:
	HandleReinforcementCommand(Txc20* _m);
	~HandleReinforcementCommand(void);
	virtual void execute(cMessage *msg);
	bool fibEntryRule();
	bool forwardingEntryRule();
	
};





#endif
