

#include "SendRoleAdvertCommand.h"
#include "SoftMessage.h"
#include "MessageHelper.h"


#define ANY -1


SendRoleAdvertCommand::SendRoleAdvertCommand(Txc20* _m)
: Command(_m)
{
	
}



void SendRoleAdvertCommand::execute(cMessage *msg)
{
	if ( !msg->isSelfMessage() )
	{
	    EV << "Message kind " << msg->getKind() << " is not a self message, but WAS sent to self\n";
		return;
	}
	GenericMessage *gmsg = check_and_cast<GenericMessage *>(msg);



/*
	GenericMessage *newmsg = MessageHelper::newMessage(ROLE_ADVERT, gmsg->getData());
	SendCopyToAllInterfaces(newmsg);
	delete newmsg;




    EV << "Message kind " << gmsg->getKind() << " PROCESSING\n";

	std::string s = gmsg->getData();
	//std::stringstream ss(s);
	int current;
	int in;
	int out;
	int interface = -2; // Means as yet unknown
	int value = 0; // gradient value if used for datacache - what is this?
	int pathvalue = 0;
	int ifModIndex = 0;
	int broken = 0; // is this used?
	int reinforced = 0;
	int instance = 0;
*/

	//need to make a proper function object (but in c)
	//ss.getline()
	//string inputString;
	//int inputArray[20];
	//std::getline(ss, currentString);
	//std::stringstream cs(currentString);
	//for ( int i = 0; !cs.eof(); i++ )
	//{
	//	cs >> inputArray[i];

	//}
	//std::getline
	//int automatonFunction[20][20];
	//while ( !ss.eof() )
	//{
	//	ss >> current >> in >> out;
	//	inputnames.insert(in);
	//	outputnames.insert(out);


	//	automatonFunction[current][in] = out;

		//ForwardingEntry fe(current, in, out, interface, instance, pathvalue, ifModIndex, reinforced);
		//m->fib.insert(fe);
	//}



	//std::string currentString;
	//std::getline(infile, currentString);
	//std::stringstream ss(currentString);
	//int kind;
	//ss >> kind;
	//std::getline(infile, currentString);







/*
int dataname[15];


int hashname(int)
{
	static int names[20];
	static int index;

	for i =
}
*/
















// what to do
/*
	For a given data name a node should pass on an interface the value of current best path
	to source and the summation of its best paths to all sinks.

	The function placement should be evaluated thus:
	The best of
	Summation of all interest paths (including multiple sinks)
	Plus
	Either
	Summation of obtaining child data
	Or
	The obtaining of the data (ie from a best neighbor, if so far available)
	Whichever is the least
*/













	return;


	/*
	TicTocMsg20 *ttmsg = check_and_cast<TicTocMsg20 *>(msg);
	if ( !ttmsg->isSelfMessage() )
	{
	    EV << "Message kind " << ttmsg->getKind() << " IS a self message, but was NOT sent to self\n";
		return;
	    //exit(-1);
	}
	*/
	

	// TODO
	// TEMPORARILY HARDCODED
	//ATransition t[3];
	//t[0].setCurrentState(0);
	//t[0].setInStateTrigger(3);
	//t[0].setOutState(1);
	//t[1].setCurrentState(1);
	//t[1].setInStateTrigger(4);
	//t[1].setOutState(2);
	//t[2].setCurrentState(1);
	//t[2].setInStateTrigger(3);
	//t[2].setOutState(0);

	//setGoodPositionValue(t);
	
	
	
	//TicTocMsg20* newmsg = MessageHelper::newMessage(ROLE_ADVERT, m->bestPositionValue, 0, 0, t);
	//SendCopyToAllInterfaces(newmsg);
	//delete newmsg;
	
	

}



void SendRoleAdvertCommand::setGoodPositionValue(ATransition *t)
{

	// Summation of output data delivery costs
	// Summation of all output data interest path values (including to multiple data sinks)
	int delivery_summation = 0;
	for ( std::set<int>::iterator i = outputnames.begin(); i != outputnames.end(); i++ )
	{
		int cost = 0;
		m->fib.BestPathValue(ANY, *i, *i, cost);
		delivery_summation += cost;
	}

	// Summation of obtaining child data to generate output data
	int obtainchildren_summation = 0;
	for ( std::set<int>::iterator i = inputnames.begin(); i != inputnames.end(); i++ )
	{
		int cost = 0;
		m->dcs.BestPathValue(ANY, *i, *i, cost);
		obtainchildren_summation += cost;
	}

	// Summation of obtaining output data from neighbours for forwarding
	int obtainoutput_summation = 0;
	for ( std::set<int>::iterator i = outputnames.begin(); i != outputnames.end(); i++ )
	{
		int cost = 0;
		m->dcs.BestPathValue(ANY, *i, *i, cost);
		obtainoutput_summation += cost;
	}

	// cost to obtain output data from a neighbour (rather than generating
	// it from children), together with cost of delivering it to interests
	int cost1 = obtainoutput_summation + delivery_summation;

	// cost to generate output data by obtaining children data from neighbours
	// together with cost of delivering it to interests
	int cost2 = obtainchildren_summation + delivery_summation;











/*
 * Issues
 * ========
 *
 * What do we do about multiple instances of same data interests
 * when we are considering best path value above
 *
 */









	// value for transition trigger index 0
	int in0 = t[0].getInStateTrigger();
	int bestIn0 = 0;
	m->dcs.BestPathValue(0, in0, in0, bestIn0);
	
	// value for transition trigger index 1
	int in1 = t[1].getInStateTrigger();
	int bestIn1 = 0;
	m->dcs.BestPathValue(0, in1, in1, bestIn1);
	
	// value for transition trigger index 2
	int in2 = t[2].getInStateTrigger();
	int bestIn2 = 0;
	m->dcs.BestPathValue(0, in2, in2, bestIn2);
	
	//==========================================
	
	// value for transition trigger index 0
	int out0 = t[0].getOutState();
	int bestOut0 = 0;
	m->fib.BestPathValue(0, out0, out0, bestOut0);
	
	// value for transition trigger index 1
	int out1 = t[1].getOutState();
	int bestOut1 = 0;
	m->fib.BestPathValue(0, out1, out1, bestOut1);
	
	// value for transition trigger index 2
	int out2 = t[2].getOutState();
	int bestOut2 = 0;
	m->fib.BestPathValue(0, out2, out2, bestOut2);
	
	//==========================================
	m->goodPositionValue = bestIn0 + bestIn1 + bestIn2 + bestOut0 + bestOut1 + bestOut2 + m->simpleNodeConstraintValue;
	m->bestPositionValue = m->goodPositionValue; 
	m->bestPositionIsMe = true;
	m->goodPositionValueSet = true;
	
	
}

