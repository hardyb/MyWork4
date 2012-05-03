

#include "SendInterestCommand.h"
#include "MessageHelper.h"
#include "txc20.h"


SendInterestCommand::SendInterestCommand(Txc20* _m)
: Command(_m)
{
	
}



void SendInterestCommand::execute(cMessage *msg)
{
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
	if ( !gmsg->isSelfMessage() )
	{
	    EV << "Message kind " << gmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	    //exit(-1);
	}
    m->getDisplayString().setTagArg("i",0,"block/sink");

	std::string  s = gmsg->getData();
	std::stringstream ss(s);
	int data;
	ss >> data;
	
	// currently hopcount zero (3rd param) use zero mpe to start (4th param)
	TicTocMsg20* newmsg = MessageHelper::newMessage(INTEREST, data, 0, 0);
	SendCopyToAllInterfaces(newmsg);
	
	
	// add an interest FIB entry pointing to interface self
	ForwardingEntry fe(0, data, data, -1, 0, 0, -1, 0);
	m->fib.erase(fe);  
	m->fib.insert(fe);  
	
	delete newmsg;
	
}


