#ifndef C_CYLINDER_H
#define C_CYLINDER_H

#include <iostream>
#include <string>
#include "C_Circle.h"
using namespace std;
class Cylinder:public Circle{
	friend ostream& operator<<(ostream& output, Cylinder & c);
protected:
	double height;
public:
	Cylinder();
	Cylinder(int x, int y, int r, int h, string clr);
	Cylinder(Cylinder& cyl);
	~Cylinder();
	double getArea();
	double getVolume();
	string getColor();
	string getName();
	void printAttributes();
	Cylinder& operator++();
	Cylinder& operator++(int dummy);
	Cylinder& operator--();
	Cylinder& operator--(int dummy);
};

#endif