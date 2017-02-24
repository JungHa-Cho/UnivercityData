#ifndef C_CIRCLE_H
#define C_CIRCLE_H

#include <iostream>
#include <string>
#include "C_Shape.h"
using namespace std;

class Circle:public Shape{
	friend ostream& operator<<(ostream& output, Circle & c);
protected:
	double radius;
public:
	Circle();
	Circle(int x, int y, int r, string clr);
	Circle(Circle &cir);
	~Circle();
	virtual double getArea();
	virtual double getVolume(){return 0.0;}
	virtual string getColor();
	virtual string getName();
	virtual void printAttributes();
	const Circle operator++();
	const Circle operator++(int dummy);
	const Circle operator--();
	const Circle operator--(int dummy);
};

#endif