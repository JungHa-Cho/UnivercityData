#include "Tetromino.h"
#include "Tile.h"
#include "Board.h"
#include "KeyBoard.h"

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <conio.h> // for kbhit()
#include <windows.h>

using namespace std;
char TetrTile[][5] = {"��","��","��"};
unsigned short colorTable[]={0xffff, 0x0003, 0x000e, 0x000d, 0x0009, 0x000a, 0x000c, 0x0005};                 // �� ����ڵ�

int BRICKS[][4][8]={
	{ { -1,0,0,0,1,0,2,0 } , { 0,-2,0,-1,0,0,0,1 } , { -1,0,0,0,1,0,2,0 } , { 0,-2,0,-1,0,0,0,1 } } ,         // I��
	{ { 0,-1,1,-1,0,0,1,0 } , { 0,-1,1,-1,0,0,1,0 } , { 0,-1,1,-1,0,0,1,0 } , { 0,-1,1,-1,0,0,1,0 } } ,       // O��
	{ { 0,-2,0,-1,0,0,1,0 } , { -2,0,-1,0,0,0,0,-1 } , { -1,0,0,0,0,1,0,2 } , { 0,0,1,0,2,0,0,1 } } ,         // L��
	{ { -1,0,0,0,0,-1,0,-2 } , { -2,0,-1,0,0,0,0,1 } , { 0,0,1,0,0,1,0,2 } , { 0,-1,0,0,1,0,2,0 } } ,         // J�� 
	{ { 0,-1,1,-1,-1,0,0,0 } , { -1,-1,-1,0,0,0,0,1 } , { 0,-1,1,-1,-1,0,0,0 } , { -1,-1,-1,0,0,0,0,1 } } ,   // S��
	{ { -1,-1,0,-1,0,0,1,0 } , { 0,-1,-1,0,0,0,-1,1 } , { -1,-1,0,-1,0,0,1,0 } , { 0,-1,-1,0,0,0,-1,1 } } ,   // Z��
	{ { -1,0,0,0,1,0,0,1 } , { 0,-1,0,0,1,0,0,1 } , { 0,-1,-1,0,0,0,1,0 } , { 0,-1,-1,0,0,0,0,1 } }           // T��
};
Tetromino::Tetromino()                                             // ����Ʈ ������
{
	ppbrickPosition = new Position *[4];                           // ���������� �������迭 ppbrickPosition �����Ҵ�
	for(int i = 0 ; i < 4 ; i ++)                                  // ������ �迭 �����Ҵ�
	{                                                              //
		ppbrickPosition[i] = new Position [4];                     //
	}       
	tetr_type = 0;                                                 // 
	string tetr_name = "EMPTY";
	tetr_color = NULL;
	tetr_rot = 0;
	for(int i = 0 ; i < NUM_BRICKS ; i ++)                         // 0 ~ 4 ����
	{
		for(int j = 0 ; j < 8 ; j = j + 2)                         // brick�� ��ǥ�� 8���� ���� �ݺ��� 8���� �ε��� ������ ���� 
		{                                                          // �ݺ����� �ε��� i �� 0123 j �� 2,4,6,8,10,12,14,16,18 
			brickPosition[i][j/2].x = 0;						   // brick 00, 01, 02, 03, 04, 05, 06, 07, 08 
			brickPosition[i][j/2].y = 0;					       // brick 00, 01, 02, 03, 04, 05, 06, 07, 08
			ppbrickPosition[i][j/2].x = 0;     // BRICKS = 00, 02, 04, 06 ���ǵ� BRICKS�� X ��ǥ
			ppbrickPosition[i][j/2].y = 0;     // BRICKS = 01, 03, 05, 07 ���ǵ� BRICKS�� Y ��ǥ
		}	                                                       // Position�� brickPosition�� Tetro ���� ���
	}
}
Position **Tetromino::ppgetBrickPositions()
{
	return ppbrickPosition;
}
string Tetromino::getName()
{
	return tetr_name;                // ��Ʈ�� ���� ����
}
int Tetromino::getType()
{
	return tetr_type;                //��Ʈ�� Ÿ�� ����
}
int Tetromino::getRot()
{
	return tetr_rot;                 //��Ʈ�� �����̼� ����
}
void Tetromino::initTetrominos(int type, string name)              // Tetromino �ʱ�ȭ
{
	ppbrickPosition = new Position *[4];                           // ���������� �������迭 ppbrickPosition �����Ҵ�
	for(int i = 0 ; i < 4 ; i ++)                                  // ������ �迭 �����Ҵ�
	{                                                              //
		ppbrickPosition[i] = new Position [4];                     //
	}                                                              //

	tetr_type = type;                                              // tetrotype �ʱ�ȭ
	tetr_color = type;                                             // tetrocolor �ʱ�ȭ
	for(int i = 0 ; i < NUM_BRICKS ; i ++)                         // 0 ~ 4 ����
	{
		for(int j = 0 ; j < 8 ; j = j + 2)                         // brick ��ǥ �� = 8��, 8�� ��ŭ j�� 2�� �þ
		{
			brickPosition[i][j/2].x = BRICKS[tetr_type][i][j];     // BRICKS = 00, 02, 04, 06 ���ǵ� BRICKS�� X ��ǥ
			brickPosition[i][j/2].y = BRICKS[tetr_type][i][j+1];   // BRICKS = 01, 03, 05, 07 ���ǵ� BRICKS�� Y ��ǥ
			ppbrickPosition[i][j/2].x = BRICKS[tetr_type][i][j];     // BRICKS = 00, 02, 04, 06 ���ǵ� BRICKS�� X ��ǥ
			ppbrickPosition[i][j/2].y = BRICKS[tetr_type][i][j+1];   // BRICKS = 01, 03, 05, 07 ���ǵ� BRICKS�� Y ��ǥ
		}	                                                       // Position�� brickPosition�� Tetro ���� ���
	}
}
void Tetromino::setType(int type)
{
	tetr_type = type;                //�� Ÿ��
}
void Tetromino::setPos(int x, int y)
{
	Pos_x = x;                       // ���� ��ǥ ��
	Pos_y = y;
}
void Tetromino::setRot(int r)
{
	tetr_rot = r;                   //�����̼� ��
}
void Tetromino::setName(string na)
{
	tetr_name = na;
}
bool Tetromino::rotate(Board *pB)
{
	Tile **TileArray;
	TileArray = pB->getppTileArray();

	int chk=0;
	tetr_rot++;
	if(tetr_rot==4)
		tetr_rot=0;

	for(int i = 0 ; i < 4 ; i ++)
	{
		if(TileArray[ getPos_x() - pB->getPos_x() + ppbrickPosition[this->getRot()][i].x ][ getPos_y() - pB->getPos_y() + ppbrickPosition[this->getRot()][i].y ].tileType > 0)
		{
			chk++;
		}
	}

	if(tetr_rot==0)
	{tetr_rot = 3;}else
	{tetr_rot--;}
	if(chk > 0)
	{return false;}else
	{return true;}
}
void Tetromino::removeTETR()
{
	for(int j = 0 ; j < NUM_BRICKS ; j ++)
	{
		gotoXY(this->getPos_x() + brickPosition[Tetromino::getRot()][j].x, this->getPos_y() + brickPosition[Tetromino::getRot()][j].y);    // Pos_x�� brick�� ��ǥ���� ���༭ �ش� ��ġ�� �̵�
		puts(TetrTile[0]);
	}
}
void Tetromino::drawTETR()
{
	for(int j = 0 ; j < NUM_BRICKS ; j ++)
	{
		gotoXY(getPos_x() + brickPosition[Tetromino::getRot()][j].x, getPos_y() + brickPosition[Tetromino::getRot()][j].y);    // Pos_x�� brick�� ��ǥ���� ���༭ �ش� ��ġ�� �̵�
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTable[tetr_color]);  // �� ���� �ܼ� // tetr_color = tetr_type ��ȣ
		puts(TetrTile[1]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �� ���� �ܼ�
	}
}
bool Tetromino::checkSpace(Board *pB, int xx, int yy)
{
	Tile **TileArray;
	TileArray = pB->getppTileArray();

	int chk=0;
	for(int i = 0 ; i < 4 ; i ++)
	{
		if(TileArray[ getPos_x() - pB->getPos_x() + xx + ppbrickPosition[this->getRot()][i].x ][ getPos_y() - pB->getPos_y() + yy + ppbrickPosition[this->getRot()][i].y ].tileType > 0)
		{
			chk++;
		}
	}
	if(chk > 0)
	{return false;}
	else
	{return true;}
}