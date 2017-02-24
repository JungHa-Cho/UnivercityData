/*
* File Name: "main.cpp"
* Description:
* - This program is 
*						Lab10 - inheritance
* Programmed by Jung-Ha Cho,
* Last updated: Version 2.0, May 23, 2012 (by Jung-Ha Cho).
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/05/23) Version Remarks
* J.H Cho 2012/05/23 1.0 Project & Main function is created
* J.H Cho 2012/05/23 2.0 Exam is done
* ========================================================
*/
#include <iostream>
#include <string>
#include "C_Shape.h"
#include "C_Circle.h"
#include "C_Square.h"
#include "C_Cylinder.h"
#include "C_Hexahedron.h"
using namespace std;
#define NUM_SHAPES 4
void main()
{
	Shape *pShapes[NUM_SHAPES];
	Circle *pCir;
	Cylinder *pCyl;
	Square *pSq;
	Hexahedron *pHexa;
	pCir = new Circle(1, 2, 3, "RED");
	cout << *pCir << endl;
	pSq = new Square(1, 2, 3, "BLUE");
	cout << *pSq << endl;
	pCyl = new Cylinder(1, 2, 3, 4, "YELLOW");
	cout << *pCyl << endl;
	pHexa = new Hexahedron(1, 2, 3, 4, "CYAN");
	cout << *pHexa << endl;
	pShapes[0] = pCir;
	pShapes[1] = pSq;
	pShapes[2] = pCyl;
	pShapes[3] = pHexa;
	for (int i=0; i<NUM_SHAPES; i++)
	{
		cout << "pShapes[" << i <<"]->getName() : " <<pShapes[i]->getName();
		cout << ", attributes: ";
		pShapes[i]->printAttributes();
		cout << endl;
	}
	cout << endl;
	cout << *pCyl << endl;
	cout << "prefix increment: ";
	cout << ++(*pCyl) << endl;
	cout << "postfix increment: ";
	(*pCyl)++;
	cout << endl << *pCyl << endl;

	cout << endl;
	cout << *pHexa << endl;
	cout << "prefix increment: ";
	cout << --(*pHexa) << endl;
	cout << "postfix increment: ";
	
	(*pHexa)--;
	
	cout << endl << *pHexa << endl;
	cout << endl;

	cout << "\nDeleting Cylinder: " ;
	delete pCyl;
	cout << "\nDeleting Hexahedron: " ;
	delete pHexa;

	cout << endl << endl;
} // end of main()