#ifndef QUEUE_H
#define QUEUE_H
#include "ListNode.h"
#include "Packet.h"
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_QUEUE_SIZE 10

class Queue{
public:
	Queue();
	int enQueue(ListNode *pLN); 
	ListNode *deQueue();
	void printQueue(ostream *pFout);
private:
	int numPkts;
	ListNode *pFirst;
	ListNode *pLast;
};

#endif