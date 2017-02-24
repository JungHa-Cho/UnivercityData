#ifndef LISTNODE_H
#define LISTNODE_H

#include "Packet.h"
//class Packet;

class ListNode{
public:
	ListNode(Packet *pPacket);
	Packet *getPtrPacket(){ return pPkt; }
	ListNode *getNext(){ return pNext; }
	ListNode *getPrev(){ return pPrev; }
	void setNext(ListNode *pNx);
	void setPrev(ListNode *pPrv);
private:
	Packet *pPkt;
	ListNode *pNext;
	ListNode *pPrev;
};

#endif