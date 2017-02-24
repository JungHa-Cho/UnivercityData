/* 
*���̾ƿ� ���� 160 ���� 60
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
			mA[count++] = bigRand; // �򷣵忡 +1���ָ� 1����100���� ����������
		}

	} 

}


void selectionSort( int mA[], int n ) //������ ��Ʈ ����
{
	int iPos, jPos; //���� ����
	int iMin;       //���� ����

	for (iPos = 0; iPos < n; iPos++)  //�ݺ���, n�� RANGE
	{

		iMin = iPos;                  //iMin�� iPos ġȯ
		for (jPos = iPos+1; jPos < n; jPos ++) //
		{
			if (mA[jPos] < mA[iMin]) 
			{
				iMin = jPos;
			} 
		}
		if ( iMin != iPos ) 
		{
			swap(mA[iPos], mA[iMin]); //����
		}
	}
}


void quicksort(int mA[], int left, int right) //����Ʈ �Լ� ȣ��.
{
	for(int i = 0; i < 20 ; i++)
	{
		cout<<mA[i]<<" ";
	}

	cout<<endl;

	int pivotIndex, newPI; //�Ǻ��ε���,���Ǻ��ε��� ����

		pivotIndex = left + ( right - left ) / 2 ; //�Ǻ��ε��� ��ġ ���

	if (left >= right) //����Լ� ���� ���� 
		return;
	else if (left < right) //����Լ� ���� ���� //�ʱ� pdf���� ����Ʈ�� 0~"12"
	{
		newPI = partition(mA, left, right, pivotIndex); // ��Ƽ���� ��ȯ���� storeindex�� ��ȯ�ϸ� storeindex�� 0~12�� 6���迭�� ��� ������ ���� ���� 6���迭 ������(0~5) ��Ƽ��
		quicksort(mA, left, newPI - 1);                 // ����Լ� ����, newPI�� ���� ��Ƽ���� storeIndex�̸� �� ���� -1�� �Ѱ��� ���� ����Լ��� right�� �ȴ�.
		quicksort(mA, newPI + 1, right);                // ����Լ� ����, 0~4������ �迭�� pivotIndex���� ������ �迭�� ��Ʈ�� ������ ������ �Ǹ� ������ �迭 ��Ʈ������ ����Լ� ����.

	}

}

int partition(int mA[], int left, int right, int pivotIndex) 
//mA[] ���������� �迭�� �ʱ� left = 0�� right 12�� �Ǻ��ε��� ���� ���� �޾ƿ�
{
	int storeIndex;  //�����ε���, �� ��Ʈ �� �迭������ �迭��ȣ ����
	int pivotValue;  //�Ǻ����

	pivotValue = mA[pivotIndex]; //�Ǻ������ mA[�Ǻ��ε���], �� 0~12������ �߰��� ġȯ

	swap(mA[pivotIndex], mA[right]); // �Ǻ��ε���(0~12������ �߰���)�� �ǳ��� right=12 ���� ����.

	storeIndex = left; //�ʱ� ����� �ε����� left(0)���� ġȯ

	for (int i = left; i <= right - 1; i++)// left���� right( �ǳ��� right �� ����) �ݺ���
	{

		if (mA[i] < pivotValue) //mA[i]�� i�� 0~11���� Ȯ���ϸ鼭 pivotvalue ��, �ʱ� 0~12�� �߰����� �� 
		{						//pivotvalue ���� �������� ������ ���ǹ� ����

			swap(mA[i], mA[storeIndex]); //mA[i]�� �Ǻ�������� ������, �׸��� mA[storeIndex] �� 0~12������ �迭�� �� ù��°�� ����
			storeIndex = storeIndex + 1; //mA[0]���� pivotvalue ���� �������� ������� ���� ������ ���� storeIndex + 1 �� ��

		}

	}

	swap(mA[storeIndex], mA[right]); //�ݺ��� ������ ������ ���� �ʱ� pivotIndex�� ���� �񱳰� ���� storeIndex �ڸ��� ����

	return storeIndex; // ��Ƽ���� ���� �� ������ �迭��ȣ�� ��ȯ
}

void swap(int& A, int& B)
{
	int temp;
	temp = A;
	A = B;
	B = temp;
}