

#include "SetRoleCommand.h"
#include "MessageHelper.h"


SetRoleCommand::SetRoleCommand(Txc20* _m)
: Command(_m)
{
	
}



void SetRoleCommand::execute(cMessage *msg)
{
	if ( !msg->isSelfMessage() )
	{
	    EV << "Message kind " << msg->getKind() << " is not a self message, but WAS sent to self\n";
		return;
	}
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);

	rd = &(m->moduleRD);

    EV << "Message kind " << gmsg->getKind() << " PROCESSING\n";
    
	std::string  s = gmsg->getData();
	std::stringstream ss(s);

	char size;
	char outMsgSegment;
	char dataSegment;
	char transitionSegment;
	char inMsgSegment;
	char size_of_transitions;
	char num_of_transitions;
	char currentState;



	unsigned char packet[200];
	int i = 0;
	while ( !ss.eof() )
	{
		unsigned int temp;
		ss >> temp;
		packet[i++] = (unsigned char)temp;
	}

	for (int i = 0; i < 4; i++ )
	{
		if ( rd->role[i] == 0 )
		{
			rd->role[i] = (unsigned char*)malloc(packet[0]);
			memcpy(rd->role[i], packet, packet[0]);
			break;
		}
	}


	//unsigned char packet[66] = {
	//66, 10, 12, 26, 5, 0, 6, 0, 7, 0, 8, 0, 44, 1, 255, 0, 232, 3, 0, 0, 231, 3, 0, 0, 0, 0, 0, 8, 6, 20, 0, 0, 8, 4, 18, 0, 0, 8, 8, 22, 1, 1, 1, 24, 18, 2, 2, 10, 24, 22, 3, 3, 6, 24, 20, 4, 3, 7, 24, 20, 0, 4, 4, 10, 22, 0
	//};

	//outMsgSegment = raw_data[1];
	//dataSegment = raw_data[2];
	//inMsgSegment = 4;

	// relies on transitions being at the end
	//unsigned char* raw_data = rd->role[i];
	//size = raw_data[0];
	//transitionSegment = raw_data[3];
	//size_of_transitions = size - transitionSegment;
	//num_of_transitions = size_of_transitions/sizeof(transition);
	//FSM = (transition*)(raw_data+transitionSegment);
    
	
	}
	
	
	
	
	
	
	


