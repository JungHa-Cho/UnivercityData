#include "C_Circle.h"
#define PI 3.14159

ostream& operator<<(ostream& output, Circle & c){
	output<<" "<<c.getName()<<" <radius:"<<c.radius<<", area:"<<c.getArea()<<">";
	return output;
}

Circle::Circle():Shape(),radius(1.0){
	cout<<"Construct <"<<getName()<<">. ";
}

Circle::Circle(int x, int y, int r, string clr):Shape(x,y,clr),radius(r){
	cout<<"Construct <"<<getName()<<">. ";
}

Circle::Circle(Circle &cir):Shape(cir.pos_x,cir.pos_y,cir.color),radius(cir.radius){
	cout<<"Copy construct <"<<getName()<<">. ";
}

Circle::~Circle(){
	cout<<"Destructor ("<<getName()<<"). ";
}

double Circle::getArea(){
	return PI*radius*radius;
}
string Circle::getColor(){
	return this->color;
}
string Circle::getName(){
	return "Circle";
}
void Circle::printAttributes(){
	cout<<"pos("<<pos_x<<", "<<pos_y<<"), radius ("<<radius<<"), color("<<color<<")";
}
const Circle Circle::operator++(){
	radius++;
	return *this;
}
const Circle Circle::operator++(int dummy){
	Circle a(*this);
	radius++;
	return a;
}
const Circle Circle::operator--(){
	if(radius<1.0)
		exit(0);
	radius--;
	return *this;
}
const Circle Circle::operator--(int dummy){
	if(radius<1.0)
		exit(0);
	Circle *a=new Circle(*this);
	radius--;
	return *a;
}
