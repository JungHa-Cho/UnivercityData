/*      Tile ����          */
#ifndef TILE_H
#define TILE_H

#include <iostream>
using namespace std;
enum TileType{EMPTY, BRICK, WALL};	//{"��","��","��"}

struct Tile{
	int tileType;    //Ÿ������ ����., Ÿ������������ 3��
	int tileColor;   //Ÿ�� �÷� ����
};

#endif