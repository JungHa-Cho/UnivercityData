/*
* File Name: "lab2-4x4.cpp"
* Description:
* - This program is 
* 4x4 행렬의 더하기 빼기 곱하기 디터미넌트값 행렬식 계산.
* Programmed by Jung-Ha Cho,
* Last updated: Version 1.0, March 14, 2012 (by Jung-Ha Cho).
*
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/03/14) Version Remarks
* J.H Cho 2012/03/14 1.0 Project & Main function is created
* J.H Cho 2012/03/14 1.1 4x4 add & sub  function is created
* J.H Cho 2012/03/15 1.5 4x4 multiply & print function is created
* J.H Cho 2012/03/15 2.0 4x4 deteminant function is created
* J.H Cho 2012/03/17 3.0 inv function is created
* ========================================================
*/

#include <iostream>
#include <iomanip>
using namespace std;

void print2DMtrx(double mA[][4], int mSize);

void mtrxAdd(double mA[][4], double mB[][4], double mC[][4], int mSize);               ////////함수 정의 
void mtrxSubtract(double mA[][4], double mB[][4], double mD[][4], int mSize);            
void mtrxMultiply(double mA[][4], double mB[][4], double mE[][4], int mSize);
void mtrxMultiply2(double mF[][4], double mE[][4], double inv_A[][4], int mSize);

void getMinor3x3(double mA[][3], int mSize, int j, int k, double minor[][2]);          ///함수 정의
void getMinor4x4(double mA[][4], int mSize, int j, int k, double minor[][3]);

void invMtrx(double mA[][4], double inv_A[][4], int mSize);

double det2x2(double mA[][2], int mSize);                       
double det3x3(double mA[][3],int mSize);
double det4x4(double mA[][4],int mSize);

double mA[][4]={{1, 2, 3, 9},{6, 5, 4, 10},{7, 9, 8, 12},{21, 19, 17, 15}};
double mB[][4]={{99, 102, 103, 11},{55, 106, 104, 12},{107, 109, 98, 14},{31, 33, 36, 40}};
double mC[4][4]={ 0 };
double mD[4][4]={ 0 };
double mE[4][4]={ 0 };
double mF[4][4]={ 0 };

double inv_A[4][4]={ 0 };



void main()              //////////print2DMtrx 함수 호출문
{                        //////////cout 작성은 print2DMtrx여기서 했지만
	print2DMtrx(mA, 4);  //////////출력되지 않고
}                        //////////메인 문 에서 호출되어 출력




void print2DMtrx(double mA[][4], int Size)   //출력함수
{
	mtrxAdd(mA,mB,mC,4);////////////// 함수의 헤더
	mtrxSubtract(mA, mB, mD, 4);////// 각 함수에 주어지는 값
	mtrxMultiply(mA, mB, mE, 4);////// 
	invMtrx(mE, inv_A, 4);////////////
	mtrxMultiply2(mF, mE, inv_A, 4);//

	double det;                 ///디터미넌트 값 저장할 det 정의
	int i,j;

	cout<<"Matrix A"<<endl;          /////각 계산값 출력문
	for(i = 0; i < Size; i++)
	{
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mA[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout << endl;
	}


		cout<<"Matrix B"<<endl;
	for(i = 0; i < Size; i++)
	{
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mB[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout << endl;
	}



	cout<<"Matrix ADD : C = A + B"<<endl;
	for(i = 0; i < Size; i++)
	{
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mC[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c=", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mA[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c+", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mB[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout << endl;
	}



	cout<<"Matrix Subtract : D = A - B"<<endl;
	for(i = 0; i < Size; i++)
	{
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mD[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c=", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mA[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c-", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mB[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout << endl;
	}



	cout<<"Matrix Multiply : E = A * B"<<endl;
	for(i = 0; i < Size; i++)
	{
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mE[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c=", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mA[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c*", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout <<setw(5)<< mB[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout << endl;
	}
	det = det4x4(mE, Size);
	cout<<"Determinent of E is : "<<setw(13)<<det<<endl;


	////inverse matrix print

	
	for(i = 0; i < Size; i++)
	{
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout.setf(ios::fixed);  // 소수점 4자리까지 표시
		     cout.precision(4);
 
			 cout<<setw(8)<< inv_A[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout<<endl;
	}
	

	cout<<"Matrix Multiply : F = A * B"<<endl;
	for(i = 0; i < Size; i++)
	{
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout.setf(ios::fixed);  // 소수점 표시 안함
		     cout.precision(0);
             cout <<setw(3)<< mF[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c=", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout.setf(ios::fixed);   ///소수점 5자리 까지 표시
		     cout.precision(0);
			 cout <<setw(5)<< mE[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c ", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c ", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c*", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c ", 0xa6, 0xa5);

		}
		for(j = 0; j < Size; j++)
		{

			 if(j==0)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa3);
			 if(j==0)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa6);

			 cout.setf(ios::fixed);   ////소수점 4자리까지 표시
		     cout.precision(4);
			 cout <<setw(8)<< inv_A[i][j];

			 if(j==3)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==3)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==3)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout << endl;
	}




}






void mtrxAdd(double mA[][4], double mB[][4], double mC[][4], int mSize) ////////////더하기
{
	int i,j;
	for(i = 0; i < mSize; i++)
	{
		for(j = 0; j < mSize; j++)
		{
		mC[i][j] = mA[i][j] + mB[i][j];
		}
	}

}

void mtrxSubtract(double mA[][4], double mB[][4], double mD[][4], int mSize) ////////빼기
{
	int i,j;
	for(i = 0; i < mSize; i++)
	{
		for(j = 0; j < mSize; j++)
		{
			mD[i][j] = mA[i][j] - mB[i][j];
		}
	}

}

void mtrxMultiply(double mA[][4], double mB[][4], double mE[][4], int mSize) 
//// 이차원 행렬의 곱셈은 A,B 행렬이라는 두개가 있다면 A의 행렬 주소 00,01,02,03과
//// B행렬의 주소 00, 10, 20, 30로 00*00 + 01*10 + 02*20 + 03*30을 
//// 값을 저장할 C행렬 주소 00에 저장한다.
{
	int i,j,k;

	for(i=0; i<mSize; i++)
	{
		for( j=0; j<mSize; j++) 
		{
			for(k=0; k<mSize; k++)//// 곱할 행과 열을 1씩 올리며 총 4번 루프를 돈다.
			{
				mE[i][ j] = mE[i][j] + ( mA[i][k] * mB[k][ j] );	
			}
		}
	}
}



void mtrxMultiply2(double mF[][4], double mE[][4], double inv_A[][4], int mSize) 
//mE에 대한 인버스 값과 mE를 mF에 곱해서 축적한다.
{
	int i,j,k;

	for(i=0; i<mSize; i++)
	{
		for( j=0; j<mSize; j++) 
		{
			for(k=0; k<mSize; k++)
			{
				mF[i][j] = mF[i][j] + ( mE[i][k] * inv_A[k][ j] );	
			}
		}
	}
}




double det2x2 (double mA[][2], int mSize) // 2x2행렬의 디터미넌트 값 반환
{
	double det = 0.0;
	if (mSize == 2) 
	{
		det = mA[0][0]*mA[1][1] - mA[0][1]*mA[1][0];
		return det;
	} else {
		cout << "Matrix size is not 2. Use other function !!" << endl;
		return 0.0;
	}
}


double det3x3 (double mA[][3], int mSize)
// 디터미넌트란 a00*m00 를 들수있는데 여기서 m00란
// a00가 속한 행과 열을 제외한 나머지 3x3 행렬에서	    
// 다시 2x2행렬을 구해 디터미넌트 값을 구해 
// 3x3으로 반환한뒤 a00 - a01 - a02 - a03으로 넘어가며
// 각각 속한 행과 열을 제외한 3x3의 디터미넌트를 계산한다.
{
	int j=0, k;
	double minor[2][2];
	double det=0.0;
	double cofactor, sign;

	for (k=0; k<mSize; k++) {
		getMinor3x3(mA, mSize, j, k, minor);
		sign = (0==( j+k)%2) ? 1 : -1;
		cofactor = sign * det2x2(minor, mSize-1);
		det = det + ( mA[j][k] * cofactor );
	}
	return det;
}



double det4x4(double mA[][4], int mSize) // 디터미넌트란 a00*m00 를 들수있는데 여기서 m00란
{                                        // a00가 속한 행과 열을 제외한 나머지 3x3 행렬에서
	int i=0, j, sign;                    // 다시 2x2행렬을 구해 디터미넌트 값을 구해 
	double minor[3][3];                  // 3x3으로 반환한뒤 a00 - a01 - a02 - a03으로 넘어가며
	double det=0.0, cofactor;            // 각각 속한 행과 열을 제외한 3x3의 디터미넌트를 계산한다.
	for (i=0, j=0; j<mSize; j++) 
	{
		getMinor4x4(mE, mSize, i, j, minor);  // 주어진 변수들로 4x4의 minor 호출
		sign = (0==(i+j)%2) ? 1 : -1;      // 부호 변경 sign
		cofactor= sign * det3x3(minor, mSize-1); ////여기서 코팩트 값이 m00값이 된다
		det = det + ( mA[0][j] * cofactor ); // 구한 디터미넌트 값 더하기.
	}
//	cout<<det<<endl;
//	cout<<cofactor<<endl;
	return det;
}






void getMinor3x3(double org[][3], int mSize, int j, int k, double minor[][2])///////org=mA 행에서 각행과열을 제외한 Minor[2][2]를 뽑는다.
{
	int n, m;
	int v=0, w=0;
	for(n=0; n<mSize; n++){
		if(n==j)
			continue; ////////////////////////// 제외할 열 선택
		for(m=0; m<mSize; m++)
		{
			if(m==k)
				continue; //////////////////////제외할 행 선택
			minor[v][w] = org[n][m]; ////////////제외할 열행을 뺀 나머지 3x3행렬을 마이너에 담는다
			w = (w+1)%(2);
//			cout<<setw(4)<<minor[v][w];
//			cout<<endl;
		}
		v=(v+1)%(2);
	}
}


void getMinor4x4(double org[][4], int mSize, int j, int k, double minor[][3])   /////////////org=mA 행에서 각행과열을 제외한 Minor[3][3]를 뽑는다.
{
	int n, m;
	int v=0, w=0;
	for(n=0; n<mSize; n++)
	{
		if(n==j)
			continue; ////////////////////////// 제외할 열 선택
		for(m=0; m<mSize; m++)
		{
			if(m==k)
				continue; //////////////////////제외할 행 선택
			minor[v][w] = org[n][m];  ////////////제외할 열행을 뺀 나머지 3x3행렬을 마이너에 담는다
			w = (w+1)%(3);
//		cout<<setw(4)<<minor[v][w];
//		cout<<endl;
		}
		v=(v+1)%(3);
	}
}


void invMtrx(double mA[][4], double inv_A[][4], int mSize)   ////////////// mE = mA * mB 에 대한 mE 인버스 값
{
	double minor[3][3];
	double det_A, det_M, cofactor,sign;
	det_A = det4x4(mA, mSize);                      ///////////adjoint(A)
	for(int i=0; i<mSize; i++) 
	{
		for(int j=0; j<mSize; j++) 
		{
			getMinor4x4(mA, mSize, i, j, minor);      ///4x4행렬인 mE에서 3x3 마이너행렬을 뽑아온다.
			det_M=det3x3(minor, mSize-1);             
			sign = (0==(i+j)%2) ? 1: -1;
			cofactor=sign*det_M/det_A;               ////////        { 1/det(A) } * adj 값
			inv_A[j][i]=cofactor;
		}
	}
}