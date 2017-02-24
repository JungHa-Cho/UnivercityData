/* Date.h */
#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class DateArray;
class Date{
	friend class DateArray;
	friend istream &operator >> ( istream &, Date & );
	friend ostream &operator << ( ostream &, const Date & );
public:
	Date();
	Date(int y, int m, int d);
	const Date operator+(int dd);
	const Date operator-(int dd);
	const Date operator++();
	const Date operator++(int dummy);
	const Date operator--();
	const Date operator--(int dummy);
	const Date operator=(const Date rightSide);
private:
	int year;
	int month;
	int day;
};
#endif