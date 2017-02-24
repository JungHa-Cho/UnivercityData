/*
* File Name: "lab4.cpp"
* Description:
* - This program is
*
* Programmed by Jung-Ha Cho,
* Last updated: Version 2.0, March 24, 2012 (by Jung-Ha Cho).
*
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/03/07) Version Remarks
* J.H Cho 2012/03/24 1.0 Project & Main function is created
* J.H Cho 2012/03/25 1.5 All function is created
* J.H Cho 2012/03/26 2.0 Graph 그리기 확인
* ========================================================
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#define PI 3.141592
using namespace std;

double swh(double amp, double freq, double t, double N);    //함수 선언
void printMarkofGraph(double e, double swh, double Max_amp);//함수 선언
void print(double e, double t , double max_amp);            //함수 선언

int main()                                                  //메인 함수 정의
{
	double Max_amp=0.0, e = 0.0, t=0.0;                     //지역변수 정의
	print(e, t, Max_amp);                                   //함수 호출
}

void print(double e, double t , double max_amp)             //프린트 함수 정의
{
	int i;                                                  //지역변수 정의
	double Max_amp=0.0, amp=0.0, freq=0.0, N=0.0, h=0.0;    //지역변수 정의

	cout<<"input the amplitude : ";
	cin>>amp;                                               //AMP값 입력받음

	cout<<"input the frequency : ";
	cin>>freq;                                              //freq값 입력받음

	cout<<"input the start time : ";
	cin>>t;                                                 //start값 t 입력

	cout<<"input the end time : ";
	cin>>e;                                                 //end값 e 입력

	cout<<"input the count N : ";
	cin>>N;                                                 //카운트 값 N 입력

	for(i=0; i<120; i++)                                    //출력문의 안내 출력
	{
		cout<<"=";                                          //==출력
	}
	cout<<setw(8)<<"x";                                     //출력의 안내
	cout<<setw(17)<<"swh(x) value";                         //출력의 안내
	cout<<setw(50)<<"swh(x) graph";                         //출력의 안내
	cout<<endl;

	for(i=0; i<120; i++)
	{
		cout<<"=";
	}

	for(i=0; i<120; i++)         //amp의 범위 출력
	{
		if(i==28)
			cout<<"-"<<amp;
		else if(i==68)
			cout<<"0";
		else if(i==109)
			cout<<amp;
		else
			cout<<" ";            //해당위치가 아닌경우 빈공간 출력
	}

	for(i=0; i<19; i++)           //출력의 안내
	{
		cout<<" ";
	}
		for(i=0; i<100; i++)
	{
		cout<<"-";
	}   
		
		cout.setf(ios::fixed);  //소수점 2번째 자리까지 출력
		cout.precision(2);

		for (t ; t < e + 0.05 ; t = t+0.05)   //시작시간 t값을 이용하여 
		{                                    //0.05씩 증가시키며 끝나는시간 e까지 반복
			cout<<setw(9)<<t;                //출력의 x 0.00부터 0.05씩 증감
			cout<<setw(9)<<swh(amp,freq,t,N)<<" "; //swh 함수 호출하여 계산값 출력
			h = swh(amp,freq,t,N);           //swh의 계산값을 h에 치환
			printMarkofGraph(e, h, amp);     //그래프를 그리는 함수 printMarkofGraph 호출
		}


}

double swh(double amp, double freq, double t, double N)  //swh 계산 함수
{
	double sum = 0.0;                                    //지역변수 선언
	double result = 0.0;                                 //지역변수 선언

	for(int i = 1; i <= N; i = i + 2)                    //입력받은 N까지 반복
	{                                                    //
		sum = sum + ( 1.0 / i ) * sin( i * PI * freq * t );//sumation 계산
	}
	result = amp * 4.0 / PI * sum;                       //리절트값 계산
	return result;
}

void printMarkofGraph(double e, double h, double Max_amp)//그래프 그리는 함수
{
	double Y;           //지역변수 선언
	int base = 50;     //지역변수 선언
	int scale, i;         //지역변수 선언

	scale = (100 - 20 ) / 2; //scale 변수 계산
	
	Y = ( h / Max_amp ) * scale + base; //실제로 그래프를 그리는 칸 Y 계산

		for(i=0; i<100; i++)  
		{
			if(floor(Y + 0.05)==i)       //Y반올림 후 *찍기
				cout<<"*";
			else if(i==50)              //|찍기
				cout<<"|";
			else
				cout<<" ";              //빈공간출력
		}
		cout<<endl;                    //다음줄
}