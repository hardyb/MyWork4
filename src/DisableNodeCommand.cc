

#include "DisableNodeCommand.h"
#include "MessageHelper.h"
#include "txc20.h"


DisableNodeCommand::DisableNodeCommand(Txc20* _m)
: Command(_m)
{
	
}



void DisableNodeCommand::execute(cMessage *msg)
{
	
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
	if ( !gmsg->isSelfMessage() )
	{
	    EV << "Message kind " << gmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	    //exit(-1);
	}
    //m->getDisplayString().setTagArg("i",0,"block/source");

	std::string  s = gmsg->getData();
	std::stringstream ss(s);
	int data;
	ss >> data;
	
    int n = m->gateSize("gate");
    for ( int i = 0; i < n; i++ )
    {
    	cGate* g = m->gate("gate$o", i);
        cGate* ig = m->gate("gate$i", i);
        if ( g && ig )
        {
            cDelayChannel *chan1  = check_and_cast<cDelayChannel *>(g->getChannel());
        	chan1->setDisabled(!chan1->isDisabled());
        	if ( chan1->isDisabled() )
        	{
                chan1->setDisplayString("ls=,0");
        	}
        	else
        	{
                chan1->setDisplayString("ls=,2");
        	}
            
            cGate*  ng = ig->getPreviousGate();
            cDelayChannel *chan2  = check_and_cast<cDelayChannel *>(ng->getChannel());
        	chan2->setDisabled(!chan2->isDisabled());
        	if ( chan2->isDisabled() )
        	{
                chan2->setDisplayString("ls=,0");
        	}
        	else
        	{
                chan2->setDisplayString("ls=,2");
        	}
        }
    }
	
}


