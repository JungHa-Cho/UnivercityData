/*********************   보드 클래스  **************************/
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
	Board();                                          // 생성자
	Board(int x, int y, int wid, int hei);            // x,y 너비 높이의 정보를 아규먼트로 받는 생성자
	~Board(){delete ppTileArray;}                     // 소멸자      동적할당한 정보 삭제 
	void initBoard();                                 // 보드 초기화
	void drawBoard();                                 // 드로우 보드
	Tetromino *addTetr(int tetr_type);                // 테트로미노 클래스형 
	bool rotate(Tetromino *pTetr);
	void BoardKeepTetr(Tetromino *pTetr);
	void drawSCORE(int s);
	int removeFilledLine(); 
	Tile **getppTileArray(){return ppTileArray;}
private:
	int width;                                        // 너비
	int height;                                       // 높이
	Tile **ppTileArray;                               // 2차원배열을 가리키기 위한 포인터
};

#endif