#include "C_Shape.h"

Shape::Shape():pos_x(0),pos_y(0),color("BLACK")
{
}
Shape::Shape(int x,int y, string clr):pos_x(x),pos_y(y),color(clr)
{
	cout<<"Construct <"<<getName()<<">. ";
}
Shape::Shape(Shape& shp):pos_x(shp.pos_x),pos_y(shp.pos_y),color(shp.color)
{
	cout<<"Copy construct <"<<getName()<<">. ";
}
Shape::~Shape()
{
	cout<<"Destructor <"<<getName()<<">. ";
}
string Shape::getName()
{
	return "Shape";
}