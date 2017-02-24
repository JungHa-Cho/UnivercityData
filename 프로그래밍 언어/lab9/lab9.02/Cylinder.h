#ifndef CYLINDER_H
#define CYLINDER_H

#include "Circle.h"
#include <fstream>
using namespace std;

class Cylinder:public Circle{
	friend ostream &operator << ( ostream &, const Cylinder & );
protected:
	double height;
public:
	Cylinder();
	Cylinder(int x, int y, double z, double h);
	double area() const;
	double volume() const;
};

#endif