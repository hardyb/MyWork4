#ifndef HandleNeighborCommand_h
#define HandleNeighborCommand_h


#include "Command.h"
#include "txc20.h"




class HandleNeighborCommand : public Command
{
public:
	HandleNeighborCommand(Txc20* _m);
	~HandleNeighborCommand(void);
	virtual void execute(cMessage *msg);
	//void process(State* s);
	int newNeighbor;
	
};





#endif
