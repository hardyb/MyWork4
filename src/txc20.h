#ifndef txc20_h
#define txc20_h

#include "tictoc20_m.h"
#include <omnetpp.h>


#include "ForwardingEntry.h"
#include "ForwardingEntrySet.h"
#include "DataCache.h"
#include "DataCacheSet.h"
#include "Command.h"
#include "RoutingAndAggregation.h"


using namespace std;


#define IMAGEPATH "C:/omnetpp-4.1/images/"

/*
class Command
{
public:
	Command(Txc20* _m);
	~Command(void);
	virtual void execute(TicTocMsg20 *ttmsg) = 0;
	void SendCopyToAllInterfaces(TicTocMsg20 *ttmsg);
	Txc20* m;
	int dummy;
};
*/








            //static unsigned char state;
            //static bool ObtainGradients;
            //static bool obtainCost;
            //static bool bestObtainGradient;
            //static bool reinforceObtain;
            //static bool deliverGradients;
            //static bool deliveryCost;
            //static bool bestDeliverGradient;
            //static bool ReinforceDelivery;
            //static bool nodeValue;


















class Txc20 : public cSimpleModule
{
  public:

	static pair<multimap<string,char*>::iterator,multimap<string,char*>::iterator> ret;
	static multimap<string,char*>::iterator it;
	static multimap<std::string,char*> sink;
    static multimap<std::string,char*> source;
    static multimap<std::string,char*> collaborator;
    static multimap<std::string,char*> collaborator_initiator;
	static map<string,string> stateNames;
	static bool sourceAndSinkData_Initialised;

    // variables for presentation features
	static unsigned char* state;
    static bool ObtainGradients;
    static bool obtainCost;
    static bool bestObtainGradient;
    static bool reinforceObtain;
    static bool deliverGradients;
    static bool deliveryCost;
    static bool bestDeliverGradient;
    static bool ReinforceDelivery;
    static bool nodeValue;
    static bool ClearPresentation;



	static bool justStartedInitialising;
	bool started;
    long numSent;
    long numReceived;
    int simpleNodeConstraintValue;
    char simpleNodeScopeValue;
    ForwardingEntrySet fib;
    DataCacheSet dcs;

    // NEW EMULATION CODE
    //KDGradientNode* grTree;
    RoutingData moduleRD;

	static const int constraintValues[9];
	int currentMinPathConstraint;
	int currentMinPathInterface;
	bool firstArrival;
	int theInput;
	Command *cmd[50];
	std::string cmdName[50];
	int  bestPositionValue;
	int  goodPositionValue;
	bool  goodPositionValueSet;
	bool  bestPositionIsMe;
	//int sourceData;
	//int sinkData;
	int currentState;
	
public:
    void Red(int gateIndex);
    void processPresentationSettings();

  protected:
    void populateCommands();
    virtual void forwardInterestMessage(TicTocMsg20 *ttmsg);
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    TicTocMsg20* generateInterestMessage(int interest, int minPathConstraint);
    TicTocMsg20* generateNotificationMessage(int notification);
    void updateDisplay();
    bool AlreadyForwardingThisInterest(int _interest);
    void SetSimpleNodeValues();
    void setDisplayString(int inf);
    void setDisplayStringInChannel(int gateIndex, std::string &ds);
    void setDisplayStringOutChannel(int gateIndex, std::string &ds);
    void setDisplayStringBothChannels(int gateIndex, std::string &ds);
    void Initialise_sourceAndSinkData();


};


#endif
