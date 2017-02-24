/** board.cpp **/
#include "Board.h"
#include "Tile.h"
#include "Tetromino.h"
#include "Position.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <stdio.h>
#include <conio.h> // for kbhit()
using namespace std;

char getTile[][5] = {"·","■","□"};  // 타일 모양 저장,,, 전역변수
string TetrName[] = {"TETR_I", "TETR_O", "TETR_L", "TETR_J", "TETR_S", "TETR_Z", "TETR_T"};
unsigned short colorTable1[]={0xffff, 0x0003, 0x000e, 0x000d, 0x0009, 0x000a, 0x000c, 0x0005}; 

Board::Board()                        // 보드 디폴트 생성자
{
	Pos_x = 0;
	Pos_y = 0;
	width = 0;
	height = 0;
}
Board::Board(int x, int y, int wid, int hei) // 보드의 정보를 아규먼트로 받는 생성자
{
	Pos_x = x;
	Pos_y = y;
	width = wid;
	height = hei;

	ppTileArray = new Tile *[width];                              // 2차원 배열 초기화
	for(int i = 0 ; i < width ; i++)     
	{
		ppTileArray[i] = new Tile [height];                    
	}
}
Tetromino *Board::addTetr(int tetr_type) /**  addTetr 여기에서 모든 테트로미노 관련 정보를 초기화한다.  **///  
{   
	int Bx = Pos_x + (width / 2);      // x preview 설정 Preview 시작점에 width / 2 는 중심 잡기         // 보드에 테트로미노 그릴 기준점 정의
	int By = Pos_y + 3;                // y preview 설정 기준점에서 밑으로 3칸                           // 

	Tetromino *TETRO;                  // Tetromino New 만듬                                           //  테트로미노형 포인터 TETRO 생성
	TETRO = new Tetromino;             // 동적할당                                                     //  동적할당
	TETRO->setPos_x(Bx);               // TETRO의 정보 셋팅                                            //   
	TETRO->setPos_y(By);               // TETRO의 정보 셋팅  
	TETRO->initTetrominos(tetr_type, TetrName[tetr_type]); // 테트로미노 초기화, 난수 = tetr_type;      // 테트로미노 초기화
	TETRO->setName(TetrName[tetr_type]);                                                                             //
	return TETRO;                                                                                     //
}
void Board::initBoard()
{
	for(int i = 0 ; i < width ; i ++)                             // 너비 만큼 
	{ 
		for( int j = 0 ; j < height ; j ++)                       // 높이 만큼
		{
			if(i == 0 || j == 0 || i == width-1 || j == height-1) // 그려야 하는 보드의 정보
			{										                                    
				ppTileArray[i][j].tileType = WALL;                // 2차원 배열을 가리키는 포인터 ppTileArray
				ppTileArray[i][j].tileColor = 0;
			}                                                     // 구조체 정보의 타일타입을 저장 
			if(i != 0 && j != 0 && i != width-1 && j != height-1) // 그려야 하는 보드의 정보
			{                                                                           
				ppTileArray[i][j].tileType = EMPTY;               // tile의 구조체는 TileType과 TileColor를 저장
				ppTileArray[i][j].tileColor= 0;
			}
		}
	}
}
void Board::drawBoard()                                           // 저장된 보드를 그리는 함수
{
	for(int i = Pos_x ; i < width + Pos_x ; i ++)                 // 여기서 i와 j는 main문에서 보드 클래스를 생성할때 넣은 정보를 기준으로 한다.
	{
		for(int j = Pos_y ; j < height + Pos_y ; j ++)            // 즉, 보드의 정보를 아규먼트로 받는 생성자로 보드의 기준점과 너비 높이를 저장하고
		{                                                         // Shape와 Board 클래스의 멤버 변수로 저장된 정보를 이용
			Board::gotoXY(i, j);                                   // 여기서 i와 j는 pos_x의 기준점 부터 시작하고 Width와 height만큼 +된 곳이 반복문의 끝
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTable1[ppTileArray[i-Pos_x][j-Pos_y].tileColor]);  // 색 선택 콘솔 // tetr_color = tetr_type 번호
			puts(getTile[ppTileArray[i-Pos_x][j-Pos_y].tileType]); // pptilearray에서 기준 pos_x,y를 반복문 ij를 뺀 값의 타일 타입을 찍어줌
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 색 선택 콘솔
		}
	}
}
bool Board::rotate(Tetromino *pTetr)
{
	Position **Position;
	Position = pTetr->ppgetBrickPositions();
	int chk=0;
	for(int i = 0 ; i < 4 ; i ++)
	{
		if(ppTileArray[ getPos_x() - pTetr->getPos_x() + Position[pTetr->getRot() + 1][i].x ][ getPos_y() - pTetr->getPos_y() + Position[pTetr->getRot() + 1][i].y ].tileType > 0)
		{
			chk++;
		}
	}
	if(chk > 0)
	{return false;}
	else
	{return true;}
}
void Board::BoardKeepTetr(Tetromino *pTetr)
{
	Position **Temp;
	Temp = pTetr->ppgetBrickPositions();
	for(int i = 0 ; i < 4 ; i ++)
	{
		ppTileArray[  pTetr->getPos_x() - getPos_x()  +  Temp[pTetr->getRot()][  i  ].x  ][  pTetr->getPos_y()- getPos_y()   +  Temp[pTetr->getRot()][  i  ].y  ].tileType = BRICK;
		ppTileArray[  pTetr->getPos_x() -getPos_x()   +  Temp[pTetr->getRot()][  i  ].x  ][   pTetr->getPos_y() -getPos_y()   +  Temp[pTetr->getRot()][  i  ].y  ].tileColor= pTetr->getType();
	}
}
int Board::removeFilledLine()
{
	int CHECK;
	int i=0;
	int scoreCounting=0;
	while(i<height)//세로만큼 loop돔
	{
		CHECK=0;
		for(int k =0; k<width;k++)
		{
			if(ppTileArray[k][i].tileType==BRICK)//꽉찬 블럭이면
				CHECK++;
		}
		if(CHECK==10)//꽉찬 블럭이 10개면
		{
			for(int h=i;h>1;h--)
			{
				for(int w =0; w<width;w++)
				{
					ppTileArray[w][h].tileType=ppTileArray[w][h-1].tileType;
					ppTileArray[w][h].tileColor=ppTileArray[w][h-1].tileColor;
				}
			}
			for(int w =0; w<width;w++)
			{
				ppTileArray[w][0].tileType=WALL;
				ppTileArray[w][0].tileColor=0;
			}
			scoreCounting=scoreCounting+25;
			continue;
		}
		i++;
	}
	return scoreCounting;
}
void Board::drawSCORE(int s)
{
	Board::gotoXY(25, 18);
	cout<<setw(4)<<s<<" Total Score";
}