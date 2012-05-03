

#include <omnetpp.h>

#include "SoftMessage.h"

#include "tictoc20_m.h"


SoftMessage::~SoftMessage()
{

}





SoftMessage::SoftMessage(TicTocMsg20 *ttmsg, Txc20* m)
{
	kind = ttmsg->getKind();
	interface = NULL == ttmsg->getArrivalGate() ? -1 : ttmsg->getArrivalGate()->getIndex();
	//TODO
    cGate* cg = m->gate("gate$o", interface); //consider whether this should be in gate or out gate!! 
    cGate*  ng = cg->getNextGate();
    cModule* senderM = ng->getOwnerModule();
    senderModuleIndex = senderM->getIndex();
    data = ttmsg->getData();
    t[0] = ttmsg->getT(0);
    t[1] = ttmsg->getT(1);
    t[2] = ttmsg->getT(2);
    msgMinPathConstraint = ttmsg->getMPathCon();
    hopCount = ttmsg->getHopCount();
	
	
}


