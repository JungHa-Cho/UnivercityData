/*
* File Name: "exam.cpp"
* Description:
* - This program is
* Programmed by Jung-Ha Cho,
* Last updated: Version 1.0, March 31, 2012 (by Jung-Ha Cho).
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/03/07) Version Remarks
* J.H Cho 2012/03/31 1.0 Project & Main function is created
* ========================================================
*/
#include<iostream>                      
#include<stdio.h>
#include<math.h>
#include<iomanip>
#define SIZE_N 5
using namespace std;

void printMtrx(double m[][5],int size_n);                                                
void statistics2DArray(double mA[5][5], double size_n, double& max, double& min, double& avg, double& var, double& st_dev);
void mtrxAdd(double mA[5][5],double mB[5][5],double mC[5][5],int size_n);
void mtrxSub(double mA[5][5],double mB[5][5],double mD[5][5],int size_n);
void mtrxMul(double mA[5][5],double mB[5][5],double mE[5][5],int size_n);
double det2x2(double A[][2],int size_n);
double det3x3(double A[3][3],int size_n);
double det4x4(double A[4][4],int size_n);
double det5x5(double A[5][5],int size_n);
void getminor5x5(double A[5][5],int size_n,int i, int j, double minor[4][4]);
void getminor4x4(double A[4][4],int size_n,int i, int j, double minor[3][3]);
void getminor3x3(double A[3][3],int size_n,int i, int j, double minor[2][2]);
void inverseMtrx(double A[5][5],double inv_A[5][5],int size_n);

int main()
{
	double max, min, avg, var, st_dev;

	double mA[SIZE_N][SIZE_N]={
		{1.0,2.0,3.0,4.0,5.0},
		{2.0,3.0,4.0,5.0,1.0},
		{3.0,2.0,5.0,3.0,2.0},
		{4.0,3.0,2.0,7.0,2.0},
		{5.0,4.0,3.0,2.0,9.0}
	};
	double mB[SIZE_N][SIZE_N]={
		{1.0,0.0,0.0,0.0,1.0},
		{0.0,1.0,0.0,0.0,0.0},
		{0.0,0.0,1.0,0.0,0.0},
		{0.0,0.0,0.0,1.0,0.0},
		{1.0,0.0,0.0,0.0,1.0},
	};
	double mC[SIZE_N][SIZE_N];                                   
	double mD[SIZE_N][SIZE_N];                                   
	double mE[SIZE_N][SIZE_N];                                    
	int size_n=SIZE_N;                               
	double inv_A[SIZE_N][SIZE_N],mF[SIZE_N][SIZE_N]; 
	double det;
    
	cout<<"Mtrx mA:\n";
	printMtrx(mA,5);   

	statistics2DArray(mA, size_n, max, min, avg, var, st_dev);
	cout<<"statistics of mA: max ("<<max<<"), min("<<min<<"), avg("<<avg<<"),\n";
	cout<<"                  var("<<var<<"), st_dev("<<st_dev<<")\n";

	cout<<"Mtrx mB:\n";
	printMtrx(mB,5);                               

	mtrxAdd(mA,mB,mC,5);                     
	cout<<"Mtrx mC = mA + mB:\n";
	printMtrx(mC,5);

	mtrxSub(mA,mB,mD,5);                     
	cout<<"Mtrx mD = mA - mB:\n";
	printMtrx(mD,5);

	mtrxMul(mA,mB,mE,5);                     
	cout<<"Mtrx mE = mA * mB:\n";
	printMtrx(mE,5);

	det = det5x5(mA,5);
	cout<<"Determinant of mA: " <<det<<endl;  

	inverseMtrx(mA,inv_A,5);                  
	cout <<"Inv_A:\n";          
	printMtrx(inv_A,5);

	mtrxMul(mA,inv_A,mF,5);                       
	cout<<"Mtrx mF = mA * inv_A:\n";
	printMtrx(mF,5);
	
}

void printMtrx(double m[][5],int size_n)    
{
	cout.setf(ios::fixed);             
	cout.precision(0);

	for(int i = 0; i < size_n; i++)
	{
		for(int j = 0; j < size_n; j++)
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
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==0)
				 if(i==4)
					 printf("%c%c", 0xa6, 0xa6);




			 cout <<setw(5)<< m[i][j];
			 if(m[i][i]<0)
			 {
				 m[i][i] = m[i][i] * -1;
			 }



			 

			 if(j==4)
				 if(i==0)
					 printf("%c%c", 0xa6, 0xa4);
			 if(j==4)
				 if(i==1)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==4)
				 if(i==2)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==4)
				 if(i==3)
					 printf("%c%c", 0xa6, 0xa2);
			 if(j==4)
				 if(i==4)
					 printf("%c%c", 0xa6, 0xa5);

		}
		cout << endl;
	}
}

void statistics2DArray(double mA[][5], double size_n, double& max, double& min, double& avg, double& var, double& st_dev)
{
	double sum = 0.0;
	double var1= 0.0;

	max=min=mA[0][0];

	for(int j=0; j<5; j++)
	{
		for(int i=0; i<5; i++)
		{
			if(max < mA[j][i])
				max = mA[j][i];
			if(min > mA[j][i])
				min = mA[j][i];
			sum = sum + mA[j][i];
		}
	}
	avg = sum / 25;

	for(int j=0; j<5; j++)
	{
		for(int i=0; i<5; i++)
		{
			var1 = var1 + (mA[j][i] - avg) * (mA[j][i] - avg);
		}
	}
	var = var1 / 25;

	st_dev = sqrt(var);

}
void mtrxAdd(double mA[5][5],double mB[5][5],double mC[5][5],int size_n) 
{
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			mC[i][j]=mA[i][j]+mB[i][j];    //°è»ê½Ä
		}
		
	}
}
void mtrxSub(double mA[5][5],double mB[5][5],double mD[5][5],int size_n)
{
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			mD[i][j]= mA[i][j]-mB[i][j];  
		}
	}
}
void mtrxMul(double mA[5][5],double mB[5][5],double mE[5][5],int size_n) 
{
	int i,j,k;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			mE[i][j] = 0;
			for(k=0;k<5;k++)
			{
				mE[i][j] += mA[i][k] * mB[k][j]; 
			}
		}
	}
}
double det2x2(double A[][2],int size_n)   
{
	double det =0.0;
	if(size_n==2)
	{
		det = A[0][0]*A[1][1]-A[0][1]*A[1][0];   
		return det;
	}
	else
	{
		cout << "Matrix size_n is not 2."<<endl;
		return 0;
	}
}
double det3x3(double A[3][3],int size_n)   
{
	int i=0,j;
	double sign, cofactor;
	double minor[2][2];        
	double det=0.0;

	for(j=0;j<size_n;j++)
	{
		getminor3x3(A,size_n,i,j,minor);
		sign = (0 == (i+j)%2) ? 1 : -1 ; 
		cofactor = sign * det2x2(minor,2);
		det += A[i][j] * cofactor;
	}
	return det;
}
double det4x4(double A[4][4],int size_n)   
{
	int i=0, j,sign;
	double minor[3][3];
	double det=0.0 , cofactor;

	for(j=0; j<size_n;j++)
	{
		getminor4x4(A,size_n,i,j,minor);
		sign = (0 == (i+j)%2) ? 1 : -1 ;
		cofactor = sign * det3x3(minor,3);
		det += A[i][j]*cofactor;
	}
	return det;
}
double det5x5(double A[5][5],int size_n)
{
	int i =0,j,sign;
	double minor[4][4];
	double det=0.0 , cofactor;
		
	for(i=0,j=0; j<size_n;j++)
	{
		getminor5x5(A,size_n,i,j,minor);
		sign = (0 == (i+j)%2) ? 1 : -1 ;
		cofactor = sign * det4x4(minor,4);
		det += A[0][j]*cofactor;
	}
	return det;
}
void getminor5x5(double A[5][5],int size_n,int i, int j, double minor[4][4])
{
	int n,m;
	int v=0,w=0;

	for(n=0;n<size_n;n++)
	{
		if(n==i)
			continue;
		for(m=0;m<size_n;m++)
		{
			if(m==j)
				continue;
			minor[v][w]=A[n][m];
			w=(w+1)%(size_n-1);
		}
		v=(v+1)%(size_n-1);
	}
}
void getminor4x4(double A[4][4],int size_n,int i, int j, double minor[3][3])
{
	int n,m;
	int v=0,w=0;

	for(n=0;n<size_n;n++)
	{
		if(n==i)
			continue;
		for(m=0;m<size_n;m++)
		{
			if(m==j)
				continue;
			minor[v][w]=A[n][m];
			w=(w+1)%(size_n-1);
		}
		v=(v+1)%(size_n-1);
	}
}
void getminor3x3(double A[3][3],int size_n,int i, int j, double minor[2][2])
{
	int n,m;
	int v=0,w=0;

	for(n=0;n<size_n;n++)
	{
		if(n==i)
			continue;
		for(m=0;m<size_n;m++)
		{
			if(m==j)
				continue;
			minor[v][w]=A[n][m];
			w=(w+1)%(size_n-1);
		}
		v=(v+1)%(size_n-1);
	}
}
void inverseMtrx(double A[5][5],double inv_A[5][5],int size_n) 
{
	int i,j,sign;
	double minor[4][4];
	double cofactor,det_A,det_M;

	det_A = det5x5(A,5);     
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			getminor5x5(A,size_n,i,j,minor);
			det_M = det4x4(minor,4);
			sign = (0==(i+j)%2) ? 1: -1;
			cofactor = sign *det_M/det_A;
			inv_A[j][i] = cofactor;
		}
	}
}
	