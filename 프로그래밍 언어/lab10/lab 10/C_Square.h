#ifndef C_SQUARE_H
#define C_SQUARE_H

#include <iostream>
#include <string>
#include "C_Shape.h"
using namespace std;


class Square:public Shape{
	friend ostream& operator<<(ostream& output, Square & c);
protected:
	double side;
public:
	Square();
	Square(int x, int y, int s, string clr);
	Square(Square &sq);
	~Square();
	virtual double getArea();
	virtual double getVolume(){return 0.0;}
	virtual string getColor();
	virtual string getName();
	virtual void printAttributes();
	const Square operator++();
	const Square operator++(int dummy);
	const Square operator--();
	const Square operator--(int dummy);
};

#endif