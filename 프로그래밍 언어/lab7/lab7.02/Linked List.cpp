/* 
* File Name: "Linked List.cpp"
* Description:
* - This program is
* Programmed by Jung-Ha Cho,
* Last updated: Version 2.0, Aprill 18, 2012 (by Jung-Ha Cho).
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/04/18) Version Remarks
* J.H Cho 2012/04/15 1.0 Project & Main function is created
* J.H Cho 2012/04/16 1.5 function is Success
* J.H Cho 2012/04/17 2.0 txt out        function is created
* ========================================================
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#define NUM_STARS 10
using namespace std;

typedef struct MyStar{
	char name[16];
	int id;
	double distance;
	double luminosity;
	double mass;
	double radius;
	int age;
} Star;
typedef struct ListNode{
	Star *pS;
	ListNode *pPrev;
	ListNode *pNext;
}ListNode;
typedef struct MyGalaxy{
	ListNode *pFirst;
	ListNode *pLast;
	int num_nodes;
}Galaxy;

void initStarArray(Star aStars[NUM_STARS], int N, int i, int starID);
void BigRand(int mA[], int RANGE);
void insertNodeInOrder(Galaxy *pGlx, ListNode *pLN);
void printLinkedList(Galaxy *pGlx);
ListNode * removeFromHead(Galaxy *pGlx);
ListNode * getFromHead(Galaxy *pGlx);
ofstream outstream("LinkedListForGalaxyOfStars.txt", ios::app);
void main()
{
	Galaxy *pGlx;   //구조체 포인터 변수 선언
	Star  *aStars;  //구조체 포인터 변수 선언
	ListNode *pLN;  //구조체 포인터 변수 선언

	int N = NUM_STARS; //변수 선언
	int *starID, i;  //인트형 포인터 및 변수 선언
	starID = new int[NUM_STARS];  //동적할당배열
	aStars = new Star[NUM_STARS];  //동적할당배열

	pGlx = new Galaxy;  //pGlx구조체 동적 할당
	pGlx->pFirst = NULL; //첫 구조체 
	pGlx->pLast = NULL;  //끝 구조체 널 치환
	pGlx->num_nodes = 0; //노드 넘버 0으로치환

	BigRand(starID, NUM_STARS);  //중복되지않는 수 생성

	for (i=0; i< NUM_STARS; i++) 
	{
		initStarArray(aStars, N, i, *(starID + i) ); //초기화 함수 호출
	}
	for (i=0; i< NUM_STARS; i++) 
	{
		pLN = new ListNode;    //리스트노드형 pLN변수 선언
		pLN->pS = &aStars[i];  //aStars 배열
		insertNodeInOrder(pGlx, pLN);  //인서트노드인오더 함수 호출
		outstream << "Galaxy after insertNodeInOrder(" << pLN->pS->name << "):";
		printLinkedList(pGlx); //프린트 링크드리스트 함수 호출
	}
	for (i=0; i< NUM_STARS; i++) 
	{
		pLN = removeFromHead(pGlx);  //pLN 에 리무브프롬헤드함수 호출한 결과를 치환
		if (pLN != NULL)  //pLN이 널이 아닐때
		{
			outstream << " Galaxy after node (" << pLN->pS->id;  //출력
			outstream << ", " << pLN->pS->name << ") removed from list head: ";
			printLinkedList(pGlx);  //링크드리스트프린트함수 호출
			free(pLN);    //pLN 삭제
		}
		pLN = getFromHead(pGlx);  //헤드 를 선택하는 함수를 호출
		if (pLN != NULL)
		{
			outstream << " New head in list of Galaxy: " << pLN->pS->name <<endl;
		}
	}
	free(pGlx);
	outstream << endl << endl;
	
}
void printLinkedList(Galaxy *pGlx)  //함수 정의
{
	ListNode *pStar;  //리스트노드형 pStar 선언
	int count;  //변수선언 

	outstream<<"Number of stars:"<< pGlx->num_nodes<<endl;

	pStar = pGlx->pFirst;  //pStar에 pGlx의 pFrist를 치환
	count = 0;  //카운트 초기화
	while((pStar != NULL) && (count < NUM_STARS)){  //pStar 널이 아니고 카운트가 넘스타스보다 작을때
		outstream<<" Star_ID ("<<setw(3)<<pStar->pS->id;  //출력
		outstream<<"), Name (" <<pStar->pS->name<<")"<<endl;//출력
		pStar = pStar->pNext; //pStar의 다음 구조체를 치환
		count++;
	}
}
void insertNodeInOrder(Galaxy *pGlx, ListNode *pLN)
{
	if(pGlx->num_nodes == 0)  //인서트 노드 인 오더 넘버 노드스가 0일때
	{
		pGlx->pFirst = pGlx -> pLast = pLN; //pGlx의 pFirst를 pGlx의 pLast를 pLN의 값으로 치환
		pLN->pNext = NULL;  //pLN의 pNext를 NULL로 치환
		pLN->pPrev = NULL;  //pLN의 pPrev를 NULL로 치환
		pGlx->num_nodes++;  //pGlx의 넘버노드수를 카운트
	}else if(pGlx->num_nodes < NUM_STARS){ //pGlx의 numnode가 numstar보다 작을때
		for(ListNode *pS= pGlx->pFirst; pS != NULL;) //리스트노드의 pS가 pGlx의 pFirst이고 pS가 널이 아닐때 까지
		{
			if(pLN->pS->id < pS->pS->id){ //pLN의 pS의 id값이 pS의 pS의 id값과 비교    
				pLN->pNext = pS;  //pLN의 pNext를 pS로 치환
				pLN->pPrev = pS->pPrev; //pLN의 pPrev값을 pS의 pPrev값으로 치환
				if(pS != pGlx->pFirst){ // pS가 pGlx의 pFirst가 아닐때
					if(pS->pPrev != NULL) //pS의 pPrev가 널이 아닐때 
						pS->pPrev->pNext = pLN; //pS의 pPrev와 next를 pLN값으로 치환
					pS->pPrev = pLN;   //pS의 pPrev이전값을 pLN값으로 치환
				} else { //ps == pglx->pfirst
					pGlx->pFirst = pLN;  
					pLN->pPrev = NULL;
					pS->pPrev = pLN;
				}
				pGlx->num_nodes++; // pGlx의 노드수를 카운트
				break;
			}
			else if((pS == pGlx -> pLast) && (pLN->pS->id > pS->pS->id))
			{                     //
				pLN -> pPrev = pS;
				pS->pNext = pLN;
				pGlx->pLast = pLN;
				pLN->pNext = NULL;
				pGlx->num_nodes++;
				break;
			}else{
				if(pS != pGlx -> pLast)
					pS = pS->pNext;
				else
					break;
			}
		}
	}else{//pGlx->num_nodes > num_STARS
		outstream<<"Error in excessive number of stars";
		outstream<<"(NUM_STARS:"<<NUM_STARS<<")";
	}
}
void BigRand(int mA[], int RANGE)
{
	srand(time(0));
	char *flag = new char[RANGE];
	unsigned int uint_32;
	unsigned int bigRand;
	for(int i = 0; i < RANGE; i++ )
	{
		flag[i] = 0;
	}
	int count = 0;
	while (count < RANGE) 
	{
		uint_32 = ( ( long ) rand() << 15) | rand(); 
		bigRand = uint_32 % RANGE;
		if (flag[bigRand] == 1)
		{ 
			continue;
		} else {
			flag[bigRand] = 1;
			mA[count++] = bigRand; // 빅랜드에 +1해주면 1부터100까지 뽑을수있음
		} } }
void initStarArray(Star aStars[NUM_STARS],int N, int i, int starID)
{
	int name_len;
	name_len = rand()%6 + 5;

	( aStars + i )->name[0] = rand()%26 + 'A';

	for (int j=1; j<name_len; j++) 
	{
		( aStars + i )->name[j] = rand()%26 + 'a';
	}
	( aStars + i )->name[name_len] = NULL;
	( aStars + i )->id = starID;
	( aStars + i )->distance = (double)(rand()%10000 + 10.0);
	( aStars + i )->luminosity = (double)(rand()%10000 + 10.0);
	( aStars + i )->mass = (double)(rand()%10000 + 10.0);
	( aStars + i )->radius = (double)(rand()%10000 + 10.0);
	( aStars + i )->age = rand()%10000 + 10;	

}
ListNode *removeFromHead(Galaxy *pGlx)
{
	ListNode *pLN;

	if(pGlx->num_nodes > 0)
	{
		pLN=pGlx->pFirst;
		pGlx->pFirst = pGlx ->pFirst->pNext;
		if(pGlx->pFirst != NULL)
		{
			pGlx->pFirst->pPrev = NULL;
		}
		pGlx->num_nodes--;

		return pLN;
	}else{
		outstream<<"Error in removeFromHead: Linked List is empty";
		return NULL;
	}
}
ListNode *getFromHead(Galaxy *pGlx)
{
	if (pGlx->num_nodes > 0) {
		return pGlx->pFirst;
	} else {
		return NULL;
	}
}