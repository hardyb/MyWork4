





#include "tictoc20_m.h"


#include "MessageHelper.h"


TicTocMsg20* MessageHelper::newMessage(TicTocMsg20 *ttmsg)
{
	char msgname[20];
	sprintf(msgname, "KIND-%d", ttmsg->getKind());
	TicTocMsg20 *msg = new TicTocMsg20(msgname);
	msg->setKind(ttmsg->getKind());
	msg->setData(ttmsg->getData());
	msg->setHopCount(ttmsg->getHopCount());
	msg->setMPathCon(ttmsg->getMPathCon());
	
	msg->setT(0, ttmsg->getT(0));
	msg->setT(1, ttmsg->getT(1));
	msg->setT(2, ttmsg->getT(2));
	
	return msg;
}


GenericMessage* MessageHelper::newMessage(GenericMessage *gmsg)
{
	char msgname[20];
	sprintf(msgname, "KIND-%d", gmsg->getKind());
	GenericMessage *msg = new GenericMessage(msgname);
	msg->setKind(gmsg->getKind());
	msg->setData(gmsg->getData());
	return msg;
}


GenericMessage* MessageHelper::newMessage(int _kind, const char* _data)
{
	char msgname[20];
	sprintf(msgname, "KIND-%d", _kind);
	GenericMessage *msg = new GenericMessage(msgname);
	msg->setKind(_kind);
	msg->setData(_data);
	return msg;
}


GenericMessage* MessageHelper::newMessage(std::ifstream &infile)
{
	std::string currentString;
	std::getline(infile, currentString);
	std::stringstream ss(currentString);
	int kind;
	ss >> kind;
	std::getline(infile, currentString);
	
	char msgname[20];
	sprintf(msgname, "KIND-%d", kind);
	GenericMessage *msg = new GenericMessage(msgname);
	msg->setKind(kind);
	msg->setData(currentString.c_str());
	return msg;
}



TicTocMsg20* MessageHelper::newMessage2(int _kind, int _data, int _hopCount, int _mPathCon)
{
	char msgname[20];
	sprintf(msgname, "KIND-%d", _kind);
	TicTocMsg20 *msg = new TicTocMsg20(msgname);
	msg->setKind(_kind);
	msg->setData(_data);
	msg->setHopCount(_hopCount);
	msg->setMPathCon(_mPathCon);
	return msg;
}



TicTocMsg20* MessageHelper::newMessage(int _kind, int _data, int _hopCount, int _mPathCon, ATransition *t)
{
	char msgname[20];
	sprintf(msgname, "KIND-%d", _kind);
	TicTocMsg20 *msg = new TicTocMsg20(msgname);
	msg->setKind(_kind);
	msg->setData(_data);
	msg->setHopCount(_hopCount);
	msg->setMPathCon(_mPathCon);
	
	ATransition dummyTransaction;
	dummyTransaction.setCurrentState(0);
	dummyTransaction.setInStateTrigger(0);
	dummyTransaction.setOutState(0);
	
	if ( t )
	{
		msg->setT(0, t[0]);
		msg->setT(1, t[1]);
		msg->setT(2, t[2]);
	}
	else
	{
		msg->setT(0, dummyTransaction);
		msg->setT(1, dummyTransaction);
		msg->setT(2, dummyTransaction);
	}
	
	
	return msg;
}




