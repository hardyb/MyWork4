

#include "HandleMoveModuleCommand.h"
#include "MessageHelper.h"


HandleMoveModuleCommand::HandleMoveModuleCommand(Txc20* _m)
: Command(_m)
{
	
}



void HandleMoveModuleCommand::execute(cMessage *msg)
{
	if ( !msg->isSelfMessage() )
	{
	    EV << "Message kind " << msg->getKind() << " is not a self message, but WAS sent to self\n";
		return;
	    //exit(-1);
	}
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
    EV << "Message kind " << gmsg->getKind() << " PROCESSING\n";
    
	std::string  s = gmsg->getData();
	std::stringstream ss(s);
	std::string x;
	std::string y;
	ss >> x;
	ss >> y;
	m->getDisplayString().setTagArg("p",0,x.c_str());
	m->getDisplayString().setTagArg("p",1,y.c_str());
	
	
	
    //int n = m->gateSize("gate");
    //char buf[200];
    //char* buf_i = buf;
    //sprintf(buf_i, "Num gates: %d\n", n);
    //getDisplayString().setTagArg("tt",0,buf);
    
    //char buf[200];
    //char* buf_i = buf;
    //sprintf(buf_i, "red");
    //char buf2[200];
    //char* buf2_i = buf2;
    //sprintf(buf2_i, "3");
    //getDisplayString().setTagArg("tt",0,buf);

    //cGate* g = m->gate("gate$o",0);
    //cGate* ig = m->gate("gate$i",0);
    //if ( g && ig )
    //{
      //  cChannel *chan1  = g->getChannel();
        //cChannel *chan  = g->getTransmissionChannel();
        
        //cIdealChannel *chan = check_and_cast<cIdealChannel *>(chan1);
        //Channel *chan = check_and_cast<Channel *>(chan1);
        //cDelayChannel *chan = check_and_cast<cDelayChannel *>(chan1);
        
        
        //cIdealChannel
        //Channel
        //ned.DelayChannel
        
        
    //chan->getDisplayString().setTagArg("ls",0,buf);
    //if (chan != NULL)
    //{
    	//chan->setDisplayString("ls=red,3");
    //}
    //chan->getDisplayString().setTagArg("ls",1,buf2);
    	
    	
    //cGate*  ng = ig->getPreviousGate();
    
    //cChannel *chan2  = ng->getChannel();
    //cDelayChannel *chan3 = check_and_cast<cDelayChannel *>(chan2);
	//chan3->setDisplayString("ls=red,3");
    
    
    	
    	
    	
    	
    //}
    
    
    //n=0;
    //for ( int i = 0; i < n; i++ )
    //{
      //  cGate* g = m->gate("gate$o",i);
        //cChannel *chan  = g->getChannel();
        //chan->setDisplayString("ls=red,3");
    //}
	
	
	
	
    EV << "Message kind " << gmsg->getKind() << " PROCESSING COMPLETE\n";
	}
	
	
	
	
	
	
	


