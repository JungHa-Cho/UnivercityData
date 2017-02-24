/*********************************************************************************************************************************************************************
**************************************************** -------    -------     |  /   ---     ----  *********************************************************************
****************************************************    |       |           | /     |      |     *********************************************************************
****************************************************    |       |------     |/      |      ----  *********************************************************************
****************************************************    |       |           |       |         |  *********************************************************************
**************************************************** 	|		-------	    |      ---     ----  *********************************************************************
**********************************************************************************************************************************************************************

*                                                                File Name: "Prog-Tetris"
*                                                                Description:
*													     		 - This program is Tetris
*															     Programmed by Jung-Ha Cho
*																 Last updated: Version 1.0, May 28, 2012 (by Jung-Ha Cho).
* ====================================================================================================================================================================
*													Version Control (Explain updates in detail)
* ====================================================================================================================================================================
*													* Updated By Date (2012/05/28) Version Remarks
*													* J.H Cho 2012/05/28 1.0 프로젝트 및 메인 함수 생성
*													* J.H Cho 2012/05/28 1.1 Shape 클래스 생성 및 정의
*													* J.H Cho 2012/05/28 1.2 모든 클래스, 구조체 생성 및 정의
*													* J.H Cho 2012/05/28 1.3 Board 구현
*													* J.H Cho 2012/05/29 1.4 Preview Board에 Tetromino 구현
*													* J.H Cho 2012/06/19 1.5 함수 및 클래스 파악 및 주석추가
*													* J.H Cho 2012/06/20 1.6 Sleep 함수 이용 Play보드 테스트 및 삭제
*													* J.H Cho 2012/06/21 1.7 TETROMINO Delay 현상 때문에 롤백
*													* J.H Cho 2012/06/21 1.8 While문 하나로 통합 및 CheckBoardSide 조건1 
*													* J.H Cho 2012/06/21 1.9 TETROMINO While Loof 결함문제로 롤백
*													* J.H Cho 2012/06/22 2.0 TETROMINO 원루프로 다시 재구성 CheckSpace 하나로 구성
*													* J.H Cho 2012/06/22 2.1 테트로미노 로테이트 밑 잔버그 잡음
* ===================================================================================================================================================================
*/

#include "Shape.h"
#include "Board.h"
#include "Tile.h"
#include "Tetromino.h"
#include "KeyBoard.h"

#include <iostream>
#include <time.h>
#include <conio.h>
#include <mmsystem.h>
#include <stdio.h>
#include <iomanip>
#include <process.h> // for thread
#include <windows.h> // for thread
#include <stdio.h> // for thread

#pragma comment(lib, "winmm.lib")
using namespace std;
enum {HIDDEN, SHOW};
int t;
UINT WINAPI gameTime(LPVOID p);
void CursorView(char show){
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void gamestart();
void gameover();
void main()
{
	gamestart();

	sndPlaySound(TEXT("bradinsky.wav"),SND_ASYNC|SND_LOOP); //소리 실행

	Sleep(2000);

	CursorView(HIDDEN);

	_beginthreadex(NULL, 0, gameTime, NULL, 0, NULL);
	system("cls");

	/*unsigned char ch;*/

	Board Play(3, 3, 12, 22);                        // Play Board 멤버변수 정의
	Play.gotoXY(3, 2); cout<<"Play Board";           // Play Board 문구
	Play.initBoard();                                // Play Board 초기화
	Play.drawBoard();                                // Play Board 그리기

	Board Preview(23, 3, 10, 7);                     // Preview Board 멤버 변수 정의
	Preview.gotoXY(23, 2); cout<<"Preview Board";    // Preview Board 문구
	Preview.initBoard();                             // Preview Board 초기화
	Preview.drawBoard();                             // Preview Board 그리기

	Board Score(23, 15, 17, 10);                     // Score Board 멤버 변수 정의
	Score.gotoXY(23, 14); cout<<"Score Board";       // Score Board 문구
	Score.initBoard();                               // Score Board 초기화
	Score.drawBoard();                               // Score Board 

	unsigned char ch;                                // 지역변수 정의 및 초기화
	int count = 0, RAN = 0, score = 0;
	int Temp = 0, TimeTemp = 0;
	int RAN_Fir = 0, RAN_sec = 0;
	int xx = 0 , yy = 0;
	int sleepdevide = 20;
	srand(time(0));

	Tetromino *PlayTetr;                             // 지역변수
	Tetromino *PreviewTetr;

	srand(time(0));

	while(1)
	{
		Score.drawSCORE(score);
		RAN = rand()%7;
		COORD xy = {25*2, 20};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
		cout<<"Game Time : "<<setw(4)<<t<<" seconds";

		if(RAN_Fir == 0)
		{
			PlayTetr = Play.addTetr(5);
			PlayTetr->drawTETR();
			PreviewTetr = Preview.addTetr(RAN);
			PreviewTetr->drawTETR();
			RAN_sec = RAN;
			RAN_Fir =1;
		}
		////////////////////////////////////////////////////////////////////////////
		PlayTetr->drawTETR();               //그리기
		////////////////////////////////////////////////////////////////////////////
		Sleep(1000/sleepdevide);
		count++;

		if(count==20)
		{ 
			if(PlayTetr->checkSpace(&Play, xx, +1))
			{
				PlayTetr->removeTETR();
				PlayTetr->setPos_y(PlayTetr->getPos_y()+1);
			}else{
				Play.BoardKeepTetr(PlayTetr);
				Play.drawBoard();
				PreviewTetr->removeTETR();
				PreviewTetr = Preview.addTetr(RAN);
				PreviewTetr->drawTETR();
				PlayTetr = Play.addTetr(RAN_sec);
				//PlayTetr->drawTETR();
				RAN_sec = RAN;
			}
			count = 0;
		} 
		if(kbhit())
		{
			ch = getch();
			if (ch == 0xE0 || ch == 0)    // 방향키 입력이거나 입력이 0일때 진입
			{  
				ch = getch();
				switch(ch)
				{
				case LEFT:
					if(PlayTetr->checkSpace(&Play, -1, yy))
					{
						PlayTetr->removeTETR();
						PlayTetr->setPos_x(PlayTetr->getPos_x()-1);
						PlayTetr->drawTETR();
					}
					break;
				case RIGHT:
					if(PlayTetr->checkSpace(&Play, +1, yy))
					{
						PlayTetr->removeTETR();
						PlayTetr->setPos_x(PlayTetr->getPos_x()+1);
						PlayTetr->drawTETR();
					}
					break;
				case UP:
					if(PlayTetr->getType() == 0 && PlayTetr->getPos_x() == 13 
						|| PlayTetr->getType() == 2 && PlayTetr->getPos_x() == 4 
						|| PlayTetr->getType() == 3 && PlayTetr->getPos_x() == 13)
					{/*EMPTY*/}else{
						if(PlayTetr->rotate(&Play))
						{
							PlayTetr->removeTETR();
							if(PlayTetr->getRot() == 3)
							{
								PlayTetr->setRot(0);
							}else{
								PlayTetr->setRot(PlayTetr->getRot()+1);
							}
						}
					}
					PlayTetr->removeTETR();
					PlayTetr->drawTETR();
					break;
				case DOWN:
					if(PlayTetr->checkSpace(&Play, xx, +1))
					{
						PlayTetr->removeTETR();
						PlayTetr->setPos_y(PlayTetr->getPos_y()+1);
						PlayTetr->drawTETR();
					}
					break;
				}
			}
			else 
			{ 
				switch(ch)
				{
				case SPACE:
					while(1)
					{
						PlayTetr->removeTETR();
						PlayTetr->setPos_y(PlayTetr->getPos_y()+1);
						//PlayTetr->drawTETR();
						if(!PlayTetr->checkSpace(&Play, xx, 1))
						{
							Play.BoardKeepTetr(PlayTetr);
							score = score + Play.removeFilledLine();
							Play.drawBoard();
							break;}
					}
					break;
				case 'p':
					while(1)
					{
						if(Temp == 0)
						{
							TimeTemp = t;
							Temp = 1;
						}
						if(getch() == 0x70)
						{
							t = TimeTemp;
							break;
						}
					}
					break;
				case 'q':
				case 'Q':
					gameover();
					return;
				case ESC:
					gameover();
					return;
				} // end switch-case
			} // end if
		} // end if
		Play.gotoXY(2 , 26);
		cout<<"Name : "<<setw(4)<<PlayTetr->getName();
		Play.gotoXY(2 , 27);
		cout<<"PlayTetr : "<<setw(4)<<PlayTetr->getPos_x()<<", "<<PlayTetr->getPos_y();
		Play.gotoXY(2 , 28);
		cout<<"PlayRotate : "<<setw(4)<<PlayTetr->getRot();
		if(t == 60){sleepdevide = 150;}
		if(t == 120){sleepdevide = 300;}
		if(t == 180){sleepdevide = 450;}
		if(PlayTetr->getPos_y() == 5){gameover();}   
	} // end while
} // end main
UINT WINAPI gameTime(LPVOID p)
{
	while(true)
	{
		Sleep(1000);// 1초 간격
		t++;
	}
}
void gamestart()
{
	Sleep(50);
	cout<<"┌─────────────────────────────────────────┐\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│            @@@@@@@@@@@@@@      @@@@           @@@@    @@@@          @@@@         │\n";
	Sleep(50);
	cout<<"│           @   @@@@@@@@   @     @  @           @  @    @   @         @  @         │\n";
	Sleep(50);
	cout<<"│           @  @        @  @     @  @           @  @    @    @        @  @         │\n";
	Sleep(50);
	cout<<"│           @  @        @  @     @  @           @  @    @  @  @       @  @         │\n";
	Sleep(50);
	cout<<"│           @  @        @  @     @  @           @  @    @  @@  @      @  @         │\n";
	Sleep(50);
	cout<<"│           @  @        @  @     @  @           @  @    @  @ @  @     @  @         │\n";
	Sleep(50);
	cout<<"│           @   @@@@@@@@   @     @  @           @  @    @  @  @  @    @  @         │\n";
	Sleep(50);
	cout<<"│           @  @@@@   @@@@@      @  @           @  @    @  @   @  @   @  @         │\n";
	Sleep(50);
	cout<<"│           @  @    @  @         @  @           @  @    @  @    @  @  @  @         │\n";
	Sleep(50);
	cout<<"│           @  @     @  @        @  @           @  @    @  @     @  @ @  @         │\n";
	Sleep(50);
	cout<<"│           @  @       @  @      @  @           @  @    @  @      @  @@  @         │\n";
	Sleep(50);
	cout<<"│           @  @        @  @     @  @           @  @    @  @       @  @  @         │\n";
	Sleep(50);
	cout<<"│           @  @        @  @      @  @@@@@@@@@@@  @     @  @        @    @         │\n";
	Sleep(50);
	cout<<"│           @  @        @  @       @             @      @  @         @   @         │\n";
	Sleep(50);   
	cout<<"│           @@@@        @@@@        @@@@@@@@@@@@@       @@@@          @@@@         │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                Please press Any key !                            │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"│                                                                                  │\n";
	Sleep(50);
	cout<<"└─────────────────────────────────────────┘\n";

	getch();

	system("cls");
}
void gameover()
{

	Sleep(1000);
	system("cls");
	for(int i=0; i<3; i++)
	{
		cout<<"                                                                                      \n";
		Sleep(50);
		cout<<"                                                                                      \n";
		Sleep(50);
		cout<<"          @@@@@@@                                                                     \n";
		Sleep(50);
		cout<<"        @@@     @@@          @@@@          @@@             @@@   @@@@@@@@@@@@@        \n";
		Sleep(50);
		cout<<"      @@@         @@@       @@  @@         @@@             @@@   @@                   \n";
		Sleep(50);
		cout<<"     @@@           @@@     @@    @@        @@@@           @@@@   @@                   \n";
		Sleep(50);
		cout<<"     @@@           @@@    @@      @@       @@ @@         @@ @@   @@                   \n";
		Sleep(50);
		cout<<"     @@@           @@@   @@        @@      @@  @@       @@  @@   @@@@@@@@@@@@@        \n";
		Sleep(50);
		cout<<"     @@@                @@@@@@@@@@@@@@     @@   @@     @@   @@   @@                   \n";
		Sleep(50);
		cout<<"      @@@    @@@@@@@@@ @@            @@    @@    @@   @@    @@   @@                   \n";
		Sleep(50);
		cout<<"        @@@  @@@ @@@  @@              @@   @@     @@ @@     @@   @@                   \n";
		Sleep(50);
		cout<<"         @@@@@@  @@@ @@                @@  @@      @@@      @@   @@@@@@@@@@@@@        \n";
		Sleep(50);
		cout<<"                                                                                      \n";
		Sleep(50);
		cout<<"                                                                                      \n";
		Sleep(50);
		cout<<"             @@@@     @@@@              @@@@  @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@        \n";
		Sleep(50);
		cout<<"          @@      @@   @@@              @@@   @@                  @@          @@      \n";
		Sleep(50);
		cout<<"        @@          @@  @@              @@    @@                  @@           @@     \n";
		Sleep(50);
		cout<<"       @@@          @@@  @@            @@     @@                  @@           @@     \n";
		Sleep(50);
		cout<<"      @@@            @@@  @@          @@      @@                  @@          @@      \n";
		Sleep(50);
		cout<<"      @@@            @@@   @@        @@       @@@@@@@@@@@@@@@@@   @@@@@@@@@@@@        \n";
		Sleep(50);
		cout<<"       @@@          @@@     @@      @@        @@                  @@        @@        \n";
		Sleep(50);
		cout<<"        @@          @@       @@    @@         @@                  @@         @@       \n";
		Sleep(50);
		cout<<"          @@      @@          @@  @@          @@                  @@          @@      \n";
		Sleep(50);
		cout<<"             @@@@              @@@@           @@@@@@@@@@@@@@@@@   @@           @@     \n";
		Sleep(50);
		cout<<"                                                                                      \n";
		Sleep(50);
		cout<<"                                                                                      \n";
		Sleep(50);
		cout<<"                                                                                      \n";
		Sleep(50);
		system("cls");
	}

	Sleep(50);
	cout<<"                                                                                      \n";
	cout<<"                                                                                      \n";
	cout<<"                                                                                      \n";
	cout<<"      @@@          @@@         @@@@          @@@@@@@@@@@@@       @@@@@@@@@@@@@@@      \n";
	cout<<"      @@ @        @ @@        @@  @@         @@           @@     @@                   \n";
	cout<<"      @@  @      @  @@       @@    @@        @@            @@    @@                   \n";
	cout<<"      @@   @    @   @@      @@      @@       @@             @@   @@                   \n";
	cout<<"      @@    @  @    @@     @@        @@      @@             @@   @@@@@@@@@@@@@@@      \n";
	cout<<"      @@     @@     @@    @@@@@@@@@@@@@@     @@             @@   @@                   \n";
	cout<<"      @@     @@     @@   @@            @@    @@            @@    @@                   \n";
	cout<<"      @@     @@     @@  @@              @@   @@           @@     @@                   \n";
	cout<<"      @@     @@     @@ @@                @@  @@@@@@@@@@@@@       @@@@@@@@@@@@@@@      \n";
	cout<<"                                                                                      \n";
	cout<<"                                                                                      \n";
	cout<<"      @@@@@@@@@@@@@@@    @@             @@   @@@@@ @@@@@ @   @    @@@ @@@@@ @   @     \n";
	cout<<"      @@            @@    @@           @@      @     @   @@@@@   @      @   @@@@@     \n";
	cout<<"      @@             @@    @@         @@     @ @   @ @   @   @   @    @ @   @   @     \n";
	cout<<"      @@            @@      @@       @@       @@    @@   @   @    @@@  @@   @   @     \n";
	cout<<"      @@@@@@@@@@@@@@         @@@   @@@                                                \n";
	cout<<"      @@            @@         @@@@@                                                  \n";
	cout<<"      @@             @@         @@@          @   @ @@@@  @   @                        \n";
	cout<<"      @@             @@          @            @ @  @  @@  @ @                         \n";
	cout<<"      @@            @@           @             @   @  @@   @                          \n";
	cout<<"      @@@@@@@@@@@@@@@            @             @   @@@@    @                          \n";
	cout<<"                                                                                      \n";
	cout<<"                                                                                      \n";
	cout<<"                                                                                      \n";
	exit(0);
}