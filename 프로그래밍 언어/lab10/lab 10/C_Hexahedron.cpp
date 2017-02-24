#include "C_Hexahedron.h"

ostream& operator<<(ostream& output,  Hexahedron & c){
	output<<c.getName()<<"<"<<c.side<<", "<<c.height<<", area:"<<c.getArea()<<", volume:"<<c.getVolume()<<")";
	return output;
}
Hexahedron::Hexahedron():Square(),height(1.0){
	cout<<"Construct <"<<getName()<<">. ";
}
Hexahedron::Hexahedron(int x, int y, int s, int h, string clr):Square(x,y,s,clr),height(h){
	cout<<"Construct <"<<getName()<<">. ";
}
Hexahedron::Hexahedron( Hexahedron& hx):Square(hx.pos_x,hx.pos_y,hx.side,hx.color),height(hx.height){
	cout<<"Copy construct <"<<getName()<<">. ";
}
Hexahedron::~ Hexahedron(){
	cout<<"Destructor ("<<getName()<<"). ";
}
double Hexahedron::getArea(){
	cout<<"hhhhhhhhhhhhhhhhhhhhh"<<endl;
	return side*side*2+4*side*height;
}
double Hexahedron::getVolume(){
	return side*side*height;
}
string Hexahedron::getColor(){
	return color;
}
string Hexahedron::getName(){
	return "Hexahedron";
}
void Hexahedron::printAttributes(){
	cout<<"pos("<<pos_x<<", "<<pos_y<<"), side ("<<side<<"), height("<<height<<"), color("<<color<<")";
}
Hexahedron& Hexahedron::operator++(){
	side++;
	height++;	
	return *this;
}
Hexahedron& Hexahedron::operator++(int dummy){
	Hexahedron *a=new Hexahedron(*this);
	side++;
	height++;
	return *a;
}
 Hexahedron& Hexahedron::operator--(){
	if((side<1.0)||(height<1.0))
		exit(0);
	side--;
	height--;
	return *this;
}
Hexahedron& Hexahedron::operator--(int dummy){
	if((side<1.0)||(height<1.0))
		exit(0);
	Hexahedron *a=new Hexahedron(*this);
	side--;
	height--;
	return *a;
}