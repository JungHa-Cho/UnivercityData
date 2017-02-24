/*
* File Name: "piano.cpp"
* Description:
* - This program is �����ǾƳ�
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


void keysound(char key, int duration);      //�Լ� ����
void playbyprogram(char key, int duration); //�Լ� ����
void playbykey(char key, int duration);     //�Լ� ����
void print(char key, int duration);         //�Լ� ����

struct music                                //����ü ����
{
	char key;                               //����ü ����
	int duration;                           //����ü ����
};


int main()                                  //���� ����
{
	char key = 0;                           //���� ����
	int duration = 300;                     //���� ����

	print(key, duration);                   //����Ʈ �Լ� ȣ��

	char num;                               //getchar�� ���� num ���� ����

	switch( num = getchar())                //1,2,3�� �������� ���� ����ġ��
	{
	case '1' :
		playbykey(key, duration);           //1�� ������ playbykey �Լ� ȣ�� 
		break;
	case '2' : 
		playbyprogram(key, duration);       //2�� ������ playbyprogram �Լ� ȣ��
		break;
	case '3' :
		cout<<"�����մϴ�"<<endl;           //3�� ������ ����
		return 0;
		break;
	default :
		cout<<"�߸� �Է��߽��ϴ�."<<endl;

	}	
}

	
void print(char key, int duration)          //print �Լ� ����
{
	cout<<"1~3 Ű�� �����ÿ�."<<endl;
	cout<<"1 : PlayByKey(���� Ű�� ���� ����)"<<endl;
	cout<<"2 : PlayByProgram(����� �뷡 ����)"<<endl;
	cout<<"3 : ����"<<endl;
}		

void playbykey(char key, int duration)      //playbykey �Լ� ����
{
	cout<<"Q ~ P : 3 octave"<<endl;         //��Ÿ�� ���� �� ���
	cout<<"A ~ L : 2 octave"<<endl;
	cout<<"Z ~ M : 1 octave"<<endl;
	cout<<"/ Ű�� ������ ���� �մϴ�"<<endl;

	fflush(stdin);

	while ((key = getchar()) !='/')         //getchar�� �Է¹ޱ� ���� ���ѷ���
	{                                       //Ű�� ���Ѵ�� �Է¹����� ������
		keysound(key, duration);            // "/" Ű�� ������ ���� ����
		fflush(stdin);
	}
	cout<<"����"<<endl;

}

void playbyprogram(char key, int duration) //playbyprogram �Լ� ����
{
	cout<<"���ٶ��� ����� ���ƶ� ���ƶ� ���̳��� ���ƶ�  �츮�����"<<endl; //����� �뷡 ����

		struct music littlestar[25]={                                            //����ü ����
		{'3',duration},{'2',duration},{'1',duration},{'2',duration},         
		{'3',duration},{'3',duration},{'3',duration},
		{'2',duration},{'2',duration},{'2',duration},
		{'3',duration},{'3',duration},{'3',duration},
		{'3',duration},{'2',duration},{'1',duration},{'2',duration},     
		{'3',duration},{'3',duration},{'3',duration},     
		{'2',duration},{'2',duration},{'3',duration},{'2',duration},{'1',duration}};
		for(int i=0; i<25; i++)                                              //����ü�� ����� �뷡��
		{                                                                    //�����ϱ����� for���� 25��
			keysound(littlestar[i].key, littlestar[i].duration);             //�Ҹ��� ���� keysound�Լ� ȣ��
		}


}



void keysound(char key, int duration)                            //�Ҹ��� ���� �Լ� keysound
{
	double freq=0.0;                                             //���� ����
	double Z = 32.70, X = 36.71, C = 41.20;                      //���� ����
	double V = 43.65, B = 49.00, N = 55.00;                      //���� ����
	double M = 61.74;                                            //���� ����

	switch(key)                                                 //Z~M������ �Է¹����� 
	{                                                           //freq�� ���� �����ֱ� ����
		case 'Z':                                               //switch ��
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
			cout<<"�߸��Է��߽��ϴ� �ٽ� �Է��ϼ���."<<endl;			
//	}
//		switch(key)       //A~J������ �Է¹����� freq�� ���� �����ִ� switch��
//	{
		case 'A':
		case 'a':
			freq = Z * 2; //���������� ������ Z * 2�� ���� 2��Ÿ�� ���̾ * 2
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
//			switch(key)   //Q~U ������ Ű�� �Է¹����� Freq�� ��ȯ�� ���� ����ġ��
//	{
		case 'Q':
		case 'q':
			freq = Z * 3; //3��Ÿ�� Q~U������ 1��Ÿ�� ���� * 3�� ��
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
//	switch(key)   //1~7 ������ Ű�� �Է¹����� Freq�� ��ȯ�� ���� ����ġ��
//	{
		case '1':
			freq = Z * 4; //4��Ÿ�� 1~7������ 1��Ÿ�� ���� * 4�� ��
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

	Beep(freq, duration);        //���� ���� �� ���ڵ�� �������� ���� �Լ�ȣ�⹮
}