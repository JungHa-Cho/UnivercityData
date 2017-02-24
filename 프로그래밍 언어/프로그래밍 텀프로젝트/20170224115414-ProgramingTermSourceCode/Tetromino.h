/**  Tetromino.h  **/
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Shape.h"
#include "Board.h"
#include "Position.h"
#include <string>
using namespace std;

#define NUM_ROTS 4       // 로테이션 개수 전역변수
#define NUM_BRICKS 4     // 브릭수 개수
enum TetrType {TETR_I, TETR_O, TETR_L, TETR_J, TETR_S, TETR_Z, TETR_T}; // 이넘 형 TetrType 정의
                                                                        // 이넘으로 정의하면 행열안의 CHAR형 이름을 INT형으로 쓸수있음
class Board;

class Tetromino : public Shape{
public:
	Tetromino();
	string getName();
	Position **ppgetBrickPositions();
	int getType();
	int getRot();
	void initTetrominos(int type, string name);
	void setType(int type);
	void setPos(int x, int y);
	void setRot(int r);
	void setName(string na);
	bool rotate(Board *pB);	
	void drawTETR();
	void removeTETR(/*int x, int y*/);
	bool checkSpace(Board *pB, int xx, int yy);
private:
	unsigned short tetr_color;
	int tetr_rot; 
	int tetr_type;                                                    // 인트형 tetr_type
	string tetr_name;                                                 // 
	Position **ppbrickPosition;                                       // 더블포인터 브릭포지션
	Position brickPosition[NUM_ROTS][NUM_BRICKS];                     // 브릭포지션 이차원배열
};

#endif
