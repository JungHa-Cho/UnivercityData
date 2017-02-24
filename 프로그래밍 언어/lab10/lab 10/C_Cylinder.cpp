#include "C_Cylinder.h"
#define PI 3.14159
ostream& operator<<(ostream& output, Cylinder & c){
	output<<c.getName()<<"<"<<c.radius<<", "<<c.height<<", area:"<<c.getArea()<<", volume:"<<c.getVolume()<<")";
	return output;
}
Cylinder::Cylinder():Circle(),height(1.0){
	cout<<"Construct <"<<getName()<<">. ";
}

Cylinder::Cylinder(int x, int y, int r, int h, string clr):Circle(x,y,r,clr),height(h){
	cout<<"Construct <"<<getName()<<">. ";
}

Cylinder::Cylinder(Cylinder& cyl):Circle(cyl.pos_x,cyl.pos_y,cyl.radius,cyl.color),height(cyl.height){
	cout<<"Copy construct <"<<getName()<<">. ";
}
	
Cylinder::~Cylinder(){
	cout<<"Destructor ("<<getName()<<"). ";
}
double Cylinder::getArea(){
	double a=0.0;
	a+=2.0*Circle::getArea();
	a+=2*PI*radius*height;
	return a;
}

double Cylinder::getVolume(){
	double v=0.0;
	v=Circle::getArea()*height;
	return v;
}
string Cylinder::getColor(){
	return color;
}

string Cylinder::getName(){
	return "Cylinder";
}
void Cylinder::printAttributes(){
	cout<<"pos("<<pos_x<<", "<<pos_y<<"), radius ("<<radius<<"), height("<<height<<"), color("<<color<<")";
}
Cylinder& Cylinder::operator++(){
	radius++;
	height++;
	return *this;
}
Cylinder& Cylinder::operator++(int dummy){
	Cylinder *a=new Cylinder(*this);
	radius++;
	height++;
	return *a;
}
Cylinder& Cylinder::operator--(){
	if(radius<1.0 || height<1.0)
		exit(0);
	radius--;
	height--;
	return *this;
}
Cylinder& Cylinder::operator--(int dummy){
	if(radius<1.0 || height<1.0)
		exit(0);
	Cylinder *a=new Cylinder(*this);
	radius--;
	height--;
	return *a;
}
