#include <iostream>
#include "Date.h"
using namespace std;

ostream &operator << ( ostream &output, const Date &d )
{
	output<<"This Date : "<<d.year<<", "<<d.month<<", "<<d.day<<endl;
	return output;
}
istream &operator >> ( istream &input, Date &d )
{
	cout<<"input the day (yyyy. mm. dd) : "; cin>>d.year>>d.month>>d.day; cout<<endl;
	return input;
}
Date::Date()
{
	year = 1;
	month = 1;
	day = 1;
}
Date::Date(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
}
const Date Date::operator=(const Date rightSide)
{
	year = rightSide.year;
	month = rightSide.month;
	day = rightSide.day;

	return *this;
}
const Date Date::operator+(int dd)
{
	Date returnDate;
	int operD = 0, operM = 0, operY = 0, operSUM = 0;
	int monthday[13] = { 0, 31, 59, 90, 120, 151, 181, 
		212, 243, 273, 304, 334, 365 };

	operY = year * 365;
	operM = monthday[month];
	operD = day;
	operSUM = operY + operM + operD + dd;

	returnDate.year = operSUM / 365;
	operM = operSUM % 365 ;

	if(operM <= 31)   //나머지 일수가 한달보다 적을때
	{
		if(operM = 31)
		{
			returnDate.month = 1;
			returnDate.day = 31;

		}
		returnDate.month = 1;
		returnDate.day = operM;
	}

	if(operM > 31)
	{
		for(int i = 1 ; i < 13 ; i++)
		{
			if(monthday[i] >= operM)
			{
				if(monthday[i] == operM)
				{
					returnDate.month = i - 1;
					returnDate.day = operM - monthday[i-1];
					break;
				}
				returnDate.month = i - 1;
				returnDate.day = operM - monthday[i-1];
				break;
			}
		}
	}

	return returnDate;
}
const Date Date::operator-(int dd)
{
	if(month == 1 && day <= 3)
	{
		cout<<"-3 을 계산할수 없습니다."<<endl;
		exit(1);
	}
	Date returnDate;
	int operD = 0, operM = 0, operY = 0, operSUM = 0;
	int monthday[13] = { 0, 31, 59, 90, 120, 151, 181, 
		212, 243, 273, 304, 334, 365 };

	operY = year * 365;
	operM = monthday[month];
	operD = day;
	operSUM = operY + operM + operD - dd;

	returnDate.year = operSUM / 365;
	operM = operSUM % 365 ;

	if(operM <= 31)   //나머지 일수가 한달보다 적을때
	{
		if(operM = 31)
		{
			returnDate.month = 1;
			returnDate.day = 31;
		}
		returnDate.month = 1;
		returnDate.day = operM;
	}

	if(operM > 31)
	{
		for(int i = 1 ; i < 13 ; i++)
		{
			if(monthday[i] >= operM)
			{
				if(monthday[i] == operM)
				{
					returnDate.month = i - 1;
					returnDate.day = operM - monthday[i-1];
					break;
				}
				returnDate.month = i - 1;
				returnDate.day = operM - monthday[i-1];
				break;
			}
		}
	}

	return returnDate;
}
const Date Date::operator--() //prefix
{
	int monthday[13] = { 0, 31, 59, 90, 120, 151, 181, 
		212, 243, 273, 304, 334, 365 };

	day = --day;
	if(day==0)
	{
		if(month - 1 == 0)
		{
			month = 12;
			year = year - 1;
			if(year == 0)
			{
				cout<<"더이상 뺄 수 없습니다."<<endl;
			}
			day = 30;
		}
		month = month - 1;
		day = monthday[month] - monthday[month-1];
	}
	return *this;
}
const Date Date::operator++()
{
	int monthday[13] = { 0, 31, 59, 90, 120, 151, 181, 
		212, 243, 273, 304, 334, 365 };

	day = ++day;
	if(day==0)
	{
		if(month - 1 == 0)
		{
			month = 12;
			year = year - 1;
			if(year == 0)
			{
				cout<<"더이상 뺄 수 없습니다."<<endl;
			}
			day = 30;
		}
		month = month - 1;
		day = monthday[month] - monthday[month-1];
	}
	return *this;
}
const Date Date::operator--(int dummy)//postfix
{
	int monthday[13] = { 0, 31, 59, 90, 120, 151, 181, 
		212, 243, 273, 304, 334, 365 };

	Date result(year, month, day);
	day = day--;
	if(day==0)
	{
		if(month - 1 == 0)
		{
			month = 12;
			year = year - 1;
			if(year == 0)
			{
				cout<<"더이상 뺄 수 없습니다."<<endl;
			}
			day = 30;
		}
		month = month - 1;
		day = monthday[month] - monthday[month-1];
	}
	return result;
}
const Date Date::operator++(int dummy)
{
	int monthday[13] = { 0, 31, 59, 90, 120, 151, 181, 
		212, 243, 273, 304, 334, 365 };

	Date result(year, month, day);
	day = day++;
	if(day==0)
	{
		if(month - 1 == 0)
		{
			month = 12;
			year = year - 1;
			if(year == 0)
			{
				cout<<"더이상 뺄 수 없습니다."<<endl;
			}
			day = 30;
		}
		month = month - 1;
		day = monthday[month] - monthday[month-1];
	}

	return result;
}
