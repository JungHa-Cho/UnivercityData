/**
* MyGalaxy.h
*/
#include "MyStar.h"
typedef struct MyGalaxy
{
	Star *pFirst;
	Star *pLast;
	int num_star;
} Galaxy;