#include "Cylinder.h"
#include <iostream>
using namespace std;

Cylinder::Cylinder()
{
	height = 1.0;
}
Cylinder::Cylinder(int x, int y, double z, double h)
{
	Cylinder::x=x;

	height = h;
}
double Cylinder::area() const
{
	double A;
	A = 3.14 * (radius/2) * (radius/2); //¿ø±âµÕ ³ĞÀÌ
	return A;
}
double Cylinder::volume() const
{
	double A;
	A = (2 * 3.14 * (radius/2) * (radius/2)) + (2 * (radius/2) * 3.14 * height); //¿ø±âµÕ ºÎÇÇ
	return A;
}
ostream &operator << ( ostream & output, const Cylinder & c)
{
	output<<c.x<<c.y<<c.radius<<c.height<<endl;
	return output;
}
