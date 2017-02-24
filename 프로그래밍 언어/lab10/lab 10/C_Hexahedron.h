#ifndef C_HEXAHEDRON_H
#define C_HEXAHEDRON_H
#include <iostream>
#include <string>
#include "C_Square.h"
using namespace std;

class Hexahedron:public Square{
	friend ostream& operator<<(ostream& output,  Hexahedron & c);
protected:
	double height;
public:
	Hexahedron();
	Hexahedron(int x, int y, int s, int h, string clr);
	Hexahedron( Hexahedron& hx);
	~ Hexahedron();
	double getArea();
	double getVolume();
	string getColor();
	string getName();
	void printAttributes();
	Hexahedron& operator++();
	Hexahedron& operator++(int dummy);
	Hexahedron& operator--();
	Hexahedron& operator--(int dummy);
};


#endif