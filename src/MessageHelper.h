#ifndef MessageHelper_h
#define MessageHelper_h





#include "tictoc20_m.h"
#include "GenericMessage_m.h"


#include<iostream>
#include <fstream>
#include <sstream>
#include <string>


class MessageHelper
{
public:
	MessageHelper();
	~MessageHelper();
	
	static GenericMessage* newMessage(GenericMessage *gmsg);
	static TicTocMsg20* newMessage(TicTocMsg20 *ttmsg);
	static GenericMessage* newMessage(int _kind, const char* _data);
	static GenericMessage* newMessage(std::ifstream &infile);
	static TicTocMsg20* newMessage(int _kind, int _data, int _hopCount, int _mPathCon, ATransition *t =NULL);
	static TicTocMsg20* newMessage2(int _kind, int _data, int _hopCount, int _mPathCon);

};




#endif

