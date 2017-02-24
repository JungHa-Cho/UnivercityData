#include "DateArray.h"
#include "Date.h"
#include <iostream>
using namespace std;

DateArray::DateArray(int num)
{
	pDates = new Date[num];
	numDates = num;
}
Date &DateArray::operator [](int sub)
{
	if (sub < 0 || sub >= numDates)
		indexOutOfRange(sub);
	return pDates[sub];
}
void DateArray::indexOutOfRange(int sub)
{
	cout<<"Dates[sub] .. size error"<<endl;
}