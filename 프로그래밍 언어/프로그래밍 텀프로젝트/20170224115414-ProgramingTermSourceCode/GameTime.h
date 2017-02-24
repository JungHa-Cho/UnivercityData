//#ifndef GAMETIME_H
//#define GAMETIME_H
//
//#include <process.h>//gt
//#include <windows.h>//gt
//#include <stdio.h>//gt
//#include <iostream>
//#include <iomanip>
//
//#include "Shape.h"
//using namespace std;
//
//class Time
//{
//public:
//	static UINT WINAPI gameTime(LPVOID p)
//	{
//		int t=0;
//		
//		while(true)
//		{
//			COORD xy = {25*2, 20};
//			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
//			cout<<"Game Time : "<<setw(4)<<t<<" seconds";
//			Sleep(1000);// 1ÃÊ °£°Ý
//			t++;
//		}
//	}
//
//
//	void printGT()
//	{
//		_beginthreadex(NULL,0, gameTime, (LPVOID)this,0,NULL);
//	}
//};
//
//#endif GAMETIME_H