#include "Packet.h"
#include <iostream>
#include <fstream>
using namespace std;

Packet::Packet(UINT_32 sA, UINT_32 sN)
{
	srcAddr = sA;
	seqNo = sN;

	dstAddr = rand() % 100;
	protocol = rand() % 100;

	payloadLength = rand() % 100;
	pPayload = new UINT_8;
}
Packet::Packet(UINT_32 sA, UINT_32 dA, UINT_16 proto, UINT_32 sN, UINT_8 *pPDU, UINT_32 length)
{
	srcAddr = sA;
	dstAddr = dA;
	protocol = proto;
	seqNo = sN;
	pPayload = pPDU;
	payloadLength = length;
}
ostream& Packet::printSaddrSeqNo(ostream *pFout)
{
	*pFout<<"srcAddr : "<<srcAddr<<" Sequence NO : "<<seqNo<<endl;
	return *pFout;
}
ostream& Packet::printPacket(ostream *pFout)
{
	*pFout<<"srcAddr : "<<srcAddr<<" dstAddr : "<< dstAddr<<" protocol : "<<protocol<<" seqNo : "<< seqNo<<" payloadLength : "<<payloadLength<<endl;
	return *pFout;
}