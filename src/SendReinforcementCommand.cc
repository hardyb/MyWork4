

#include "SendReinforcementCommand.h"
#include "MessageHelper.h"
#include "txc20.h"


SendReinforcementCommand::SendReinforcementCommand(Txc20* _m)
: Command(_m)
{
	
}



void SendReinforcementCommand::execute(cMessage *msg)
{
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);
    EV << "SendReinforcementCommand::execute\n";
	if ( !gmsg->isSelfMessage() )
	{
	    EV << "Message kind " << gmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	    //exit(-1);
	}
	
	rd = &(m->moduleRD);

	std::string  s = gmsg->getData();
	std::stringstream ss(s);
	int data;
	ss >> data;
	
	//cModuleType *moduleType = cModuleType::get("tictoc20.txc20");
	//cModuleType *moduleType = cModuleType::get("Txc20");
	//cModule *parentMod = cSimulation::getActiveSimulation()->getModuleByPath("Tictoc20");
	//cModule *mod1 = moduleType->createScheduleInit("node", parentMod);
	//cModule *mod2 = moduleType->createScheduleInit("node", parentMod);
	
	//return;
	
	//cSimulation* sim = cSimulation::getActiveSimulation();
	//fromModule = check_and_cast<Txc20 *>(sim->getModuleByPath("Tictoc20"));
	
    m->getDisplayString().setTagArg("i",0,"block/sink");
    
	// NEW EMULATION CODE
	//StateNode* sn = FindStateNode(rd->stateTree, data);
	//StateNode* sn = FindStateNode(m->moduleRD.stateTree, data);
	//if ( sn && sn->s->bestGradientToObtain )
	//{
		// prepare and forward the reinforcement on this next entry interface
	//	int interface = sn->s->bestGradientToObtain->key2->iName;
    //    int instance = 0;
	//	TicTocMsg20* newmsg = MessageHelper::newMessage(REINFORCE, data, instance, 0);
    //	SendCopyTo(newmsg, interface);
    //	delete msg;
        //reinforceDeliverGradient(data, SELF_INTERFACE);
	//}

	return;


    
	std::set<DataCache>::iterator bestEntry;
    if ( m->dcs.BestPathEntry(0, data, data, bestEntry) )
    {
        int interface = bestEntry->outgoingInterface;
        int instance = bestEntry->instance;
        EV << "got best interface\n";
    	TicTocMsg20* newmsg = MessageHelper::newMessage(REINFORCE, data, instance, 0);
        EV << "Sending copy\n";
    	SendCopyTo(newmsg, interface);
        EV << "SENT copy\n";
    	delete msg;
    	
    	if ( m->fib.InSet(data).empty() )
    	{
        	// add an interest FIB entry pointing to interface self
        	ForwardingEntry fe(0, data, data, -1, 0, 0, -1, 0);
        	m->fib.erase(fe);
        	m->fib.insert(fe);
    	}

    }
	
}


