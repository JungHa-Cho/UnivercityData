/************ �θ� Ŭ���� Shape�� ���� *************/

#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <windows.h>
using namespace std;

class Shape{
public:
	Shape();                     //����Ʈ ������
	Shape(int x, int y);         //������
	//~Shape();                  //�Ҹ���
	void gotoXY(int x, int y);   // xy��ǥ�� �̵�
	int getPos_x();              //Shape Ŭ������ X�� ����
	int getPos_y();              //Shape Ŭ������ Y�� ����
	void setPos_x(int x);        //Shape Ŭ������ X�� �ʱ�ȭ
	void setPos_y(int y);        //Shape Ŭ������ Y�� �ʱ�ȭ
protected:
	int Pos_x;                   //��� ���� ����
	int Pos_y;                   //��� ���� ����
};

#endif




	
