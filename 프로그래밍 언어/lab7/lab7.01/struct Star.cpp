#include <iostream>
#include <time.h>
#include <iomanip>
#include "MyStar.h"
#define NUM_STARS 10
using namespace std;

void initArrayStars(Star aStars[NUM_STARS], int size, int aID[]);
void BigRand(int mA[], int RANGE);
void printStar(Star *pS);

void main()
{
	Star *aStars;
	aStars = new Star[NUM_STARS];
	int *aID;
	aID = new int[NUM_STARS];
	BigRand(aID, NUM_STARS);

	initArrayStars(aStars, NUM_STARS, aID);
	for( int i = 0 ; i < NUM_STARS ; i++ )
	{
		printStar(aStars+i);
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
void initArrayStars(Star aStars[NUM_STARS], int size, int aID[])
{
	int name_len;
	name_len = rand()%6 + 5;
	for(int i = 0 ; i < NUM_STARS; i++)
	{
		(aStars+i)->name[0] = rand()%26 + 'A';
		for (int j=1; j<name_len; j++) 
		{
			(aStars+i)->name[j] = rand()%26 + 'a';
		}
		(aStars + i)->name[name_len] = NULL;
		(aStars + i) -> id = aID[i];
		(aStars + i)->distance = (double)(rand()%10000 + 10.0);
		(aStars + i)->luminosity = (double)(rand()%10000 + 10.0);
		(aStars + i)->mass = (double)(rand()%10000 + 10.0);
		(aStars + i)->radius = (double)(rand()%10000 + 10.0);
		(aStars + i)->age = rand()%10000 + 10;
	}
}
void printStar(Star *pS)
{
	cout << " Star_ID (" << setw(3) << pS->id ;
	cout << "), Name (" << pS->name << ")" << endl;
}

