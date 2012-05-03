#ifndef SoftMessage_h
#define SoftMessage_h



#include "txc20.h"


/*
 * This is intended instantiated as a temporary object to facilitate the
 * common action of extracting certain information explicit or implicit in a message
 * and making that easily available to code that is responding to a message just received
 */

class SoftMessage
{
public:
	SoftMessage();
	SoftMessage(TicTocMsg20 *ttmsg, Txc20* m);
	~SoftMessage();

	int kind; // same as generic message
	int interface; // the gate index from the module instance point of view
	int senderModuleIndex; // while all nodes on the network are of the same type, then the index of the node in the whole network 
    
	// TODO
	// These members are an early representation of the data name
	// and need to be made proper
	int data; // the data or state purveyed in the message
	ATransition t[3]; // early example transition set for role data name 
	
	
	
    int msgMinPathConstraint; //  min path value purveyed in the message
    int hopCount; // hop count purveyed in the message
	
	
};


#endif
