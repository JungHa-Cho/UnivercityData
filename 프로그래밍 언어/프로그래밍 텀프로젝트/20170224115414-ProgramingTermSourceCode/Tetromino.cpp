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
char TetrTile[][5] = {"·","■","□"};
unsigned short colorTable[]={0xffff, 0x0003, 0x000e, 0x000d, 0x0009, 0x000a, 0x000c, 0x0005};                 // 색 헥사코드

int BRICKS[][4][8]={
	{ { -1,0,0,0,1,0,2,0 } , { 0,-2,0,-1,0,0,0,1 } , { -1,0,0,0,1,0,2,0 } , { 0,-2,0,-1,0,0,0,1 } } ,         // I형
	{ { 0,-1,1,-1,0,0,1,0 } , { 0,-1,1,-1,0,0,1,0 } , { 0,-1,1,-1,0,0,1,0 } , { 0,-1,1,-1,0,0,1,0 } } ,       // O형
	{ { 0,-2,0,-1,0,0,1,0 } , { -2,0,-1,0,0,0,0,-1 } , { -1,0,0,0,0,1,0,2 } , { 0,0,1,0,2,0,0,1 } } ,         // L형
	{ { -1,0,0,0,0,-1,0,-2 } , { -2,0,-1,0,0,0,0,1 } , { 0,0,1,0,0,1,0,2 } , { 0,-1,0,0,1,0,2,0 } } ,         // J형 
	{ { 0,-1,1,-1,-1,0,0,0 } , { -1,-1,-1,0,0,0,0,1 } , { 0,-1,1,-1,-1,0,0,0 } , { -1,-1,-1,0,0,0,0,1 } } ,   // S형
	{ { -1,-1,0,-1,0,0,1,0 } , { 0,-1,-1,0,0,0,-1,1 } , { -1,-1,0,-1,0,0,1,0 } , { 0,-1,-1,0,0,0,-1,1 } } ,   // Z형
	{ { -1,0,0,0,1,0,0,1 } , { 0,-1,0,0,1,0,0,1 } , { 0,-1,-1,0,0,0,1,0 } , { 0,-1,-1,0,0,0,0,1 } }           // T형
};
Tetromino::Tetromino()                                             // 디폴트 생성자
{
	ppbrickPosition = new Position *[4];                           // 더블포인터 이차원배열 ppbrickPosition 동적할당
	for(int i = 0 ; i < 4 ; i ++)                                  // 이차원 배열 동적할당
	{                                                              //
		ppbrickPosition[i] = new Position [4];                     //
	}       
	tetr_type = 0;                                                 // 
	string tetr_name = "EMPTY";
	tetr_color = NULL;
	tetr_rot = 0;
	for(int i = 0 ; i < NUM_BRICKS ; i ++)                         // 0 ~ 4 까지
	{
		for(int j = 0 ; j < 8 ; j = j + 2)                         // brick의 좌표값 8개를 위해 반복문 8개와 인덱스 선택을 위한 
		{                                                          // 반복문의 인덱스 i 는 0123 j 는 2,4,6,8,10,12,14,16,18 
			brickPosition[i][j/2].x = 0;						   // brick 00, 01, 02, 03, 04, 05, 06, 07, 08 
			brickPosition[i][j/2].y = 0;					       // brick 00, 01, 02, 03, 04, 05, 06, 07, 08
			ppbrickPosition[i][j/2].x = 0;     // BRICKS = 00, 02, 04, 06 정의된 BRICKS의 X 좌표
			ppbrickPosition[i][j/2].y = 0;     // BRICKS = 01, 03, 05, 07 정의된 BRICKS의 Y 좌표
		}	                                                       // Position형 brickPosition에 Tetro 정보 담김
	}
}
Position **Tetromino::ppgetBrickPositions()
{
	return ppbrickPosition;
}
string Tetromino::getName()
{
	return tetr_name;                // 테트로 네임 리턴
}
int Tetromino::getType()
{
	return tetr_type;                //테트로 타입 리턴
}
int Tetromino::getRot()
{
	return tetr_rot;                 //테트로 로테이션 리턴
}
void Tetromino::initTetrominos(int type, string name)              // Tetromino 초기화
{
	ppbrickPosition = new Position *[4];                           // 더블포인터 이차원배열 ppbrickPosition 동적할당
	for(int i = 0 ; i < 4 ; i ++)                                  // 이차원 배열 동적할당
	{                                                              //
		ppbrickPosition[i] = new Position [4];                     //
	}                                                              //

	tetr_type = type;                                              // tetrotype 초기화
	tetr_color = type;                                             // tetrocolor 초기화
	for(int i = 0 ; i < NUM_BRICKS ; i ++)                         // 0 ~ 4 까지
	{
		for(int j = 0 ; j < 8 ; j = j + 2)                         // brick 좌표 값 = 8개, 8번 만큼 j는 2씩 늘어남
		{
			brickPosition[i][j/2].x = BRICKS[tetr_type][i][j];     // BRICKS = 00, 02, 04, 06 정의된 BRICKS의 X 좌표
			brickPosition[i][j/2].y = BRICKS[tetr_type][i][j+1];   // BRICKS = 01, 03, 05, 07 정의된 BRICKS의 Y 좌표
			ppbrickPosition[i][j/2].x = BRICKS[tetr_type][i][j];     // BRICKS = 00, 02, 04, 06 정의된 BRICKS의 X 좌표
			ppbrickPosition[i][j/2].y = BRICKS[tetr_type][i][j+1];   // BRICKS = 01, 03, 05, 07 정의된 BRICKS의 Y 좌표
		}	                                                       // Position형 brickPosition에 Tetro 정보 담김
	}
}
void Tetromino::setType(int type)
{
	tetr_type = type;                //셋 타입
}
void Tetromino::setPos(int x, int y)
{
	Pos_x = x;                       // 기준 좌표 셋
	Pos_y = y;
}
void Tetromino::setRot(int r)
{
	tetr_rot = r;                   //로테이션 셋
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
		gotoXY(this->getPos_x() + brickPosition[Tetromino::getRot()][j].x, this->getPos_y() + brickPosition[Tetromino::getRot()][j].y);    // Pos_x에 brick의 좌표값을 빼줘서 해당 위치로 이동
		puts(TetrTile[0]);
	}
}
void Tetromino::drawTETR()
{
	for(int j = 0 ; j < NUM_BRICKS ; j ++)
	{
		gotoXY(getPos_x() + brickPosition[Tetromino::getRot()][j].x, getPos_y() + brickPosition[Tetromino::getRot()][j].y);    // Pos_x에 brick의 좌표값을 빼줘서 해당 위치로 이동
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTable[tetr_color]);  // 색 선택 콘솔 // tetr_color = tetr_type 번호
		puts(TetrTile[1]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 색 선택 콘솔
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