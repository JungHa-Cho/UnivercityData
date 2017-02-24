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

char getTile[][5] = {"��","��","��"};  // Ÿ�� ��� ����,,, ��������
string TetrName[] = {"TETR_I", "TETR_O", "TETR_L", "TETR_J", "TETR_S", "TETR_Z", "TETR_T"};
unsigned short colorTable1[]={0xffff, 0x0003, 0x000e, 0x000d, 0x0009, 0x000a, 0x000c, 0x0005}; 

Board::Board()                        // ���� ����Ʈ ������
{
	Pos_x = 0;
	Pos_y = 0;
	width = 0;
	height = 0;
}
Board::Board(int x, int y, int wid, int hei) // ������ ������ �ƱԸ�Ʈ�� �޴� ������
{
	Pos_x = x;
	Pos_y = y;
	width = wid;
	height = hei;

	ppTileArray = new Tile *[width];                              // 2���� �迭 �ʱ�ȭ
	for(int i = 0 ; i < width ; i++)     
	{
		ppTileArray[i] = new Tile [height];                    
	}
}
Tetromino *Board::addTetr(int tetr_type) /**  addTetr ���⿡�� ��� ��Ʈ�ι̳� ���� ������ �ʱ�ȭ�Ѵ�.  **///  
{   
	int Bx = Pos_x + (width / 2);      // x preview ���� Preview �������� width / 2 �� �߽� ���         // ���忡 ��Ʈ�ι̳� �׸� ������ ����
	int By = Pos_y + 3;                // y preview ���� ���������� ������ 3ĭ                           // 

	Tetromino *TETRO;                  // Tetromino New ����                                           //  ��Ʈ�ι̳��� ������ TETRO ����
	TETRO = new Tetromino;             // �����Ҵ�                                                     //  �����Ҵ�
	TETRO->setPos_x(Bx);               // TETRO�� ���� ����                                            //   
	TETRO->setPos_y(By);               // TETRO�� ���� ����  
	TETRO->initTetrominos(tetr_type, TetrName[tetr_type]); // ��Ʈ�ι̳� �ʱ�ȭ, ���� = tetr_type;      // ��Ʈ�ι̳� �ʱ�ȭ
	TETRO->setName(TetrName[tetr_type]);                                                                             //
	return TETRO;                                                                                     //
}
void Board::initBoard()
{
	for(int i = 0 ; i < width ; i ++)                             // �ʺ� ��ŭ 
	{ 
		for( int j = 0 ; j < height ; j ++)                       // ���� ��ŭ
		{
			if(i == 0 || j == 0 || i == width-1 || j == height-1) // �׷��� �ϴ� ������ ����
			{										                                    
				ppTileArray[i][j].tileType = WALL;                // 2���� �迭�� ����Ű�� ������ ppTileArray
				ppTileArray[i][j].tileColor = 0;
			}                                                     // ����ü ������ Ÿ��Ÿ���� ���� 
			if(i != 0 && j != 0 && i != width-1 && j != height-1) // �׷��� �ϴ� ������ ����
			{                                                                           
				ppTileArray[i][j].tileType = EMPTY;               // tile�� ����ü�� TileType�� TileColor�� ����
				ppTileArray[i][j].tileColor= 0;
			}
		}
	}
}
void Board::drawBoard()                                           // ����� ���带 �׸��� �Լ�
{
	for(int i = Pos_x ; i < width + Pos_x ; i ++)                 // ���⼭ i�� j�� main������ ���� Ŭ������ �����Ҷ� ���� ������ �������� �Ѵ�.
	{
		for(int j = Pos_y ; j < height + Pos_y ; j ++)            // ��, ������ ������ �ƱԸ�Ʈ�� �޴� �����ڷ� ������ �������� �ʺ� ���̸� �����ϰ�
		{                                                         // Shape�� Board Ŭ������ ��� ������ ����� ������ �̿�
			Board::gotoXY(i, j);                                   // ���⼭ i�� j�� pos_x�� ������ ���� �����ϰ� Width�� height��ŭ +�� ���� �ݺ����� ��
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorTable1[ppTileArray[i-Pos_x][j-Pos_y].tileColor]);  // �� ���� �ܼ� // tetr_color = tetr_type ��ȣ
			puts(getTile[ppTileArray[i-Pos_x][j-Pos_y].tileType]); // pptilearray���� ���� pos_x,y�� �ݺ��� ij�� �� ���� Ÿ�� Ÿ���� �����
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // �� ���� �ܼ�
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
	while(i<height)//���θ�ŭ loop��
	{
		CHECK=0;
		for(int k =0; k<width;k++)
		{
			if(ppTileArray[k][i].tileType==BRICK)//���� ���̸�
				CHECK++;
		}
		if(CHECK==10)//���� ���� 10����
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