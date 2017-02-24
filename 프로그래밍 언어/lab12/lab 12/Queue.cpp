#include "Queue.h"
#include <iostream>
#include <fstream>
using namespace std;
Queue::Queue()
{
	numPkts = 0;
	pFirst = NULL;
	pLast = NULL;
}
int Queue::enQueue(ListNode *pLN)
{
	if(numPkts == 0)
	{
		pFirst = pLN;
		pLast = pLN;
		numPkts++;
		return true;
	}
	else if(MAX_QUEUE_SIZE > numPkts)
	{
		pLN->setPrev(pLast);
		pLast->setNext(pLN);
		pLast = pLN;
		pLN->setNext(NULL);
		numPkts++;
		return true;
	}
	return false;
}
ListNode *Queue::deQueue()
{
	ListNode *pLN;
	pLN = NULL;

	if(numPkts > 0)                 //ťť�� ��Ŷ�� 0����Ŭ��
	{
		pLN = pFirst;
		pFirst = pFirst->getNext();
		if(pFirst != NULL)
			pFirst->setPrev(NULL);
		numPkts--;
		return pLN;
	}
	else
	{
		cout<<"Error in removeFromHead: Linked List is empty\n";
		return	NULL;
	}
	//ListNode *pLN;
	//if (numPkts > 0)  //�����ǿ� ���ö�
	//{
	//	pLN = pFirst; 
	//	pFirst=pFirst->getNext();
	//	if (pFirst != NULL) //first�� ����� prev �� NULL�� �����
	//		pFirst->setPrev(NULL)/*pPrev = NULL*/;
	//	numPkts--; 
	//	return pLN;
	//} 
	//else 
	//{
	//	cout <<"Error in removeFromHead: Linked List is empty\n";

	//	return NULL;
	//}
}
void Queue::printQueue(ostream *pFout)
{
	if(pFirst!=NULL)
	{
		if(pFirst->getPtrPacket()!=NULL)
		{
			*pFout<<"Print Queue: ";
			pFirst->getPtrPacket()->printSaddrSeqNo(pFout);
		}
	}
	else
		*pFout<<"Empty queue."<<endl;
}