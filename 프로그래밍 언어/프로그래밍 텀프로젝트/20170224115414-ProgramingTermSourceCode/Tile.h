/*      Tile 선언          */
#ifndef TILE_H
#define TILE_H

#include <iostream>
using namespace std;
enum TileType{EMPTY, BRICK, WALL};	//{"·","■","□"}

struct Tile{
	int tileType;    //타입정보 저장., 타입정보종류는 3개
	int tileColor;   //타일 컬러 저장
};

#endif