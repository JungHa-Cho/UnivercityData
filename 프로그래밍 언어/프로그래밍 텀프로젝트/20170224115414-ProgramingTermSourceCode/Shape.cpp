/************ �θ� Ŭ���� Shape�� ����***********/
#include "Shape.h"
using namespace std;

Shape::Shape()                      //����Ʈ ������
{
	Pos_x = 0;
	Pos_y = 0;
}
Shape::Shape(int x, int y)           //������
{
	Pos_x = x;
	Pos_y = y;
}
int Shape::getPos_x()                 //get
{
	return Pos_x;
}
int Shape::getPos_y()                 //get
{
	return Pos_y;
}
void Shape::gotoXY(int x, int y)      //XY ��ǥ�� Ŀ�� �̵�
{
	COORD xy = {x*2, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
void Shape::setPos_x(int x)           //set
{
	Pos_x = x;
}
void Shape::setPos_y(int y)           //set
{
	Pos_y = y;
}