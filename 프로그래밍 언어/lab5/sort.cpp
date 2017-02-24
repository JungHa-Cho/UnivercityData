/* 
*레이아웃 넓이 160 높이 60
*
* File Name: "sort.cpp"
* Description:
* - This program is
* Programmed by Jung-Ha Cho,
* Last updated: Version 2.0, March 29, 2012 (by Jung-Ha Cho).
*
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/03/07) Version Remarks
* J.H Cho 2012/03/29 1.0 Project & Main function is created
* J.H Cho 2012/03/30 1.5 Selection Sort function is created
* J.H Cho 2012/04/02 2.0 BigRand        function is created
* J.H Cho 2012/04/02 2.3 QuckSort       function is created
* J.H Cho 2012/04/02 2.5 PrintOut                is created
* J.H Cho 2012/04/02 2.7 PerformanceCounter      is created
* J.H Cho 2012/04/02 3.0 Sort Program            is Done
* ========================================================
*/

#include <iostream>
#include <time.h>
#include <iomanip>
#include <windows.h>

using namespace std;

void BigRand(int mA[], int RANGE);
void quicksort(int mA[], int left, int right);
void swap(int& A, int& B);
void selectionSort( int mA[], int n );
void print(int mA[], int RANGE);

int partition(int mA[], int left, int right, int pivotIndex);

int main()
{
	
	int RANGE = 20;
	int *mA = new int [RANGE];
	print(mA, RANGE);

}

void print(int mA[], int RANGE)
{/*
	LARGE_INTEGER freq, t_1, t_2;
	LONGLONG t_diff;
	double elapsed_time;

	int *mB = new int [RANGE];

	cout<<"*************** Quick Sort ****************"<<endl;
	cout<<endl;
	cout<<"/initial Array <first 100>/"<<endl;
	
	BigRand(mA, RANGE);
	for(int i = 0; i < 100; i++)
	{
		cout<<setw(6)<<mA[i]<<", ";
		mB[i] = mA[i];
	}

	cout<<endl;
	cout<<"/initial Array <last 100>/"<<endl;

	for(int i= RANGE - 100; i < RANGE; i++)
	{
		cout<<setw(6)<<mA[i]<<", ";
		mB[i] = mA[i];
	}

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&t_1);

	quicksort(mA, 0, RANGE-1);

	QueryPerformanceCounter(&t_2);

	t_diff = t_2.QuadPart - t_1.QuadPart; 
	elapsed_time = ( (double)t_diff / (double)freq.QuadPart) * 1000000;
	
	cout<<endl;
	cout<<"QuickSort took "<<elapsed_time<<" [micro-seconds] to sort "<<RANGE<<" Integer array"<<endl;
	cout<<endl;

	cout<<"After Quick Sort <fist 100>:"<<endl;
	for(int i = 0; i < 100; i++)
	{
		cout<<setw(6)<<mA[i]<<", ";
	}

	cout<<endl;

	cout<<"After Quick Sort <last 100>:"<<endl;
	for(int i = RANGE-100; i < RANGE; i++)
	{
		cout<<setw(6)<<mA[i]<<", ";
	}

	cout<<endl;
	cout<<"**************** Selection Sort ******************"<<endl;
	cout<<endl;

	cout<<"/initial Array <first 100>/"<<endl;
	for(int i = 0; i < 100; i++)
	{
		cout<<setw(6)<<mB[i]<<", ";
	}

	cout<<endl;
	cout<<"/initial Array <last 100>/"<<endl;
	for(int i = RANGE-100; i < RANGE; i++)
	{
		cout<<setw(6)<<mB[i]<<", ";
	}

	cout<<endl;
	
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&t_1);

	selectionSort(mA, RANGE);

	QueryPerformanceCounter(&t_2);

	t_diff = t_2.QuadPart - t_1.QuadPart; 
	elapsed_time = ( (double)t_diff / (double)freq.QuadPart) * 1000000;
	
	cout<<endl;
	cout<<"QuickSort took "<<elapsed_time<<" [micro-seconds] to sort "<<RANGE<<" Integer array"<<endl;
	cout<<endl;

	cout<<"After Selection Sort <fist 100>:"<<endl;
	for(int i = 0; i < 100; i++)
	{
		cout<<setw(6)<<mA[i]<<", ";
	}

	cout<<endl;

	cout<<"After Selection Sort <last 100>:"<<endl;
	for(int i = RANGE-100; i < RANGE; i++)
	{
		cout<<setw(6)<<mA[i]<<", ";
	}
	*/


	BigRand(mA, RANGE);

	for(int i = 0 ; i < RANGE; i++)
	{
	cout<<mA[i]<<" ";
	}

	cout<<endl;
	cout<<endl;

	quicksort(mA, 0, RANGE-1);
}


void BigRand(int mA[], int RANGE)
{
	srand(time(0));
	char *flag = new char[RANGE];

	unsigned int uint_32;
	unsigned int bigRand;

	for(int i = 0; i < RANGE; i++ )
	{
		flag[i] = 0;
	}

	int count = 0;

	while (count < RANGE) 
	{

		uint_32 = ( ( long ) rand() << 15) | rand(); 
		bigRand = uint_32 % RANGE;

		if (flag[bigRand] == 1) 

		{ 
			continue;
		} 

		else 

		{
			flag[bigRand] = 1;
			mA[count++] = bigRand; // 빅랜드에 +1해주면 1부터100까지 뽑을수있음
		}

	} 

}


void selectionSort( int mA[], int n ) //셀렉션 소트 정의
{
	int iPos, jPos; //변수 선언
	int iMin;       //변수 선언

	for (iPos = 0; iPos < n; iPos++)  //반복문, n은 RANGE
	{

		iMin = iPos;                  //iMin에 iPos 치환
		for (jPos = iPos+1; jPos < n; jPos ++) //
		{
			if (mA[jPos] < mA[iMin]) 
			{
				iMin = jPos;
			} 
		}
		if ( iMin != iPos ) 
		{
			swap(mA[iPos], mA[iMin]); //스왑
		}
	}
}


void quicksort(int mA[], int left, int right) //퀵소트 함수 호출.
{
	for(int i = 0; i < 20 ; i++)
	{
		cout<<mA[i]<<" ";
	}

	cout<<endl;

	int pivotIndex, newPI; //피봇인덱스,뉴피봇인덱스 선언

		pivotIndex = left + ( right - left ) / 2 ; //피봇인덱스 위치 계산

	if (left >= right) //재귀함수 종료 조건 
		return;
	else if (left < right) //재귀함수 진입 조건 //초기 pdf에서 라이트는 0~"12"
	{
		newPI = partition(mA, left, right, pivotIndex); // 파티션한 반환값은 storeindex를 반환하며 storeindex는 0~12의 6번배열에 담긴 수보다 작은 수를 6번배열 앞으로(0~5) 파티션
		quicksort(mA, left, newPI - 1);                 // 재귀함수 진입, newPI는 전에 파티션한 storeIndex이며 이 값에 -1을 한값이 다음 재귀함수의 right가 된다.
		quicksort(mA, newPI + 1, right);                // 재귀함수 진입, 0~4까지의 배열의 pivotIndex에서 왼쪽편 배열이 소트가 끝나고 리턴이 되면 오른쪽 배열 소트를위해 재귀함수 진입.

	}

}

int partition(int mA[], int left, int right, int pivotIndex) 
//mA[] 난수생성된 배열과 초기 left = 0과 right 12와 피봇인덱스 계산된 값을 받아옴
{
	int storeIndex;  //저장인덱스, 즉 소트 된 배열까지의 배열번호 저장
	int pivotValue;  //피봇밸류

	pivotValue = mA[pivotIndex]; //피봇밸류에 mA[피봇인덱스], 즉 0~12사이의 중간값 치환

	swap(mA[pivotIndex], mA[right]); // 피봇인덱스(0~12사이의 중간값)과 맨끝값 right=12 값과 스왑.

	storeIndex = left; //초기 스토어 인덱스를 left(0)으로 치환

	for (int i = left; i <= right - 1; i++)// left부터 right( 맨끝값 right 전 까지) 반복문
	{

		if (mA[i] < pivotValue) //mA[i]의 i가 0~11까지 확인하면서 pivotvalue 즉, 초기 0~12의 중간값과 비교 
		{						//pivotvalue 보다 작은수가 나오면 조건문 진입

			swap(mA[i], mA[storeIndex]); //mA[i]는 피봇밸류보다 작은수, 그리고 mA[storeIndex] 즉 0~12까지의 배열중 맨 첫번째와 스왑
			storeIndex = storeIndex + 1; //mA[0]에는 pivotvalue 보다 작은수가 담겻으며 다음 스왑을 위해 storeIndex + 1 을 함

		}

	}

	swap(mA[storeIndex], mA[right]); //반복문 종료후 끝으로 보낸 초기 pivotIndex를 현재 비교가 끝난 storeIndex 자리와 스왑

	return storeIndex; // 파티션이 끝난 곳 까지의 배열번호를 반환
}

void swap(int& A, int& B)
{
	int temp;
	temp = A;
	A = B;
	B = temp;
}