

#include "NodeStartupCommand.h"
#include "MessageHelper.h"
#include "txc20.h"
#include "RoutingAndAggregation.h"
#include <stdio.h>
#include <string.h>



NodeStartupCommand::NodeStartupCommand(Txc20* _m)
: Command(_m)
{
	
}



void NodeStartupCommand::execute(cMessage *msg)
{
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
	if ( !gmsg->isSelfMessage() )
	{
	    EV << "Message kind " << gmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	    //exit(-1);
	}
	rd = &(m->moduleRD);



/*
 * we want a single fully qualified data name
 *
 * so...
 *
 * create the right size space
 * copy in the basic data name
 * copy in the dot
 * copy in the full context name
 *
 * how do we get the full context name?
 *
 * is there any where else we do this.  think for a minute
 *
 *
 */
char temp[30];

    if ( Txc20::sink.find(m->getName()) != Txc20::sink.end() )
    {
        Txc20::ret = Txc20::sink.equal_range(m->getName());
        for (Txc20::it=Txc20::ret.first; Txc20::it!=Txc20::ret.second; ++Txc20::it)
        {
            char x[20];
            int datalen = strlen((*Txc20::it).second);
            memcpy(x, (*Txc20::it).second, datalen);
            x[datalen] = DOT;
            getShortestContextTrie(rd->top_context, temp, temp, &(x[datalen+1]));
            weAreSinkFor(x);
        }
    }

    if ( Txc20::source.find(m->getName()) != Txc20::source.end() )
    {
        Txc20::ret = Txc20::source.equal_range(m->getName());
        for (Txc20::it=Txc20::ret.first; Txc20::it!=Txc20::ret.second; ++Txc20::it)
        {
            char x[20];
            int datalen = strlen((*Txc20::it).second);
            memcpy(x, (*Txc20::it).second, datalen);
            x[datalen] = DOT;
            getLongestContextTrie(rd->top_context, temp, temp, &(x[datalen+1]));
            weAreSourceFor(x);
        }
    }


    if ( Txc20::collaborator.find(m->getName()) != Txc20::collaborator.end() )
    {
        Txc20::ret = Txc20::collaborator.equal_range(m->getName());
        for (Txc20::it=Txc20::ret.first; Txc20::it!=Txc20::ret.second; ++Txc20::it)
        {
            char x[20];
            int datalen = strlen((*Txc20::it).second);
            memcpy(x, (*Txc20::it).second, datalen);
            x[datalen] = DOT;
            getLongestContextTrie(rd->top_context, temp, temp, &(x[datalen+1]));
            weAreCollaboratorFor(x);
        }
    }


    if ( Txc20::collaborator_initiator.find(m->getName()) != Txc20::collaborator_initiator.end() )
    {
        Txc20::ret = Txc20::collaborator_initiator.equal_range(m->getName());
        for (Txc20::it=Txc20::ret.first; Txc20::it!=Txc20::ret.second; ++Txc20::it)
        {
            char x[20];
            int datalen = strlen((*Txc20::it).second);
            memcpy(x, (*Txc20::it).second, datalen);
            x[datalen] = DOT;
            getShortestContextTrie(rd->top_context, temp, temp, &(x[datalen+1]));
            weAreCollaboratorInitiatorFor(x);
        }
    }




    //m->getDisplayString().setTagArg("i",0,"block/source");
	m->started = true;
	//m->getDisplayString().setTagArg("b",4,"green");
	//m->getDisplayString().setTagArg("b",5,"10");
	m->getDisplayString().setTagArg("i2",0,"misc/sun_s");

	StartUp();

    
	//int myInterface = m->getId();
	//TicTocMsg20* newmsg = MessageHelper::newMessage(NEIGHBOR_BROADCAST, myInterface, 0, 0);
	//SendCopyToAllInterfaces(newmsg);

    //reinforceObtainGradient(data, SELF_INTERFACE);
	//delete newmsg;
	
}


