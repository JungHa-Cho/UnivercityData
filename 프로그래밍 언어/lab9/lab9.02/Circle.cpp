#include "Circle.h"
#include <iostream>
using namespace std;

Circle::Circle()
{
	radius = 1.0;
}
Circle::Circle(int x, int y, double z)
{
	Circle::x = x;
	Circle::y = y;
	Circle::radius = z;
}
double Circle::area() const
{
	double A;
	A = 4 * 3.14 * (Circle::radius/2) * (Circle::radius/2); //±∏¿« ≥–¿Ã
	return A;
}
double Circle::volume() const
{
	double A;
	A = 4/3 * 3.14 * (Circle::radius/2) * (Circle::radius/2) * (Circle::radius/2);
	return A;
}
ostream &operator << ( ostream & output, const Circle & c )
{
	output<<c.x<<c.y<<c.radius<<endl;
	return output;
}
