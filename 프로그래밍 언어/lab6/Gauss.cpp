/*
* File Name: "Gauss.cpp"
* Description:
* - This program is Gauss Elimination
* Programmed by Jung-Ha Cho,
* Last updated: Version 1.5, April 06, 2012 (by Jung-Ha Cho).
*
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/04/06) Version Remarks
* J.H Cho 2012/04/06 1.0 Project & Main function is created
* J.H Cho 2012/04/06 1.2 
* ========================================================
*/
#define N 7 // size of linear system

void diagonalize(double mAUG[N][N+1], int size_N, int *solExist);
void pivoting(double aug[N][N+1], int size_N, int p, int *piv_found);
void print(double aug[N][N+1], int size_N, int *solExist);;

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(void)
{    
	int solExist = 1;

	double aug[N][N+1] = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 55.0},
	{2.0, 3.0, 4.0, 5.0, 1.0, 9.0, 3.0, 56.0},
	{3.0, 2.0, 5.0, 3.0, 2.0, 3.0, 2.0, 57.0},
	{4.0, 3.0, 2.0, 7.0, 2.0, 7.0, 2.0, 58.0},
	{5.0, 3.0, 2.0, 7.0, 2.0, 7.0, 2.0, 59.0},
	{6.0, 3.0, 2.0, 7.0, 2.0, 1.0, 5.0, 60.0},
	{7.0, 4.0, 3.0, 2.0, 9.0, 5.0, 8.0, 61.0}};

	print(aug, N, &solExist);
}

void print(double aug[N][N+1], int size_N, int *solExist)
{
	int i=0,j=0;

	cout << fixed; 
	cout.precision(2);

	double x[N];

	int error = 0;

	cout<<"Augmented Matrix:"<<endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N+1; j++)
		{
			if(j==N-N && i==0)
				printf("%c%c", 0xa6, 0xa3);
			if(j==N-N && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==6)
				printf("%c%c", 0xa6, 0xa6);

			cout<<setw(7)<<aug[i][j];

			if(j==N && i==0)
				printf("%c%c", 0xa6, 0xa4);
			if(j==N && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==6)
				printf("%c%c", 0xa6, 0xa5);
		}
		cout<<endl;
	}

	diagonalize(aug, N, solExist);

	cout<<"After Diagonalize:"<<endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N+1; j++)
		{
			if(j==N-N && i==0)
				printf("%c%c", 0xa6, 0xa3);
			if(j==N-N && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N-N && i==6)
				printf("%c%c", 0xa6, 0xa6);

			cout<<setw(7)<<aug[i][j];

			if(j==N && i==0)
				printf("%c%c", 0xa6, 0xa4);
			if(j==N && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==N && i==6)
				printf("%c%c", 0xa6, 0xa5);
		}
		cout<<endl;
	}

	if (solExist) 
	{
		cout <<"The solution of given linear system:\n ";
		for (i=0; i<N; i++)
		{
			x[i] = aug[i][N];
			cout << " x[" << i << "] : " << aug[i][N];
		}
	} 
	else 
	{
		cout << "No unique solution\n";
	}

	cout<<endl;


}

void diagonalize(double mAUG[N][N+1], int size_N, int *solExist)
{
	int j, k, p = 0; // pivot index
	double pivot, w;
	// Elimination of coefficients of above and below
	// the diagonal elements of mAUG[][]
	for (p=0; (*solExist) && (p<N); p++) 
	{
		pivoting(mAUG, size_N, p, solExist);
		if (*solExist) 
		{
			if (mAUG[p][p] != 1.0) 
			{ // adjust pivot row, if the pivot is not 1.0
				pivot = mAUG[p][p]; // scaling value pivot row
				mAUG[p][p] = 1.0; // make the diagonal element at pivot row into 1.0
				for (k=p+1; k<=N; k++) 
				{
					mAUG[p][k] /= pivot; // scaling the elements in pivot row
				} // for
			} // if(mAUG[p][p] != 1.0)
		} 
		else 
		{// end if (*solExist)
			break;
		}
		// eliminate coefficients above and below the pivot row
		for (j=0; j<N; j++)
		{ // for j-th row
			if ((j != p) && (mAUG[j][p] != 0.0))
			{
				w = mAUG[j][p]; // weight
				mAUG[j][p] = 0.0; // eliminate coefficients, just except the pivot row
				for (k=p+1; k<=N; k++) 
				{
					mAUG[j][k] -= w * mAUG[p][k]; // Rj = Rj – w * Rp
				}
			} // end if ( j !=p)
		} // end for (j=0; …)
	} // end for (p=0; …)
}

void pivoting(double aug[N][N+1], int size_N, int p, int *piv_found)
{
	double xmax=0.0, xtemp;
	int j, k, max_row;

	// find maximum pivot
	xmax = fabs(aug[p][p]);
	max_row = p;
	for (j=p+1; j< N; j++)
	{
		if (fabs(aug[j][p]) > xmax) 
		{
			xmax = fabs(aug[j][p]);
			max_row = j;
		}
	} 
	if (fabs(xmax) < 0.000001) 
	{
		*piv_found = false;
	} 
	else 
	{
		*piv_found = true;
		if (max_row != p) 
		{ // swap rows
			for (k=p; k<=N; k++) 
			{
				xtemp = aug[p][k];
				aug[p][k] = aug[max_row][k];
				aug[max_row][k] = xtemp;
			} // end for
		} // end if
	} // end if-else
} // end pivoting