#ifndef HandleMoveModuleCommand_h
#define HandleMoveModuleCommand_h


#include "Command.h"
#include "txc20.h"
#include "SoftMessage.h"




class HandleMoveModuleCommand : public Command
{
public:
	HandleMoveModuleCommand(Txc20* _m);
	~HandleMoveModuleCommand(void);
	virtual void execute(cMessage *msg);
	
};





#endif
