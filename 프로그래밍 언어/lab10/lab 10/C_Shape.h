#ifndef C_SHAPE_H
#define C_SHAPE_H

#include <iostream>
#include <string>
using namespace std;

class Shape{
protected:
	int pos_x;
	int pos_y;
	string color;
public:
	Shape();
	Shape(int x,int y, string clr);
	Shape(Shape& shp);
	~Shape();
	virtual double getArea()=0;
	virtual double getVolume()=0;
	virtual string getColor()=0;
	virtual string getName()=0;
	virtual void printAttributes()=0;
};





#endif