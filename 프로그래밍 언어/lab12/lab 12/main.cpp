/* File Name: "Queue"
* Description:
* - This program is Queue
* Programmed by Jung-Ha Cho
* Last updated: Version 1.0, JUNE 12, 2012 (by Jung-Ha Cho).
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/06/12) Version Remarks
* J.H Cho 2012/06/12 1.0 완료!
* =========================================================
*/
#include <iostream> // for cin, cout
#include <fstream> // for file I/O
#include "Packet.h"
#include "ListNode.h"
#include "Queue.h"
#include <windows.h>
#include <conio.h> // for getch()
#include <cstdlib> // for exit()
#define MAX_QUEUE_SIZE 10
enum ROLE {PACKET_GEN, PACKET_RECV, LINK_TX, LINK_RX};
#define NUM_PACKET_GENS 5 //thread수
#define NUM_LINK_TX 1
DWORD WINAPI Thread_PacketGenerator(LPVOID pParam);
DWORD WINAPI Thread_LinkTransmitter(LPVOID pParam);

typedef struct ThreadParam
{
	CRITICAL_SECTION *pCS;
	Queue *pQ;
	int role; //
	UINT_32 addr;
	int max_queue;
	int duration;
	ofstream *pOfstr;
}ThreadParam;

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if(fout.fail()) {
		cout << "Fail in opening output.txt file.\n";
		exit (1);
	}
	////////////////////////////////////////////////////////////////////////
	Queue *pQueue;
	ThreadParam *pThrParam;
	CRITICAL_SECTION crit;
	HANDLE hThreadPktGen[NUM_PACKET_GENS], hThreadLinkTx[NUM_LINK_TX];
	pQueue = new Queue();
	//////////////////////////////////////////////////////////////////////// pQueue 동적할당부분
	InitializeCriticalSection(&crit);
	for (int i=0; i<NUM_LINK_TX; i++) {
		pThrParam = new ThreadParam;
		pThrParam->role = LINK_TX;
		pThrParam->addr = (UINT_32) i;
		pThrParam->pCS = &crit;
		pThrParam->pQ = pQueue;
		pThrParam->max_queue = MAX_QUEUE_SIZE;
		pThrParam->duration = 30; // 30 second
		pThrParam->pOfstr = &fout;
		hThreadLinkTx[i] = CreateThread(NULL, 0, Thread_LinkTransmitter, pThrParam, 0, NULL);
	}
	for (int i=0; i<NUM_PACKET_GENS; i++)
	{
		pThrParam = new ThreadParam;
		pThrParam->role = PACKET_GEN;
		pThrParam->addr = (UINT_32) i;
		pThrParam->pCS = &crit;
		pThrParam->pQ = pQueue;
		pThrParam->max_queue = MAX_QUEUE_SIZE;
		pThrParam->duration = 30; // 30 second
		pThrParam->pOfstr = &fout;
		hThreadPktGen[i] = CreateThread(NULL, 0, Thread_PacketGenerator, pThrParam, 0, NULL);
	}

	cout << "Press any key to terminate..\n";
	getch();
	DeleteCriticalSection (&crit);
	fout.close();
}
DWORD WINAPI Thread_PacketGenerator(LPVOID pParam)
{
	int count=0;
	ThreadParam *pThrParam;
	Packet *pPkt;
	ListNode *pLN;
	UINT_32 srcAddr;
	ofstream *pFout;
	pThrParam = (ThreadParam *)pParam;
	srcAddr = pThrParam->addr;
	pFout = pThrParam->pOfstr;
	*pFout << "Thread_PacketGen(addr:" << srcAddr << ")..." << endl;
	for (int i=0; i<pThrParam->max_queue; i++)
	{
		pPkt = new Packet(srcAddr, i);
		pLN = new ListNode(pPkt);
		/* Entering Critical Section */
		EnterCriticalSection(pThrParam->pCS);
		pThrParam->pQ->enQueue(pLN);
		LeaveCriticalSection(pThrParam->pCS);
		/* Leaving Critical Section */
		//pInputQ->printQueue(cout);
		//cout << endl;
		*pFout << "Thread_PktGen (" << pPkt->getSrcAddr() ;
		*pFout << "): PacketGen(seqNo: " << pPkt->getSeqNo() << ")\n";
		Sleep(rand()%4000+1000);
		count++;
	}
	cout<<"enQueue num : "<<count<<endl;
	*pFout << "Terminating Thread_PktGen(" << srcAddr <<") ...\n";
	return 0;
}
DWORD WINAPI Thread_LinkTransmitter(LPVOID pParam)
{
	ThreadParam *pThrParam;
	Packet *pPkt;
	ListNode *pLN;
	int count = 0;
	UINT_32 srcLinkAddr;
	ofstream *pFout;
	int pktTx_per_src[NUM_PACKET_GENS];
	pThrParam = (ThreadParam *)pParam;
	srcLinkAddr = pThrParam->addr;
	pFout = pThrParam->pOfstr;
	*pFout << "Thread_LinkTx(srcLinkAddr" << srcLinkAddr<<") ..." << endl;
	for (int i=0; i<NUM_PACKET_GENS; i++)
	{
		pktTx_per_src[i] = 0;
	}
	while (count < ((pThrParam->max_queue*NUM_PACKET_GENS)/NUM_LINK_TX))
	{
		EnterCriticalSection(pThrParam->pCS);
		pLN = pThrParam->pQ->deQueue();
		LeaveCriticalSection(pThrParam->pCS);
		if (pLN != NULL)
		{
			pPkt = pLN->getPtrPacket();
			if (pPkt != NULL)
			{
				*pFout << "\nThread_LinkTx->";
				pPkt->printPacket(pFout);
				pktTx_per_src[pPkt->getSrcAddr()]++;
				count++;
			 } else {
				*pFout << "pPkt is NULL !\n";
			}
		}
		*pFout << "\nThread_LinkTx->";
		EnterCriticalSection(pThrParam->pCS);
		pThrParam->pQ->printQueue(pFout);
		LeaveCriticalSection(pThrParam->pCS);
		Sleep(rand()%4000+1000);
	} // end while
	for (int i=0; i<NUM_PACKET_GENS; i++)
	{
		*pFout << "Number of packet transmitted (src: ";
			*pFout << i << ") : " << pktTx_per_src[i] <<endl;
	}
	*pFout << "Terminating Thread_LinkTx ...\n";
	return 0;
}