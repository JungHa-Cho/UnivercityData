#ifndef PACKET_H
#define PACKET_H
#include <iostream>
#include <fstream>
typedef unsigned int UINT_32;
typedef unsigned short UINT_16;
typedef unsigned char UINT_8;
using namespace std;
class Packet
{
public:
	Packet(UINT_32 sA, UINT_32 sN); // default constructor
	Packet(UINT_32 sA, UINT_32 dA, UINT_16 proto, UINT_32 sN, UINT_8 *pPDU, UINT_32 length); // constructor
	UINT_32 getSrcAddr() { return srcAddr;}
	UINT_32 getDstAddr() { return dstAddr;}
	UINT_16 getProtocol() { return protocol;}
	UINT_8 *getPtrPayload() { return pPayload;}
	UINT_32 getSeqNo() { return seqNo; }
	void setSrcAddr(UINT_32 sA) {srcAddr = sA;}
	void setDstAddr(UINT_32 dA) {dstAddr = dA;}
	void setProtocol(UINT_16 proto) { protocol = proto;}
	void setPtrPayload(UINT_8 *pPDU) { pPayload = pPDU;}
	void setSeqNo(UINT_32 sN) { seqNo = sN; }
	ostream& printSaddrSeqNo(ostream *pFout);
	ostream& printPacket(ostream *pFout);
private:
	UINT_32 srcAddr; // source address
	UINT_32 dstAddr; // destination address
	UINT_16 protocol;
	UINT_32 seqNo; // sequence number
	UINT_32 payloadLength;
	UINT_8 *pPayload; // payload
};
#endif