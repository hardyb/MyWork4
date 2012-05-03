#ifndef Command_h
#define Command_h

//#include "txc20.h"
#include "tictoc20_m.h"
#include "GenericMessage_m.h"

#define SET_CONTEXT 5

#define SEND_INTEREST 0
#define SEND_ADVERTISE 1
#define SEND_DATA 2
#define DISABLE_NODE 3
#define ENABLE_NODE 4
//#define INTEREST 5
#define ADVERTISE 6
#define DATA 7
#define SEND_REINFORCE 8
#define REINFORCE 9
#define CHECK_FOR_EVENTS 10
#define ADVERTISE_ROLE 11
#define ROLE_ADVERT 12
#define MOVE_MODULE 13
#define SET_ROLE 14
#define NODE_STARTUP 15
#define NEIGHBOR_BROADCAST 16
#define NEIGHBOR_MESSAGE 17
#define ROUTING_MESSAGE 18


/*
char xx[][] = { "SEND_INTEREST",
"SEND_ADVERTISE",
"SEND_DATA",
"DISABLE_NODE",
"ENABLE_NODE",
"SET_CONTEXT",
"ADVERTISE",
"DATA",
"SEND_REINFORCE",
"REINFORCE",
"CHECK_FOR_EVENTS",
"ADVERTISE_ROLE",
"ROLE_ADVERT",
"MOVE_MODULE",
"SET_ROLE",
"NODE_STARTUP",
"NEIGHBOR_BROADCAST",
"NEIGHBOR_MESSAGE"}
*/




class Txc20;

class Command
{
public:
	Command();
	Command(Txc20* _m);
	~Command(void);
	virtual void execute(cMessage *msg);
	bool SendCopyTo(TicTocMsg20 *ttmsg, int _interface);
	bool SendCopyToModule(TicTocMsg20 *ttmsg, int _moduleID);
	void SendCopyToAllInterfaces(TicTocMsg20 *ttmsg, int exceptInterface = -1);
	void SendCopyToAllInterfaces(GenericMessage *ttmsg, int exceptInterface = -1);
	Txc20* m;
	int dummy;
};

#endif
