

#include "Command.h"
#include "txc20.h"  // this class was forward decalred in command.h so we now need the formal declaration

#include "MessageHelper.h"



Command::Command(Txc20* _m) : 
m(_m)
{
	
}
Command::~Command()
{
}

void Command::execute(cMessage *msg)
{
    char buf[100];
    char* buf_i = buf;
    sprintf(buf_i, "UNHANDLED MESSAGE\n");
    m->getDisplayString().setTagArg("t",0,buf);

}


bool Command::SendCopyTo(TicTocMsg20 *ttmsg, int _interface)
{
	if ( _interface < 0 )
	{
	    EV << "Gate index: " << _interface << " \n";
	    EV << "Gate index is negative.\n";
	    return false;
	}
	cGate* g = m->gate("gate$o", _interface);
    cDelayChannel *chan  = check_and_cast<cDelayChannel *>(g->getChannel());
	if ( chan->isDisabled() )
	{
        return false;
	}
	
	TicTocMsg20 *msg = MessageHelper::newMessage(ttmsg);    	
	m->send(msg, "gate$o",_interface);
	return true;
    
}




bool Command::SendCopyToModule(TicTocMsg20 *ttmsg, int _moduleID)
{
    int n = m->gateSize("gate");
    for ( int i = 0; i < n; i++ )
    {
    	cGate* g = m->gate("gate$o", i);
    	cModule* endModule = cSimulation::getActiveSimulation()->getModule(_moduleID);
    	if ( g->pathContains(endModule) )
    	{
        	cMessage *msg = MessageHelper::newMessage(ttmsg);
    	    EV << "Send to gate " << i << " \n";
            m->send(msg, "gate$o",i);
            return true;
    	}
    }
    return false;
}


void Command::SendCopyToAllInterfaces(TicTocMsg20 *ttmsg, int exceptInterface)
{
    int n = m->gateSize("gate");
    
    for ( int i = 0; i < n; i++ )
    {
    	if ( i == exceptInterface )
    	{
    		continue;
    	}
    	cMessage *msg = MessageHelper::newMessage(ttmsg);
	    EV << "Send to gate " << i << " \n";
        m->send(msg, "gate$o",i);
    }
    
}


void Command::SendCopyToAllInterfaces(GenericMessage *ttmsg, int exceptInterface)
{
    int n = m->gateSize("gate");

    for ( int i = 0; i < n; i++ )
    {
    	if ( i == exceptInterface )
    	{
    		continue;
    	}
    	cMessage *msg = MessageHelper::newMessage(ttmsg);
	    EV << "Send to gate " << i << " \n";
        m->send(msg, "gate$o",i);
    }

}
