/*
* File Name: "lab2-4x4.cpp"
* Description:
* - This program is 
* 4x4 ����� ���ϱ� ���� ���ϱ� ���͹̳�Ʈ�� ��Ľ� ���.
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

void mtrxAdd(double mA[][4], double mB[][4], double mC[][4], int mSize);               ////////�Լ� ���� 
void mtrxSubtract(double mA[][4], double mB[][4], double mD[][4], int mSize);            
void mtrxMultiply(double mA[][4], double mB[][4], double mE[][4], int mSize);
void mtrxMultiply2(double mF[][4], double mE[][4], double inv_A[][4], int mSize);

void getMinor3x3(double mA[][3], int mSize, int j, int k, double minor[][2]);          ///�Լ� ����
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



void main()              //////////print2DMtrx �Լ� ȣ�⹮
{                        //////////cout �ۼ��� print2DMtrx���⼭ ������
	print2DMtrx(mA, 4);  //////////��µ��� �ʰ�
}                        //////////���� �� ���� ȣ��Ǿ� ���




void print2DMtrx(double mA[][4], int Size)   //����Լ�
{
	mtrxAdd(mA,mB,mC,4);////////////// �Լ��� ���
	mtrxSubtract(mA, mB, mD, 4);////// �� �Լ��� �־����� ��
	mtrxMultiply(mA, mB, mE, 4);////// 
	invMtrx(mE, inv_A, 4);////////////
	mtrxMultiply2(mF, mE, inv_A, 4);//

	double det;                 ///���͹̳�Ʈ �� ������ det ����
	int i,j;

	cout<<"Matrix A"<<endl;          /////�� ��갪 ��¹�
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

			 cout.setf(ios::fixed);  // �Ҽ��� 4�ڸ����� ǥ��
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

			 cout.setf(ios::fixed);  // �Ҽ��� ǥ�� ����
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

			 cout.setf(ios::fixed);   ///�Ҽ��� 5�ڸ� ���� ǥ��
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

			 cout.setf(ios::fixed);   ////�Ҽ��� 4�ڸ����� ǥ��
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






void mtrxAdd(double mA[][4], double mB[][4], double mC[][4], int mSize) ////////////���ϱ�
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

void mtrxSubtract(double mA[][4], double mB[][4], double mD[][4], int mSize) ////////����
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
//// ������ ����� ������ A,B ����̶�� �ΰ��� �ִٸ� A�� ��� �ּ� 00,01,02,03��
//// B����� �ּ� 00, 10, 20, 30�� 00*00 + 01*10 + 02*20 + 03*30�� 
//// ���� ������ C��� �ּ� 00�� �����Ѵ�.
{
	int i,j,k;

	for(i=0; i<mSize; i++)
	{
		for( j=0; j<mSize; j++) 
		{
			for(k=0; k<mSize; k++)//// ���� ��� ���� 1�� �ø��� �� 4�� ������ ����.
			{
				mE[i][ j] = mE[i][j] + ( mA[i][k] * mB[k][ j] );	
			}
		}
	}
}



void mtrxMultiply2(double mF[][4], double mE[][4], double inv_A[][4], int mSize) 
//mE�� ���� �ι��� ���� mE�� mF�� ���ؼ� �����Ѵ�.
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




double det2x2 (double mA[][2], int mSize) // 2x2����� ���͹̳�Ʈ �� ��ȯ
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
// ���͹̳�Ʈ�� a00*m00 �� ����ִµ� ���⼭ m00��
// a00�� ���� ��� ���� ������ ������ 3x3 ��Ŀ���	    
// �ٽ� 2x2����� ���� ���͹̳�Ʈ ���� ���� 
// 3x3���� ��ȯ�ѵ� a00 - a01 - a02 - a03���� �Ѿ��
// ���� ���� ��� ���� ������ 3x3�� ���͹̳�Ʈ�� ����Ѵ�.
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



double det4x4(double mA[][4], int mSize) // ���͹̳�Ʈ�� a00*m00 �� ����ִµ� ���⼭ m00��
{                                        // a00�� ���� ��� ���� ������ ������ 3x3 ��Ŀ���
	int i=0, j, sign;                    // �ٽ� 2x2����� ���� ���͹̳�Ʈ ���� ���� 
	double minor[3][3];                  // 3x3���� ��ȯ�ѵ� a00 - a01 - a02 - a03���� �Ѿ��
	double det=0.0, cofactor;            // ���� ���� ��� ���� ������ 3x3�� ���͹̳�Ʈ�� ����Ѵ�.
	for (i=0, j=0; j<mSize; j++) 
	{
		getMinor4x4(mE, mSize, i, j, minor);  // �־��� ������� 4x4�� minor ȣ��
		sign = (0==(i+j)%2) ? 1 : -1;      // ��ȣ ���� sign
		cofactor= sign * det3x3(minor, mSize-1); ////���⼭ ����Ʈ ���� m00���� �ȴ�
		det = det + ( mA[0][j] * cofactor ); // ���� ���͹̳�Ʈ �� ���ϱ�.
	}
//	cout<<det<<endl;
//	cout<<cofactor<<endl;
	return det;
}






void getMinor3x3(double org[][3], int mSize, int j, int k, double minor[][2])///////org=mA �࿡�� ��������� ������ Minor[2][2]�� �̴´�.
{
	int n, m;
	int v=0, w=0;
	for(n=0; n<mSize; n++){
		if(n==j)
			continue; ////////////////////////// ������ �� ����
		for(m=0; m<mSize; m++)
		{
			if(m==k)
				continue; //////////////////////������ �� ����
			minor[v][w] = org[n][m]; ////////////������ ������ �� ������ 3x3����� ���̳ʿ� ��´�
			w = (w+1)%(2);
//			cout<<setw(4)<<minor[v][w];
//			cout<<endl;
		}
		v=(v+1)%(2);
	}
}


void getMinor4x4(double org[][4], int mSize, int j, int k, double minor[][3])   /////////////org=mA �࿡�� ��������� ������ Minor[3][3]�� �̴´�.
{
	int n, m;
	int v=0, w=0;
	for(n=0; n<mSize; n++)
	{
		if(n==j)
			continue; ////////////////////////// ������ �� ����
		for(m=0; m<mSize; m++)
		{
			if(m==k)
				continue; //////////////////////������ �� ����
			minor[v][w] = org[n][m];  ////////////������ ������ �� ������ 3x3����� ���̳ʿ� ��´�
			w = (w+1)%(3);
//		cout<<setw(4)<<minor[v][w];
//		cout<<endl;
		}
		v=(v+1)%(3);
	}
}


void invMtrx(double mA[][4], double inv_A[][4], int mSize)   ////////////// mE = mA * mB �� ���� mE �ι��� ��
{
	double minor[3][3];
	double det_A, det_M, cofactor,sign;
	det_A = det4x4(mA, mSize);                      ///////////adjoint(A)
	for(int i=0; i<mSize; i++) 
	{
		for(int j=0; j<mSize; j++) 
		{
			getMinor4x4(mA, mSize, i, j, minor);      ///4x4����� mE���� 3x3 ���̳������ �̾ƿ´�.
			det_M=det3x3(minor, mSize-1);             
			sign = (0==(i+j)%2) ? 1: -1;
			cofactor=sign*det_M/det_A;               ////////        { 1/det(A) } * adj ��
			inv_A[j][i]=cofactor;
		}
	}
}