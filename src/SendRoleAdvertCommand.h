#ifndef SendRoleAdvertCommand_h
#define SendRoleAdvertCommand_h


#include "Command.h"
#include "txc20.h"




class SendRoleAdvertCommand : public Command
{
public:
	std::set<int> inputnames;
	std::set<int> outputnames;
	SendRoleAdvertCommand(Txc20* _m);
	~SendRoleAdvertCommand(void);
	virtual void execute(cMessage *msg);
	void setGoodPositionValue(ATransition *t);
	
};





#endif
