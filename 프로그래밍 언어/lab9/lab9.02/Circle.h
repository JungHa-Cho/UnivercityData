#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <fstream>
using namespace std;

class Circle:public Shape{
	friend ostream &operator << ( ostream &, const Circle & );
protected:
	double radius;
public:
	Circle();
	Circle(int x, int y, double z);
	double area() const;
	double volume() const;
};

#endif