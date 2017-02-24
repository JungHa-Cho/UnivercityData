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
* J.H Cho 2012/03/26 2.0 Graph �׸��� Ȯ��
* ========================================================
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#define PI 3.141592
using namespace std;

double swh(double amp, double freq, double t, double N);    //�Լ� ����
void printMarkofGraph(double e, double swh, double Max_amp);//�Լ� ����
void print(double e, double t , double max_amp);            //�Լ� ����

int main()                                                  //���� �Լ� ����
{
	double Max_amp=0.0, e = 0.0, t=0.0;                     //�������� ����
	print(e, t, Max_amp);                                   //�Լ� ȣ��
}

void print(double e, double t , double max_amp)             //����Ʈ �Լ� ����
{
	int i;                                                  //�������� ����
	double Max_amp=0.0, amp=0.0, freq=0.0, N=0.0, h=0.0;    //�������� ����

	cout<<"input the amplitude : ";
	cin>>amp;                                               //AMP�� �Է¹���

	cout<<"input the frequency : ";
	cin>>freq;                                              //freq�� �Է¹���

	cout<<"input the start time : ";
	cin>>t;                                                 //start�� t �Է�

	cout<<"input the end time : ";
	cin>>e;                                                 //end�� e �Է�

	cout<<"input the count N : ";
	cin>>N;                                                 //ī��Ʈ �� N �Է�

	for(i=0; i<120; i++)                                    //��¹��� �ȳ� ���
	{
		cout<<"=";                                          //==���
	}
	cout<<setw(8)<<"x";                                     //����� �ȳ�
	cout<<setw(17)<<"swh(x) value";                         //����� �ȳ�
	cout<<setw(50)<<"swh(x) graph";                         //����� �ȳ�
	cout<<endl;

	for(i=0; i<120; i++)
	{
		cout<<"=";
	}

	for(i=0; i<120; i++)         //amp�� ���� ���
	{
		if(i==28)
			cout<<"-"<<amp;
		else if(i==68)
			cout<<"0";
		else if(i==109)
			cout<<amp;
		else
			cout<<" ";            //�ش���ġ�� �ƴѰ�� ����� ���
	}

	for(i=0; i<19; i++)           //����� �ȳ�
	{
		cout<<" ";
	}
		for(i=0; i<100; i++)
	{
		cout<<"-";
	}   
		
		cout.setf(ios::fixed);  //�Ҽ��� 2��° �ڸ����� ���
		cout.precision(2);

		for (t ; t < e + 0.05 ; t = t+0.05)   //���۽ð� t���� �̿��Ͽ� 
		{                                    //0.05�� ������Ű�� �����½ð� e���� �ݺ�
			cout<<setw(9)<<t;                //����� x 0.00���� 0.05�� ����
			cout<<setw(9)<<swh(amp,freq,t,N)<<" "; //swh �Լ� ȣ���Ͽ� ��갪 ���
			h = swh(amp,freq,t,N);           //swh�� ��갪�� h�� ġȯ
			printMarkofGraph(e, h, amp);     //�׷����� �׸��� �Լ� printMarkofGraph ȣ��
		}


}

double swh(double amp, double freq, double t, double N)  //swh ��� �Լ�
{
	double sum = 0.0;                                    //�������� ����
	double result = 0.0;                                 //�������� ����

	for(int i = 1; i <= N; i = i + 2)                    //�Է¹��� N���� �ݺ�
	{                                                    //
		sum = sum + ( 1.0 / i ) * sin( i * PI * freq * t );//sumation ���
	}
	result = amp * 4.0 / PI * sum;                       //����Ʈ�� ���
	return result;
}

void printMarkofGraph(double e, double h, double Max_amp)//�׷��� �׸��� �Լ�
{
	double Y;           //�������� ����
	int base = 50;     //�������� ����
	int scale, i;         //�������� ����

	scale = (100 - 20 ) / 2; //scale ���� ���
	
	Y = ( h / Max_amp ) * scale + base; //������ �׷����� �׸��� ĭ Y ���

		for(i=0; i<100; i++)  
		{
			if(floor(Y + 0.05)==i)       //Y�ݿø� �� *���
				cout<<"*";
			else if(i==50)              //|���
				cout<<"|";
			else
				cout<<" ";              //��������
		}
		cout<<endl;                    //������
}