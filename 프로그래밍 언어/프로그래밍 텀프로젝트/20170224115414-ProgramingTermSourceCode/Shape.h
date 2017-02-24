/************ 부모 클래스 Shape의 선언 *************/

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <windows.h>
using namespace std;

class Shape{
public:
	Shape();                     //디폴트 생성자
	Shape(int x, int y);         //생성자
	//~Shape();                  //소멸자
	void gotoXY(int x, int y);   // xy좌표로 이동
	int getPos_x();              //Shape 클래스의 X값 리턴
	int getPos_y();              //Shape 클래스의 Y값 리턴
	void setPos_x(int x);        //Shape 클래스의 X값 초기화
	void setPos_y(int y);        //Shape 클래스의 Y값 초기화
protected:
	int Pos_x;                   //멤버 변수 선언
	int Pos_y;                   //멤버 변수 선언
};

#endif




	
