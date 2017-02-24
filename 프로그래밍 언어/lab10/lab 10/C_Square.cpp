#include "C_Square.h"


ostream& operator<<(ostream& output, Square & c){
	output<<" "<<c.getName()<<"<"<<c.side<<", area:"<<c.getArea()<<">";
	return output;

}
Square::Square():Shape(),side(1.0)
{
	cout<<"Construct <"<<getName()<<">. ";
}

Square::Square(int x, int y, int s, string clr):Shape(x,y,clr),side(s){
	cout<<"Construct <"<<getName()<<">. ";
}
Square::Square(Square &sq):Shape(sq.pos_x,sq.pos_y,sq.color),side(sq.side){
	cout<<"Copy construct <"<<getName()<<">. ";
}

Square::~Square(){
	cout<<"\nDestructor ("<<getName()<<"). ";
}

double Square::getArea(){
	cout<<"gggggggggggggggggggggg"<<endl;
	return side*side;
}
string Square::getColor(){
	return color;
}
string Square::getName(){
	return "Square";
}
void Square::printAttributes(){
	cout<<"pos("<<pos_x<<", "<<pos_y<<"), side ("<<side<<"), color("<<color<<")";
}
const Square Square::operator++(){
	side++;
	return *this;
}
const Square Square::operator++(int dummy){
	Square a(*this);
	side++;
	return a;
}
const Square Square::operator--(){
	if(side<1.0)
		exit(0);
	side--;
	return *this;
}
const Square Square::operator--(int dummy){
	if(side<1.0)
		exit(0);
	Square a(*this);
	side--;
	return a;
}
