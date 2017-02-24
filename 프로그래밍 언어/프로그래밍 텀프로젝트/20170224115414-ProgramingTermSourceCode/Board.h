/*********************   ���� Ŭ����  **************************/
#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include "Tile.h"
#include "Tetromino.h"
#include "Position.h"
using namespace std;

class Tetromino;

class Board : public Shape{
public:
	Board();                                          // ������
	Board(int x, int y, int wid, int hei);            // x,y �ʺ� ������ ������ �ƱԸ�Ʈ�� �޴� ������
	~Board(){delete ppTileArray;}                     // �Ҹ���      �����Ҵ��� ���� ���� 
	void initBoard();                                 // ���� �ʱ�ȭ
	void drawBoard();                                 // ��ο� ����
	Tetromino *addTetr(int tetr_type);                // ��Ʈ�ι̳� Ŭ������ 
	bool rotate(Tetromino *pTetr);
	void BoardKeepTetr(Tetromino *pTetr);
	void drawSCORE(int s);
	int removeFilledLine(); 
	Tile **getppTileArray(){return ppTileArray;}
private:
	int width;                                        // �ʺ�
	int height;                                       // ����
	Tile **ppTileArray;                               // 2�����迭�� ����Ű�� ���� ������
};

#endif