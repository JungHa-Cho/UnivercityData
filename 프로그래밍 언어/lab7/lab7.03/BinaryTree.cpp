#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <fstream>
#define NUM_STARS 10

using namespace std;

typedef struct MyStar {
	char name[16];
	int id;
	double distance;
	double luminosity;
	double mass;
	double radius;
	int age;
} Star;
typedef struct MyTreeNode
{
	Star *pStar; // pointer to struct Star
	MyTreeNode *pL;// pointer to left child
	MyTreeNode *pR; // pointer to right child
}TreeNode;

Star * searchTree(TreeNode *pT, int nodeID);
void initStarArray(Star aStar[NUM_STARS], int N, int i, int starID);
void BigRand(int mA[], int RANGE);
void insertTreeNode(TreeNode **ppT, Star *pS);
void printStar(Star *pS);
void printTreeInOrder(TreeNode *pT);
void printTreeReverseOrder(TreeNode *pT);

void insertTreeNode2(TreeNode **ppT, Star *pS);
void printTreeInOrder2(TreeNode *pT);
void printTreeReverseOrder2(TreeNode *pT);

ofstream outstream("sortedSolarStar.dat", ios::app);

void main()
{
	//TreeNode *pGlx = NULL;
	TreeNode *pGlx = NULL; //트리노드형을 가르킬수 있는변수 pGlx를 선언
	
	int *starID, i;  //인테자형 포인터 변수 선언
	int id_to_search;//변수선언
	Star *aStar, *pS;//스타형을 가르킬수 있는aStar변수 선언 pS선언

	aStar = new Star[NUM_STARS];//동적 할당 배열
	starID = new int[NUM_STARS];//동적 할당 배열
	BigRand(starID, NUM_STARS); //동적 할당 배열

	for (i=0; i< NUM_STARS; i++)  //초기화 함수 호출을 NUM_STAR만큼 반복
	{
		initStarArray(aStar, NUM_STARS, i, *(starID + i) );
	}
	for (int i=0; i<NUM_STARS; i++)
	{
		pS = &aStar[i];    //pS에 aStar[i]번째 배열의 주소를 치환
		insertTreeNode(&(pGlx), pS);  //인서트함수 호출 
	}
	outstream <<" Galaxy after Initialization:"<<endl;
	printTreeInOrder(pGlx);   //트리인오더 함수 호출
	outstream <<" Galaxy in reverse order:"<<endl;;
	printTreeReverseOrder(pGlx);//리버스오더 함수 호출
	id_to_search = 5; //서치아이디
	outstream <<" Search Tree with id=" << id_to_search <<endl;
	pS = NULL; //pS초기화
	pS = searchTree(pGlx, id_to_search); //서치트리함수 호출후 치환
	if (pS != NULL) { 
		printStar(pS);  //출력문
	} else {
		outstream <<" Star (id: " << id_to_search << ") was not found."<<endl;
	}
	outstream << endl;
	
	pGlx=NULL;

	for (i=0; i< NUM_STARS; i++)  //초기화 함수 호출을 NUM_STAR만큼 반복
	{
		initStarArray(aStar, NUM_STARS, i, *(starID + i) );
	}


	outstream<<" Name Sort "<<endl;
	for (int i=0; i<NUM_STARS; i++)
	{
		pS = &aStar[i];    //pS에 aStar[i]번째 배열의 주소를 치환
		insertTreeNode2(&(pGlx), pS);  //인서트함수 호출 
	}
	outstream <<" Galaxy after Initialization:"<<endl;
	printTreeInOrder2(pGlx);   //트리인오더 함수 호출
	outstream <<" Galaxy in reverse order:"<<endl;;
	printTreeReverseOrder2(pGlx);//리버스오더 함수 호출
}
void initStarArray(Star aStar[NUM_STARS], int N, int i, int starID)
{
	int name_len;                   //변수정의
	name_len = rand()%6 + 5;        //변수의 랜드함수 범위값 지정
	(aStar+i)->name[0] = rand()%26 + 'A'; //랜드함수 호출 A로 시작
	for (int j=1; j<name_len; j++)   //j가 1부터 네임렝스 만큼
	{
		(aStar+i)->name[j] = rand()%26 + 'a'; //소문자 
	}
	(aStar + i)->name[name_len] = NULL;  //널값으로 치환
	(aStar + i) -> id = starID;          //starID를 iD로 치환
	(aStar + i)->distance = (double)(rand()%10000 + 10.0); //랜덤 생셩
	(aStar + i)->luminosity = (double)(rand()%10000 + 10.0); //랜덤생성
	(aStar + i)->mass = (double)(rand()%10000 + 10.0);  //랜덤생성
	(aStar + i)->radius = (double)(rand()%10000 + 10.0); //랜ㄷ덤생성
	(aStar + i)->age = rand()%10000 + 10; //랜덤생성
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
void insertTreeNode(TreeNode **ppT, Star *pS)
{
	TreeNode *pN;   //트리노드형 포인터변수 pN
	if(*ppT == NULL) //ppT의 값이 
	{
		pN = new TreeNode; //트리노드 형으로 동적할당
		pN->pStar = pS; // pN
		pN->pL = NULL;  //pN의 pL초기화
		pN->pR = NULL;  //pN의 pL초기화
		*ppT = pN;
		outstream <<" InsertTreeNode (Star id:" << pS->id;
		outstream <<", name: " << pS->name << ")"<<endl;
	
	} else if (pS->id < (*ppT)->pStar->id)
	{
		insertTreeNode(&(*ppT)->pL, pS);//작으면 왼쪽
	} else 
	{
		insertTreeNode(&(*ppT)->pR, pS);//크면 오른쪽
	}
}
void printStar(Star *pS)
{
	if (pS != NULL) {
		outstream << " Star (ID: " << setw(3) << pS->id;
		outstream << ", Name :" << pS->name << ")"<<endl;
	}
}
void printTreeInOrder(TreeNode *pT)
{
	if (pT != NULL) {     
		printTreeInOrder(pT->pL); //
		printStar(pT->pStar);
		printTreeInOrder(pT->pR);
	}
}
void printTreeReverseOrder(TreeNode *pT)
{
	if (pT != NULL) {
		printTreeReverseOrder(pT->pR);
		printStar(pT->pStar);
		printTreeReverseOrder(pT->pL);
	}
}
Star *searchTree(TreeNode *pT, int nodeID)
{
	if (pT == NULL)
	{
		return NULL;
	} else if (pT->pStar->id == nodeID)
	{
		return pT->pStar;
	} else if (pT->pStar->id < nodeID)
	{
		searchTree(pT->pR, nodeID);
	} else {
		searchTree(pT->pL, nodeID);
	}
}

void insertTreeNode2(TreeNode **ppT, Star *pS)
{
	TreeNode *pN;
	if(*ppT == NULL)
	{
		pN = new TreeNode;
		pN->pStar = pS;
		pN->pL = NULL;
		pN->pR = NULL;
		*ppT = pN;
		outstream <<" InsertTreeNode (Star id:" << pS->id;
		outstream <<", name: " << pS->name << ")"<<endl;
	} else if (string(pS->name) <string((*ppT)->pStar->name))
	{
		insertTreeNode(&(*ppT)->pL, pS);//작으면 왼쪽
	} else 
	{
		insertTreeNode(&(*ppT)->pR, pS);//크면 오른쪽
	}
}
void printTreeInOrder2(TreeNode *pT)
{
	if (pT != NULL) {     
		printTreeInOrder(pT->pL); //
		printStar(pT->pStar);
		printTreeInOrder(pT->pR);
	}
}
void printTreeReverseOrder2(TreeNode *pT)
{
	if (pT != NULL) {
		printTreeReverseOrder(pT->pR);
		printStar(pT->pStar);
		printTreeReverseOrder(pT->pL);
	}
}
