#ifndef SetRoleCommand_h
#define SetRoleCommand_h


#include "Command.h"
#include "txc20.h"
#include "SoftMessage.h"




class SetRoleCommand : public Command
{
public:
	SetRoleCommand(Txc20* _m);
	~SetRoleCommand(void);
	virtual void execute(cMessage *msg);
	
};





#endif
