/* DateArray.h */

#ifndef DATEARRAY_H
#define DATEARRAY_H

#include "Date.h"

class DateArray{
public:
	DateArray();
	DateArray(int numDates);
	Date& operator [] (int sub);
private:
	Date *pDates;
	int numDates;
	void indexOutOfRange(int sub);
};

#endif
