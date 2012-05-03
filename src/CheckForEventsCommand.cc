
#include<iostream>
#include <fstream>
#include <string>

#include "CheckForEventsCommand.h"
#include "MessageHelper.h"
#include "txc20.h"
#include "RoutingAndAggregation.h"


CheckForEventsCommand::CheckForEventsCommand(Txc20* _m)
: Command(_m)
{
	
}



void CheckForEventsCommand::execute(cMessage *msg)
{
	TicTocMsg20 *ttmsg = check_and_cast<TicTocMsg20 *>(msg);
	if ( !ttmsg->isSelfMessage() )
	{
	    EV << "Message kind " << ttmsg->getKind() << " is a self message, but was not sent to self\n";
		return;
	}
	
	processPresentation();
	processModuleInstrumentation();
	//process

    regular_checks();
	m->scheduleAt(simTime()+2.0, ttmsg);




}



void CheckForEventsCommand::processModuleInstrumentation()
{
	std::string fp = m->getFullPath();
	std::string filename = "./events/"+fp+".txt";
	infile.open (filename.c_str());
	if ( infile.is_open() && !infile.eof() )
	{
	    EV << "Reading instrumentation file: " << filename << "\n";
		GenericMessage* msg = MessageHelper::newMessage(infile);
		m->scheduleAt(simTime()+0.2, msg);
	}
	infile.close();
    remove(filename.c_str());
	
	
}





void CheckForEventsCommand::processPresentation()
{
    std::string filename = "./events/presentation.txt";
	infile.open (filename.c_str());
	//infile.open ("./events/presentation.txt");
	if ( infile.is_open() && !infile.eof() )
	{
		EV << "Reading presentation file.\n";
		std::string currentString;
		std::istringstream currentStream;

		int keyElement;
		unsigned char stateKey[40];
		std::getline(infile, currentString);
		currentStream.clear();
		currentStream.str(currentString);
		for ( int i = 0; stateKey[i] != 0; i++ )
		{
			currentStream >> keyElement;
			stateKey[i] = keyElement;
		}

		int type;
		std::getline(infile, currentString);
		currentStream.clear();
		currentStream.str(currentString);
		currentStream >> type;
		if ( type == 0 )
		{
			//Txc20::state = stateKey;
		}
		else
		{
			//dataname = dataname | type;
			//Txc20::state = dataname | type;
		}

		Txc20::state = stateKey;

		// TODO
		// Very temporary test code
		//dataname_struct dataName;
		//dataName._dataname_struct1.the_dataname = dataname;
		//dataName._dataname_struct2.scope = PROPERTY1 | ROOM1;
		//dataname = dataName._dataname_struct1.the_dataname;
		//Txc20::state = dataname;



		std::getline(infile, currentString);
		Txc20::ObtainGradients = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::obtainCost = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::bestObtainGradient = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::reinforceObtain = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::deliverGradients = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::deliveryCost = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::bestDeliverGradient = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::ReinforceDelivery = currentString == "True" ? true : false;
		std::getline(infile, currentString);
		Txc20::nodeValue = currentString == "True" ? true : false;

		//EV << "PRESENTATION DEBUG" << Txc20::state << Txc20::ObtainGradients << Txc20::obtainCost << Txc20::bestObtainGradient << Txc20::reinforceObtain
		//<< Txc20::deliverGradients << Txc20::deliveryCost << Txc20::bestDeliverGradient << Txc20::ReinforceDelivery << Txc20::nodeValue;

		Txc20::ClearPresentation = true;
		for (cModule::SubmoduleIterator iter(m->getParentModule()); !iter.end(); iter++)
		{
			Txc20 *currentMod = check_and_cast<Txc20 *>(iter());
			currentMod->processPresentationSettings();
		}
		Txc20::ClearPresentation = false;

		for (cModule::SubmoduleIterator iter(m->getParentModule()); !iter.end(); iter++)
		{
			Txc20 *currentMod = check_and_cast<Txc20 *>(iter());
			currentMod->processPresentationSettings();
		}
	}
	infile.close();
    remove(filename.c_str());

}



