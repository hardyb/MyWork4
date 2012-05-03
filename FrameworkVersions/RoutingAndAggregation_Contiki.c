SearchForKDGradientNodereinforceObtainGradientbestGradientToObtainUpdated

//#include "contiki.h"
#define NULL 0

#include "RoutingAndAggregation.h"
#include <stdlib.h>


/*
TODO

Need to consider the stack in this code.
Since the framework is for multi-platform
i.e. 
how big it is 
whether it is maintained across certain calls
etc

*/


void (*sendAMessage) (unsigned short _interface, char* _msg);
void (*handleApplicationData) (char* _msg);
void (*bcastAMessage) (char* _msg);


static int currentState = 1;
static int K = 2;


struct RoutingData* rd;

union packet incoming_packet;
union packet outgoing_packet;



struct StateNode* newStateNode(int stateDataname)
{
	struct StateNode* n = (struct StateNode *)malloc(sizeof(struct StateNode));
	n->s = (struct State *)malloc(sizeof(struct State));
	n->s->dataName = stateDataname;
	n->s->bestGradientToObtain = NULL;
	n->s->bestGradientToDeliver = NULL;
	n->s->deliveryInterfaces = NULL;
	n->s->obtainInterfaces = NULL;
	n->s->bestGradientToObtainUpdated = FALSE;
	n->s->bestGradientToDeliverUpdated = FALSE;
	n->s->action = FORWARD_ACTION;
	n->left = NULL;
	n->right = NULL;
	return n;
}


struct InterfaceNode* newInterfaceNode(int interfaceName)
{
	struct InterfaceNode* n = (struct InterfaceNode *)malloc(sizeof(struct InterfaceNode));
	n->i = (struct Interface *)malloc(sizeof(struct Interface));
	n->i->iName = interfaceName;
	n->i->up = TRUE;
	n->i->type = 0;
	n->left = NULL;
	n->right = NULL;
	return n;
}




 struct StateNode* InsertStateNode(struct StateNode** treeNode, int stateDataname)
 {
     if (*treeNode == NULL)
	 {
		*treeNode = newStateNode(stateDataname);
#ifdef DEBUG
		std::cout << "Inserted state: " << stateDataname << " = true" << std::endl;
#endif
		return *treeNode;
	 }

	 if (stateDataname == (*treeNode)->s->dataName )
	 {
#ifdef DEBUG
		 std::cout << "Inserted state: " << stateDataname << " = FALSE" << std::endl;
#endif
		 return *treeNode;
	 }

	 if (stateDataname < (*treeNode)->s->dataName)
	 {
	     // I think possibly returns need to occurr here also
		 InsertStateNode(&((*treeNode)->left), stateDataname);
	 }
	 else
	 {
	     // I think possibly returns need to occurr here also
		InsertStateNode(&((*treeNode)->right), stateDataname);
	 }
 }



 struct InterfaceNode* InsertInterfaceNode(struct InterfaceNode** treeNode, unsigned short interfaceName)
 {
     if (*treeNode == NULL)
	 {
		*treeNode = newInterfaceNode(interfaceName);
#ifdef DEBUG
		std::cout << "Inserted interface: " << interfaceName << " = true" << std::endl;
#endif
		return *treeNode;
	 }

	 if (interfaceName == (*treeNode)->i->iName )
	 {
#ifdef DEBUG
		 std::cout << "Inserted interface: " << interfaceName << " = FALSE" << std::endl;
#endif
		 return *treeNode;
	 }

	 if ( interfaceName < (*treeNode)->i->iName )
	 {
		 return InsertInterfaceNode(&((*treeNode)->left), interfaceName);
	 }
	 else
	 {
		return InsertInterfaceNode(&((*treeNode)->right), interfaceName);
	 }
 }




 int UcastAllAdverts(StateNode* tree, unsigned short inf)
 {
	 if ( tree )
	 {
		outgoing_packet.the_message.message_type = ADVERT;
		outgoing_packet.the_message.data_value = tree->s->dataName;
		outgoing_packet.the_message.path_value = tree->s->bestGradientToObtain->costToObtain + nodeConstraint;
		sendAMessage(inf, outgoing_packet.packet_bytes);
	 }
	 else
	 {
		 return 0;
	 }
	 UcastAllAdverts(tree->left, inf);
	 UcastAllAdverts(tree->right, inf);
	 return 1;
 }



 int SendToAllInterfaces(InterfaceNode* tree, void* caller)
 {
	 if ( tree )
	 {
		 sendAMessage(tree->i->iName, outgoing_packet.packet_bytes);
	 }
	 else
	 {
		 return 0;
	 }
	 SendToAllInterfaces(tree->left, caller);
	 SendToAllInterfaces(tree->right, caller);
	 return 1;
 }



 int SendToAllInterfacesExcept(InterfaceNode* tree, unsigned short _exception)
 {
	 if ( tree )
	 {
		if (tree->i->iName != _exception)
		{
			if ( tree->i->iName == SELF_INTERFACE )
			{
				sendAMessage(tree->i->iName, outgoing_packet.packet_bytes);
			}
			else
			{
				sendAMessage(tree->i->iName, outgoing_packet.packet_bytes);
			}
		}
	 }
	 else
	 {
		 return 0;
	 }
	 SendToAllInterfacesExcept(tree->left, _exception);
	 SendToAllInterfacesExcept(tree->right, _exception);
	 return 1;
 }





struct StateNode* FindStateNode(struct StateNode* tree, int val)
{
    struct StateNode *next = tree;
#ifdef DEBUG
	std::cout << "Searching for: " << val << std::endl;
#endif

    int i = 0;
	while (next != NULL) {
#ifdef DEBUG
		std::cout << "Reached node: " << next->s->dataName << std::endl;
#endif
		if (val == next->s->dataName) {
#ifdef DEBUG
			std::cout << "Found = true" << std::endl << std::endl;
#endif
            return next;
		} else if (val < next->s->dataName) {
            next = next->left;
        } else {
            next = next->right;
        }
		i++;
    }

    //not found
#ifdef DEBUG
	std::cout << "Found = false" << std::endl << std::endl;
#endif
    return NULL;
}



struct InterfaceNode* FindInterfaceNode(struct InterfaceNode* tree, unsigned short val)
{
    struct InterfaceNode *next = tree;
#ifdef DEBUG
	std::cout << "Searching for: " << val << std::endl;
#endif

    int i = 0;
	while (next != NULL) {
#ifdef DEBUG
		std::cout << "Reached node: " << next->i->iName << std::endl;
#endif
		if (val == next->i->iName) {
#ifdef DEBUG
			std::cout << "Found = true" << std::endl << std::endl;
#endif
            return next;
		} else if (val < next->i->iName) {
            next = next->left;
        } else {
            next = next->right;
        }
		i++;
    }

    //not found
#ifdef DEBUG
	std::cout << "Found = false" << std::endl << std::endl;
#endif
    return NULL;
}






struct KDGradientNode* newKDGradientNode(int sName, int iName, int obtain, int deliver)
{
	struct KDGradientNode* n = (struct KDGradientNode *)malloc(sizeof(struct KDGradientNode));
	// we need to make it so that the same st cannot get created twice
	// this is enforced in the same tree but not in different trees

	n->key1 = InsertStateNode(&(rd->stateTree), sName)->s;
	n->key2 = InsertInterfaceNode(&(rd->interfaceTree), iName)->i;
	n->costToObtain = obtain;
	n->costToDeliver = deliver;
	n->deliveryReinforcement = FALSE;
	n->obtainReinforcement = FALSE;
	n->left = NULL;
	n->right =NULL;
	return n;
}









struct KDGradientNode* insertKDGradientNode( int sName, int iName, int costType, int pCost, struct KDGradientNode* treeNode, int lev )
{
	if ( treeNode == NULL )
	{
		switch ( costType )
		{
			case OBTAIN:
				treeNode = newKDGradientNode(sName, iName, pCost, 9999);
				break;
			case DELIVER:
				treeNode = newKDGradientNode(sName, iName, 9999, pCost);
				break;
			case REINFORCE_DELIVER:
				treeNode = newKDGradientNode(sName, iName, 9999, 9999);
				//treeNode->deliveryReinforcement = true;
				//treeNode->key1->deliveryInterface = treeNode->key2;
				add(&(treeNode->key1->deliveryInterfaces), treeNode->key2);
				break;
			case REINFORCE_OBTAIN:
				treeNode = newKDGradientNode(sName, iName, 9999, 9999);
				//treeNode->obtainReinforcement = true;
				//treeNode->key1->obtainInterface = treeNode->key2;
				add(&(treeNode->key1->obtainInterfaces), treeNode->key2);
				break;
		}

	}
	else
	{
		// all identical keys to the incoming keys
		if ( sName == treeNode->key1->dataName
			&& iName == treeNode->key2->iName )
		{
			// the node for these keys already exists
			// overwrite of the data if better
			switch ( costType )
			{
				case OBTAIN:
					if ( pCost < treeNode->costToObtain )
					{
						treeNode->costToObtain = pCost;
					}
					break;
				case DELIVER:
					if ( pCost < treeNode->costToDeliver )
					{
						treeNode->costToDeliver = pCost;
					}
					break;
				case REINFORCE_DELIVER:
					//treeNode->deliveryReinforcement = true;
					//treeNode->key1->deliveryInterface = treeNode->key2;
					add(&(treeNode->key1->deliveryInterfaces), treeNode->key2);
					break;
				case REINFORCE_OBTAIN:
					//treeNode->obtainReinforcement = true;
					//treeNode->key1->obtainInterface = treeNode->key2;
					add(&(treeNode->key1->obtainInterfaces), treeNode->key2);
					break;
			}
		}
		else
		{
			if ( lev == 0 )
			{
				if ( sName > treeNode->key1->dataName )
				{
					treeNode->right = insertKDGradientNode( sName, iName, costType, pCost, treeNode->right, (lev+1)%K );
				}
				else
				{
					treeNode->left  = insertKDGradientNode( sName, iName, costType, pCost, treeNode->left, (lev+1)%K );
				}
			}

			if ( lev == 1 )
			{
				if ( iName > treeNode->key2->iName )
				{
					treeNode->right = insertKDGradientNode( sName, iName, costType, pCost, treeNode->right, (lev+1)%K );
				}
				else
				{
					treeNode->left  = insertKDGradientNode( sName, iName, costType, pCost, treeNode->left, (lev+1)%K );
				}
			}

		}
	}

	switch ( costType )
	{
		case OBTAIN:
		case REINFORCE_OBTAIN:
			if ( !treeNode->key1->bestGradientToObtain
				|| treeNode->costToObtain < treeNode->key1->bestGradientToObtain->costToObtain )
			{
				treeNode->key1->bestGradientToObtain = treeNode;
				treeNode->key1->bestGradientToObtainUpdated = TRUE;
			}
			break;
		case DELIVER:
		case REINFORCE_DELIVER:
			if ( !treeNode->key1->bestGradientToDeliver
				|| treeNode->costToDeliver < treeNode->key1->bestGradientToDeliver->costToDeliver )
			{
				treeNode->key1->bestGradientToDeliver = treeNode;
				treeNode->key1->bestGradientToDeliverUpdated = TRUE;
			}
			break;
	}

	return treeNode;
}



struct KDGradientNode* reinforceDeliverGradient(int sName, unsigned short iName)
{
	rd->grTree = insertKDGradientNode(sName, iName, REINFORCE_DELIVER, 0, rd->grTree, 0);
	return rd->grTree;
}


struct KDGradientNode* reinforceObtainGradient(int sName, unsigned short iName)
{
	rd->grTree = insertKDGradientNode(sName, iName, REINFORCE_OBTAIN, 0, rd->grTree, 0);
	return rd->grTree;
}



struct KDGradientNode* setObtainGradient(int sName, int iName, int pCost)
{
	rd->grTree = insertKDGradientNode(sName, iName, OBTAIN, pCost, rd->grTree, 0);
	return rd->grTree;
}


struct KDGradientNode* setDeliverGradient(int sName, int iName, int pCost)
{
	rd->grTree = insertKDGradientNode(sName, iName, DELIVER, pCost, rd->grTree, 0);
	return rd->grTree;
}



















struct KDNode* newKDNode(int keys[], int newStateName)
{
	struct KDNode* n = (KDNode *)malloc(sizeof(KDNode));
	n->keys[0] = InsertStateNode(&(rd->stateTree), keys[0])->s;
	n->keys[1] = InsertStateNode(&(rd->stateTree), keys[1])->s;
	n->newState = InsertStateNode(&(rd->stateTree), newStateName)->s;
	n->left = NULL;
	n->right =NULL;
	return n;
}





















struct KDNode* insertKDNode( int stateDataname[], int newStateName, struct KDNode* treeNode, int lev )
{
	int i;
	if ( treeNode==NULL )
	{
		treeNode = newKDNode(stateDataname, newStateName);
	}
	else
	{
		// this line sets i == K if we have reached a node with
		// all identical keys to the incoming keys
		for ( i=0; i<K && stateDataname[i] == treeNode->keys[i]->dataName; i++ );
		if ( i==K )
		{
			// we have found a duplicate node
		}
		else
		{
			if ( stateDataname[lev] > treeNode->keys[lev]->dataName )
			{
				treeNode->right = insertKDNode( stateDataname, newStateName, treeNode->right, (lev+1)%K );
			}
			else
			{
				treeNode->left  = insertKDNode( stateDataname, newStateName, treeNode->left, (lev+1)%K );
			}
		}
	}
	return treeNode;
}



struct KDGradientNode* SearchForKDGradientNode( int sName, int iName, struct KDGradientNode* treeNode)
{
	int lev, i;
	for ( lev=0; treeNode != NULL; lev=(lev+1)%K )
	{
		// all identical keys to the incoming keys
		if ( sName == treeNode->key1->dataName
			&& iName == treeNode->key2->iName )
		{
#ifdef DEBUG
			std::cout << "Found:     " << "(" << treeNode->keys[0]->dataName << ","
				<< treeNode->keys[1]->dataName << "," << treeNode->newState->dataName << ")" << std::endl;
#endif
			return treeNode;
		}

		if ( lev == 0 )
		{
			if ( sName > treeNode->key1->dataName )
			{
				treeNode = treeNode->right;
			}
			else
			{
				treeNode = treeNode->left;
			}
		}

		if ( lev == 1 )
		{
			if ( iName > treeNode->key2->iName )
			{
				treeNode = treeNode->right;
			}
			else
			{
				treeNode = treeNode->left;
			}
		}
	}
#ifdef DEBUG
	std::cout << "NOT Found: " << "(" << stateDataname[0] << ","
		<< stateDataname[1] << ")" << std::endl;
#endif
	return treeNode; // now NULL
}




struct KDNode* SearchForKDNode( int stateDataname[], struct KDNode* treeNode )
{
	int lev, i;
	for ( lev=0; treeNode != NULL; lev=(lev+1)%K )
	{
		// this line sets i == K if we have reached a node with
		// all identical keys to the incoming keys
		for ( i=0; i<K && stateDataname[i] == treeNode->keys[i]->dataName; i++ );
		if ( i==K )
		{
#ifdef DEBUG
			std::cout << "Found:     " << "(" << treeNode->keys[0]->dataName << ","
				<< treeNode->keys[1]->dataName << "," << treeNode->newState->dataName << ")" << std::endl;
#endif
			return treeNode;
		}

		if ( stateDataname[lev] > treeNode->keys[lev]->dataName )
		{
			treeNode = treeNode->right;
		}
		else
		{
			treeNode = treeNode->left;
		}
	}
#ifdef DEBUG
	std::cout << "NOT Found: " << "(" << stateDataname[0] << ","
		<< stateDataname[1] << ")" << std::endl;
#endif
	return treeNode; // now NULL
}


int getNewState(int input)
{
	int keys[2];
	keys[0] = input;
	keys[1] = currentState;
	struct KDNode* kdn = SearchForKDNode(keys, rd->kdRoot);
	if ( kdn )
	{
		return (currentState = kdn->newState->dataName);
	}
	else
	{
		return input;
	}

}



int SearchForKDNodeTransition(int input)
{
	int stateDataname[2];
	stateDataname[0] = input;
	stateDataname[1] = currentState;
	struct KDNode* treeNode = rd->kdRoot;

	int lev, i;
	for ( lev=0; treeNode != NULL; lev=(lev+1)%K )
	{
		// this line sets i == K if we have reached a node with
		// all identical keys to the incoming keys
		for ( i=0; i<K && stateDataname[i] == treeNode->keys[i]->dataName; i++ );
		if ( i==K )
		{
#ifdef DEBUG
			std::cout << "(" << currentState << ")     " << input << "  --->  " << treeNode->newState->dataName << std::endl;
#endif
			return (currentState = treeNode->newState->dataName);
		}

		if ( stateDataname[lev] > treeNode->keys[lev]->dataName )
		{
			treeNode = treeNode->right;
		}
		else
		{
			treeNode = treeNode->left;
		}
	}
#ifdef DEBUG
	std::cout << "(" << currentState << ")     " << input << "  --->  " << input << std::endl;
#endif
	return input; // now NULL
}



/*
 void PrepareKDNodeDisplayStream(KDNode** treeNode, int level, std::ostringstream* os)
 {

	 if (*treeNode == NULL)
	 {
		os[level] << "(-,-) ";
		return;
	 }
	 else
	 {
		 os[level] << "(" << (*treeNode)->keys[0]->dataName << "," <<
			 (*treeNode)->keys[1]->dataName << "," << (*treeNode)->newState->dataName << ") ";
	 }

	 PrepareKDNodeDisplayStream(&((*treeNode)->left), level+1, os);
	 PrepareKDNodeDisplayStream(&((*treeNode)->right), level+1, os);
 }



 void PrepareKDGradientNodeDisplayStream(KDGradientNode** treeNode, int level, std::ostringstream* os)
 {

	 if (*treeNode == NULL)
	 {
		os[level] << "(-,-) ";
		return;
	 }
	 else
	 {
		 os[level] << "(" << (*treeNode)->key1->dataName << "," <<
			 (*treeNode)->key2->iName << "," << (*treeNode)->costToDeliver << ", " << (*treeNode)->costToObtain << ") ";
	 }

	 PrepareKDGradientNodeDisplayStream(&((*treeNode)->left), level+1, os);
	 PrepareKDGradientNodeDisplayStream(&((*treeNode)->right), level+1, os);
 }


 void DisplayKDTree(KDNode** treeNode, std::ofstream& infile)
 {
	std::ostringstream os[MAXLEVELS];
	PrepareKDNodeDisplayStream(treeNode, 0, os);
	for ( int i = 0; i < MAXLEVELS; i++ )
	{
		infile << os[i].str() << std::endl;
	}
 }


 void DisplayKDGradientTree(KDGradientNode** treeNode, std::ofstream& infile)
 {
	std::ostringstream os[MAXLEVELS];
	PrepareKDGradientNodeDisplayStream(treeNode, 0, os);
	for ( int i = 0; i < MAXLEVELS; i++ )
	{
		infile << os[i].str() << std::endl;
	}
 }
*/


void add(struct InterfaceList** l, struct Interface* _i)
{
	struct InterfaceList *temp,*r;
	temp = *l;
	if( *l == NULL )
	{
		temp = (struct InterfaceList *)malloc(sizeof(struct InterfaceList));
		temp->i = _i;
		temp->link = NULL;
		*l = temp;
	}
	else
	{
		temp = *l;
		while( temp->link !=NULL )
		{
			temp = temp->link;
		}
		r = (struct InterfaceList *)malloc(sizeof(struct InterfaceList));
		r->i = _i;
		r->link = NULL;
		temp->link = r;
	}
}





/*================================ MESSAGE HANDLERS ==============================*/



void (*h[4]) (unsigned short _interface) = 
{
handle_advert, 
handle_interest, 
handle_reinforce, 
handle_data,
handle_neighbor_bcast,
handle_neighbor_ucast
};


void setMessageCallBack(void (*_sendAMessage) (unsigned short _interface, char* _msg))
{
	sendAMessage = _sendAMessage;
}
 
void setBroadcastCallBack(void (*_bcastAMessage) (char* _msg))
{
	bcastAMessage = _bcastAMessage;
}
 

void setApplicationCallBack(void (*_handleApplicationData) (char* _msg))
{
	handleApplicationData = _handleApplicationData;
}


void weAreSourceFor(char _data)
{
	//reinforceObtainGradient(_data, SELF_INTERFACE);

	InsertInterfaceNode(&(rd->interfaceTree), SELF_INTERFACE);
	StateNode* n = InsertStateNode(&(rd->stateTree), _data);
	n->s->action = SOURCE_ACTION;

}


void weAreSinkFor(char _data)
{
	//reinforceDeliverGradient(_data, SELF_INTERFACE);

	InsertInterfaceNode(&(rd->interfaceTree), SELF_INTERFACE);
	StateNode* n = InsertStateNode(&(rd->stateTree), _data);
	n->s->action = SOURCE_ACTION;

}


static void handle_message(char* _msg)
{
	memcpy(incoming_packet.packet_bytes, _msg, 4);
	(*h[incoming_packet.the_message.message_type]) (mm);

}



void handle_advert(unsigned short _interface)
{
	static packet p;
	static struct StateNode* n;
	static struct KDGradientNode* k;

	//memcpy(incoming_packet.packet_bytes, msg, 4);

	// a gradient to self indicates this is the source (or sink?)
	
	//if ( (k = SearchForKDGradientNode(incoming_packet.the_message.data_value, SELF_INTERFACE, rd.grTree)) )
	//{
	//	if (  k->costToDeliver == 0 )
	//	{
	//	}
	//}

    // possibly removing this
	if ( SearchForKDGradientNode(incoming_packet.the_message.data_value, SELF_INTERFACE, rd.grTree) )
	{
		return;
	}

	setObtainGradient(incoming_packet.the_message.data_value, _interface, incoming_packet.the_message.path_value);
	if ( (n = FindStateNode(rd->stateTree, incoming_packet.the_message.data_value)) )
	{
		if ( n->s->bestGradientToObtainUpdated )
		{
			n->s->bestGradientToObtainUpdated = false;
			outgoing_packet.the_message.message_type = ADVERT;
			outgoing_packet.the_message.data_value = incoming_packet.the_message.data_value;
			outgoing_packet.the_message.path_value = incoming_packet.the_message.path_value+nodeConstraint;
			SendToAllInterfacesExcept(rd->InterfaceTree, nm->interface);

// here send to self if the state is marked for action as source
// self would then create a gradient to self, deliver cost zero and reinforce it, then send 
// a reinforcement message to the best obtain gradient

// HOWEVER
// we need to wait a moment in case we dont have the best obtain gradient

// may be we need a different tacl
// may be we should not respond to the advert, but perhaps the application should
// occasionally reinforce for the interested items







		}




	}


}


void handle_interest(unsigned short _interface)
{
// TODO
// Do this later




}


void handle_reinforce(unsigned short _interface)
{

	// NEW EMULATION CODE
    KDGradientNode* g = reinforceDeliverGradient(incoming_packet.the_message.data_value, _interface);

    // a reinforced obtain gradient to self indicates this is the source, so stop
    // and ultimately allow this source to send data
    //KDGradientNode* gn;
	//if ( (gn = SearchForKDGradientNode(incoming_packet.the_message.data_value, SELF_INTERFACE, rd->grTree)) )
			//&& gn->key1->obtainInterface == gn->key2 )
	//{
	//	return;
	//}

	if ( g->key1->bestGradientToObtain )
	{
		// already reinforced so stop here
		if ( g->key1->bestGradientToObtain->obtainReinforcement )
			return;

		// otherwise prepare and forward the reinforcement on this next entry interface
		unsigned short interface = g->key1->bestGradientToObtain->key2->iName;
        //int instance = 0;
        reinforceObtainGradient(incoming_packet.the_message.data_value, interface);
		//TicTocMsg20* newmsg = MessageHelper::newMessage(REINFORCE, sm.data, instance, 0);

		outgoing_packet.the_message.message_type = REINFORCE;
		outgoing_packet.the_message.data_value = incoming_packet.the_message.data_value;
		outgoing_packet.the_message.path_value = 0;
		sendAMessage(interface, outgoing_packet.packet_bytes);

	}

}


void handle_data(unsigned short _interface)
{

	StateNode* sn = FindStateNode(rd->stateTree, incoming_packet.the_message.data_value);
	// not quite right 'cos we just using the best interest gradient
	// rather than the reinforced one

	outgoing_packet.the_message.message_type = DATA;
	outgoing_packet.the_message.data_value = incoming_packet.the_message.data_value;
	outgoing_packet.the_message.path_value = 0;

	InterfaceList* temp = sn->s->deliveryInterfaces;
	while( temp !=NULL )
	{
		// we have temporarily made some assumptions in the above and below code
		if ( temp->i->iName == SELF_INTERFACE )
		{
			handleApplicationData(outgoing_packet.packet_bytes);
		}
		else
		{
			sendAMessage(temp->i->iName, outgoing_packet.packet_bytes);
		}
		temp = temp->link;
	}

}


void handle_neighbor_bcast(unsigned short _interface)
{
	InsertInterfaceNode(&(rd->interfaceTree), _interface);
	printf("Inserted interface\n");

	outgoing_packet.the_message.message_type = NEIGHBOR_UCAST;
	outgoing_packet.the_message.data_value = 0;
	outgoing_packet.the_message.path_value = 0;
	sendAMessage(_interface, outgoing_packet.packet_bytes);
	printf("NEIGHBOR_UCAST\n");

	int advertsFound = UcastAllAdverts(rd->stateTree, _interface);
	printf("Forwarded our adverts\n");

}


void handle_neighbor_ucast(unsigned short _interface)
{
	InsertInterfaceNode(&(rd->interfaceTree), _interface);
	printf("Inserted interface\n");

	int advertsFound = UcastAllAdverts(rd->stateTree, _interface);
	printf("Forwarded our adverts\n");
}




void StartUp()
{

	outgoing_packet.the_message.message_type = NEIGHBOR_BCAST;
	outgoing_packet.the_message.data_value = 0;
	outgoing_packet.the_message.path_value = 0;
	bcastAMessage(outgoing_packet.packet_bytes);

}



void self_handle_advert(struct State* advert)
{
if ( advert->action == ACTION_SINK )
{

// NEED TO BE CAREFUL  -  outgoing_packet already in use?

    KDGradientNode* g = reinforceDeliverGradient(theadvert, SELF_INTERFACE);


	if ( g->key1->bestGradientToObtain )
	{
		// already reinforced so stop here
		if ( g->key1->bestGradientToObtain->obtainReinforcement )
			return;

		// otherwise prepare and forward the reinforcement on this next entry interface
		unsigned short interface = g->key1->bestGradientToObtain->key2->iName;
        //int instance = 0;
        reinforceObtainGradient(incoming_packet.the_message.data_value, interface);
		//TicTocMsg20* newmsg = MessageHelper::newMessage(REINFORCE, sm.data, instance, 0);

		outgoing_packet.the_message.message_type = REINFORCE;
		outgoing_packet.the_message.data_value = incoming_packet.the_message.data_value;
		outgoing_packet.the_message.path_value = 0;
		sendAMessage(interface, outgoing_packet.packet_bytes);

	}















}


//if so:



}


void self_message(void * msg)
{


//are we interested in this advert?

//if so:



}


