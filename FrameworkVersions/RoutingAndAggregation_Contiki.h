#ifndef RoutingAndAggregation_h
#define RoutingAndAggregation_h



#define MAXLEVELS 10

#define OBTAIN 1
#define DELIVER 2
#define REINFORCE_DELIVER 3
#define REINFORCE_OBTAIN 4


#define ANY_STATE 0
#define SELF_INTERFACE 65535
#define UNKNOWN_INTERFACE 65534
#define COST_ZERO 0

#define FALSE 0
#define TRUE 1




//#define DEBUG

//#ifndef max
//	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
//#endif

//#ifndef min
//	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
//#endif


#define ADVERT 0
#define INTEREST 1
#define REINFORCE 2
#define DATA 3
#define NEIGHBOR_BCAST 4
#define NEIGHBOR_UCAST 5



#define SINK_ACTION 1
#define SOURCE_ACTION 2
#define FORWARD_ACTION 3
#define TRANSFORM_ACTION 4



extern unsigned char nodeConstraint;

#define MESSAGE_SIZE

struct message
{
	char message_type;			// assume size 1
	char data_value;			// assume size 1
	unsigned short path_value;	// assume size 2
};


union packet
{
	unsigned char packet_bytes[4];
	message the_message;
};



typedef struct Interface
{
	unsigned short iName;
	int up; /* this is used as a bool */
	int type;
};


typedef struct KDGradientNode;

struct InterfaceList
{
	 struct Interface* i;
	 struct InterfaceList *link;
};


typedef struct InterfaceList InterfaceList;


typedef struct State
{
	// Consider having state as just the int
	// and in future maybe a string
	// but possibly never a structure - no additional members needed
	int dataName;
	struct KDGradientNode* bestGradientToObtain;
	int bestGradientToObtainUpdated; /* used as a bool */
	struct InterfaceList* obtainInterfaces;
	struct KDGradientNode* bestGradientToDeliver;
	int bestGradientToDeliverUpdated; /* used as a bool */
	struct InterfaceList* deliveryInterfaces;
	int action;
};



struct StateNode
{
	struct State* s;
	struct StateNode* left;
	struct StateNode* right;
};

typedef struct StateNode StateNode;


struct InterfaceNode
{
	struct Interface* i;
	struct InterfaceNode* left;
	struct InterfaceNode* right;
};

typedef struct InterfaceNode InterfaceNode;





typedef struct KDGradientNode
{
	// just these for now
	// also consider that maybe keys should be an array of State pointers
	// OK NOW WE USING POINTERS AND NEWKDNODE() creates or gets accordingly
	struct State* key1;
	struct Interface* key2;
	int costToObtain;
	int costToDeliver;
	int deliveryReinforcement; /* used as a bool*/
	int obtainReinforcement; /* used as a bool*/
	struct KDGradientNode* left;
	struct KDGradientNode* right;


};


struct KDNode
{
	struct State* keys[2];
	struct State* newState;
	struct KDNode* left;
	struct KDNode* right;
};

typedef struct KDNode KDNode;



typedef struct RoutingData
{
	struct StateNode* stateTree;
	struct InterfaceNode* interfaceTree;
	struct KDGradientNode* grTree;
	struct KDNode* kdRoot;
};



extern struct RoutingData* rd;



void add(struct InterfaceList** q, struct Interface* _i);
StateNode* newStateNode(int stateDataname);
InterfaceNode* newInterfaceNode(int interfaceName);
StateNode* InsertStateNode(StateNode** treeNode, int stateDataname);
InterfaceNode* InsertInterfaceNode(InterfaceNode** treeNode, unsigned short interfaceName);
StateNode* FindStateNode(StateNode* tree, int val);
InterfaceNode* FindInterfaceNode(InterfaceNode* tree, unsigned short val);
struct KDGradientNode* newKDGradientNode(int sName, int iName, int obtain, int deliver);
struct KDGradientNode* insertKDGradientNode( int sName, int iName, int costType, int pCost, struct KDGradientNode* treeNode, int lev );
struct KDGradientNode* reinforceDeliverGradient(int sName, unsigned short iName);
struct KDGradientNode* reinforceObtainGradient(int sName, unsigned short iName);
struct KDGradientNode* setObtainGradient(int sName, int iName, int pCost);
struct KDGradientNode* setDeliverGradient(int sName, int iName, int pCost);
KDNode* newKDNode(int keys[], int newStateName);
KDNode* insertKDNode( int stateDataname[], int newStateName, KDNode* treeNode, int lev );
struct KDGradientNode* SearchForKDGradientNode( int sName, int iName, struct KDGradientNode* treeNode);
KDNode* SearchForKDNode( int stateDataname[], KDNode* treeNode );
int getNewState(int input);
int SearchForKDNodeTransition(int input);
//void PrepareKDNodeDisplayStream(KDNode** treeNode, int level, std::ostringstream* os);
//void PrepareKDGradientNodeDisplayStream(KDGradientNode** treeNode, int level, std::ostringstream* os);
//void DisplayKDTree(KDNode** treeNode, std::ofstream& infile);
//void DisplayKDGradientTree(KDGradientNode** treeNode, std::ofstream& infile);



/*================================ MESSAGE HANDLERS ==============================*/

void handle_advert(unsigned short _interface);
void handle_interest(unsigned short _interface);
void handle_reinforce(unsigned short _interface);
void handle_data(unsigned short _interface);
void handle_neighbor_bcast(unsigned short _interface);
void handle_neighbor_ucast(unsigned short _interface);


#endif



