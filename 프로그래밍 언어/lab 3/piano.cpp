/*
* File Name: "piano.cpp"
* Description:
* - This program is 전자피아노
* Programmed by Jung-Ha Cho,
* Last updated: Version 2.0, March 21, 2012 (by Jung-Ha Cho).
*
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/03/07) Version Remarks
* J.H Cho 2012/03/18 1.0 Project & Main function is created
* J.H Cho 2012/03/19 1.2 Print & structrue function is created
* J.H Cho 2012/03/19 1.3 playbykey,playbyprogram,keysound function is operating check
* J.H Cho 2012/03/20 1.5 Piano.cpp is Beep Sound Success
* J.H Cho 2012/03/21 1.8 Each Function "Cout" is created
* J.H Cho 2012/03/21 2.0 Com Piano is complete
* ========================================================
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;


void keysound(char key, int duration);      //함수 선언
void playbyprogram(char key, int duration); //함수 선언
void playbykey(char key, int duration);     //함수 선언
void print(char key, int duration);         //함수 선언

struct music                                //구조체 선언
{
	char key;                               //구조체 인자
	int duration;                           //구조체 인자
};


int main()                                  //메인 문장
{
	char key = 0;                           //변수 정의
	int duration = 300;                     //변수 정의

	print(key, duration);                   //프린트 함수 호출

	char num;                               //getchar를 위한 num 변수 정의

	switch( num = getchar())                //1,2,3번 선택지를 위한 스위치문
	{
	case '1' :
		playbykey(key, duration);           //1을 누르면 playbykey 함수 호출 
		break;
	case '2' : 
		playbyprogram(key, duration);       //2을 누르면 playbyprogram 함수 호출
		break;
	case '3' :
		cout<<"종료합니다"<<endl;           //3을 누르면 종료
		return 0;
		break;
	default :
		cout<<"잘못 입력했습니다."<<endl;

	}	
}

	
void print(char key, int duration)          //print 함수 내용
{
	cout<<"1~3 키를 누르시오."<<endl;
	cout<<"1 : PlayByKey(직접 키를 눌러 연주)"<<endl;
	cout<<"2 : PlayByProgram(저장된 노래 연주)"<<endl;
	cout<<"3 : 종료"<<endl;
}		

void playbykey(char key, int duration)      //playbykey 함수 내용
{
	cout<<"Q ~ P : 3 octave"<<endl;         //옥타브 설명 문 출력
	cout<<"A ~ L : 2 octave"<<endl;
	cout<<"Z ~ M : 1 octave"<<endl;
	cout<<"/ 키를 누르면 종료 합니다"<<endl;

	fflush(stdin);

	while ((key = getchar()) !='/')         //getchar를 입력받기 위한 무한루프
	{                                       //키를 무한대로 입력받을수 있으나
		keysound(key, duration);            // "/" 키를 누르면 루프 종료
		fflush(stdin);
	}
	cout<<"종료"<<endl;

}

void playbyprogram(char key, int duration) //playbyprogram 함수 내용
{
	cout<<"떳다떳다 비행기 날아라 날아라 높이높이 날아라  우리비행기"<<endl; //내장된 노래 설명

		struct music littlestar[25]={                                            //구조체 정의
		{'3',duration},{'2',duration},{'1',duration},{'2',duration},         
		{'3',duration},{'3',duration},{'3',duration},
		{'2',duration},{'2',duration},{'2',duration},
		{'3',duration},{'3',duration},{'3',duration},
		{'3',duration},{'2',duration},{'1',duration},{'2',duration},     
		{'3',duration},{'3',duration},{'3',duration},     
		{'2',duration},{'2',duration},{'3',duration},{'2',duration},{'1',duration}};
		for(int i=0; i<25; i++)                                              //구조체에 내장된 노래를
		{                                                                    //전달하기위한 for루프 25번
			keysound(littlestar[i].key, littlestar[i].duration);             //소리를 내는 keysound함수 호출
		}


}



void keysound(char key, int duration)                            //소리를 내는 함수 keysound
{
	double freq=0.0;                                             //변수 정의
	double Z = 32.70, X = 36.71, C = 41.20;                      //변수 정의
	double V = 43.65, B = 49.00, N = 55.00;                      //변수 정의
	double M = 61.74;                                            //변수 정의

	switch(key)                                                 //Z~M까지를 입력받을때 
	{                                                           //freq시 값을 돌려주기 위한
		case 'Z':                                               //switch 문
		case 'z':
			freq = Z;
			break;
		case 'X':
		case 'x':
			freq = X;
			break;

		case 'C':
		case 'c':
			freq = C;
			break;

		case 'V':
		case 'v':
			freq = V;
			break;

		case 'B':
		case 'b':
			freq = B;
			break;

		case 'N':
		case 'n':
			freq = N;
			break;

		case 'M':
		case 'm':
			freq = M;
			break;
		default :
			cout<<"잘못입력했습니다 다시 입력하세요."<<endl;			
//	}
//		switch(key)       //A~J까지를 입력받을때 freq시 값을 돌려주는 switch문
//	{
		case 'A':
		case 'a':
			freq = Z * 2; //지역변수로 정의한 Z * 2의 값이 2옥타브 값이어서 * 2
			break;

		case 'S':
		case 's':
			freq = X * 2;
			break;

		case 'D':
		case 'd':
			freq = C * 2;
			break;

		case 'F':
		case 'f':
			freq = V * 2;
			break;

		case 'G':
		case 'g':
			freq = B * 2;
			break;

		case 'H':
		case 'h':
			freq = N * 2;
			break;

		case 'J':
		case 'j':
			freq = M * 2;
			break;
//	}
//			switch(key)   //Q~U 까지의 키를 입력받을때 Freq값 반환을 위한 스위치문
//	{
		case 'Q':
		case 'q':
			freq = Z * 3; //3옥타브 Q~U까지는 1옥타브 값에 * 3한 값
			break;

		case 'W':
		case 'w':
			freq = X * 3;
			break;

		case 'E':
		case 'e':
			freq = C * 3;
			break;

		case 'R':
		case 'r':
			freq = V  * 3;
			break;

		case 'T':
		case 't':
			freq = B * 3;
			break;

		case 'Y':
		case 'y':
			freq = N * 3;
			break;

		case 'U':
		case 'u':
			freq = M * 3;
			break;
//	}
//	switch(key)   //1~7 까지의 키를 입력받을때 Freq값 반환을 위한 스위치문
//	{
		case '1':
			freq = Z * 4; //4옥타브 1~7까지는 1옥타브 값에 * 4한 값
			break;

		case '2':
			freq = X * 4;
			break;

		case '3':
			freq = C * 4;
			break;

		case '4':
			freq = V  * 4;
			break;

		case '5':
			freq = B * 4;
			break;

		case '6':
			freq = N * 4;
			break;

		case '7':
			freq = M * 4;
			break;
	}

	Beep(freq, duration);        //전달 받은 각 인자들로 비프음을 내는 함수호출문
}