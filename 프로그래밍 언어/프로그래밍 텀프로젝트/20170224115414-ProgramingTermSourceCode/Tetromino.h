/**  Tetromino.h  **/
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Shape.h"
#include "Board.h"
#include "Position.h"
#include <string>
using namespace std;

#define NUM_ROTS 4       // �����̼� ���� ��������
#define NUM_BRICKS 4     // �긯�� ����
enum TetrType {TETR_I, TETR_O, TETR_L, TETR_J, TETR_S, TETR_Z, TETR_T}; // �̳� �� TetrType ����
                                                                        // �̳����� �����ϸ� �࿭���� CHAR�� �̸��� INT������ ��������
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
	int tetr_type;                                                    // ��Ʈ�� tetr_type
	string tetr_name;                                                 // 
	Position **ppbrickPosition;                                       // ���������� �긯������
	Position brickPosition[NUM_ROTS][NUM_BRICKS];                     // �긯������ �������迭
};

#endif
