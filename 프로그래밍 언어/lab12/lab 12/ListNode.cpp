#include "ListNode.h"
#include <iostream>
using namespace std;

ListNode::ListNode(Packet *pPacket)
{pPkt = pPacket;
pNext=pPrev=NULL;}
void ListNode::setNext(ListNode *pNx)
{pNext = pNx;}
void ListNode::setPrev(ListNode *pPrv)
{pPrev = pPrv;}