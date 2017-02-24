#include "Cylinder.h"
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
	ofstream outf("output.dat", ios::out);
	Circle circle1(1, 2, 3), circle2(4, 5, 6);
	Cylinder Cylinder1(1,2,3,4), Cylinder2(5,6,7,8); 
	
	outf << circle1 << ", area of circle 1 is : " << circle1.area() << endl;
	outf << circle2 << ", area of circle 2 is : " << circle2.area() << endl;
	outf << Cylinder1 << ", volume of cylinder 1 is : " << Cylinder1.volume() << endl;
	outf << Cylinder2 << ", volume of cylinder 2 is : " << Cylinder2.volume() << endl;
}