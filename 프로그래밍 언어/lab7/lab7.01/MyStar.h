/*
* MyStar.H
*/
typedef struct MyStar
{
	char name[16];
	int id;
	double distance;
	double luminosity;
	double mass;
	double radius;
	int age;
	//MyStar *pPrev;
	//MyStar *pNext;
}Star;