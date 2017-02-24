/************ 부모 클래스 Shape의 정의***********/
#include "Shape.h"
using namespace std;

Shape::Shape()                      //디폴트 생성자
{
	Pos_x = 0;
	Pos_y = 0;
}
Shape::Shape(int x, int y)           //생성자
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
void Shape::gotoXY(int x, int y)      //XY 좌표로 커서 이동
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