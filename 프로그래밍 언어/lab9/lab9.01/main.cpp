/** * main.cpp */
#include <iostream>
#include "DateArray.h"
#include "Date.h"

using namespace std;
#define NUM_DATES 12

void main()
{
	DateArray dates(NUM_DATES);
	Date d;

	cin >> d;
	dates[0] = d;

	for (int i=1; i<NUM_DATES; i++) {
		d = dates[0] + i*25;
		dates[i] = d;
	}
	for (int i=0; i<NUM_DATES; i++) {
		cout << "dates[0] + " << i << "x25 = " << dates[i];
	}
	cout<<endl;
	cout << " dates[0] : " << dates[0] << endl;
	cout << " dates[0]-- : " << dates[0]-- << endl;// postfix
	cout << " dates[0]++ : " << dates[0]++ << endl;
	cout << " --dates[0] : " << --dates[0] << endl;//prefix
	cout << " ++dates[0] : " << ++dates[0] << endl;
	cout << " dates[0] - 3 : " << dates[0] - 3 << endl;
	cout << endl;
}