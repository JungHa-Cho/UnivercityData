/*
* File Name: "lab_0307.cpp"
* Description:
* - This program is 
*   주어진배열데이터로 제일 큰값,작은값,평균,분산,표준편차 출력
* Programmed by Jung-Ha Cho,
* Last updated: Version 1.0, March 7, 2012 (by Jung-Ha Cho).
*
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/03/07) Version Remarks
* J.H Cho 2012/03/07 1.0 Project & Main function is created
* ========================================================
*/

#include <iostream>
#include <cmath>
using namespace std;

void maxMinAvg(int data[], int data_num);

int main()
{
	int data[]={5,3,8,9,1,2,0,6,4,7};
	int data_num=10;
	maxMinAvg(data,data_num);
}

void maxMinAvg(int data[],int data_num)
{
	int max,min;
	double avg,var,sum=0,sum2=0;
	max=min=data[0];

	for(int i=0; i<10; i++)
	{
		if(max < data[i])
			max = data[i];
		if(min > data[i])
			min = data[i];
		sum = sum + data[i];
	}

	avg = sum / data_num;

	for(int i = 0; i < 10; i++)
	{
		sum2 = sum2 + ((data[i] - avg) * ( data[i] - avg));
	}

	var = sum2 / 10;


	cout << " maximum = " << max << endl;
	cout << " minimum = " << min << endl;
	cout << " average = " << avg << endl;
	cout << " variance = " << var << endl;
    cout << " standard deviation = " << sqrt(var) << endl;
}

