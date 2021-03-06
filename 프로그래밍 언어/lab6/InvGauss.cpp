/*
* File Name: "GaussInverse.cpp"
* Description:
* - This program is Gauss Elimination
* Programmed by Jung-Ha Cho,
* Last updated: Version 1.5, April 7, 2012 (by Jung-Ha Cho).
*
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/04/7) Version Remarks
* J.H Cho 2012/04/7 1.0 Project & Main function is created
* J.H Cho 2012/04/06 1.2 
* ========================================================
*/
#include <iostream>
#include <iomanip>

using namespace std;

#define SIZE_N 7

void InvMtrxGaussJordanElim(double mA[][SIZE_N],double inv_A[][SIZE_N], int N);
void print(double mA[][SIZE_N],double inv_A[][SIZE_N], int N);
void mtrxMultiply(double mA[][SIZE_N],double inv_A[][SIZE_N],double res[SIZE_N][SIZE_N], int N) ;

int main(void)
{	
	int N = 7;
	double mA[SIZE_N][SIZE_N] = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0},
								{2.0, 3.0, 4.0, 5.0, 1.0, 9.0, 3.0},
								{3.0, 2.0, 5.0, 3.0, 2.0, 3.0, 2.0},
								{4.0, 3.0, 2.0, 7.0, 2.0, 7.0, 2.0},
								{5.0, 3.0, 2.0, 7.0, 2.0, 7.0, 2.0},
								{6.0, 3.0, 2.0, 7.0, 2.0, 1.0, 5.0},
								{7.0, 4.0, 3.0, 2.0, 9.0, 5.0, 8.0}};

	double inv_A[SIZE_N][SIZE_N] = {0};


	print(mA, inv_A, N);
}

void print(double mA[][SIZE_N],double inv_A[][SIZE_N], int N)
{
	double res[SIZE_N][SIZE_N] = {0};

	cout << fixed; 
	cout.precision(2);

	cout<<"Matrix A:"<<endl;
	for( int i = 0 ; i < N ; i++ )
	{
		for( int j = 0 ; j < N ; j++ )
		{
			if(j==0 && i==0)
				printf("%c%c", 0xa6, 0xa3);
			if(j==0 && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==6)
				printf("%c%c", 0xa6, 0xa6);

			cout<<setw(8)<<mA[i][j]<<" ";

			if(j==6 && i==0)
				printf("%c%c", 0xa6, 0xa4);
			if(j==6 && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==6)
				printf("%c%c", 0xa6, 0xa5);
		}
		cout<<endl;
	}

	InvMtrxGaussJordanElim(mA, inv_A, N);

	cout<<"Inverse A:"<<endl;
	for( int i = 0 ; i < N ; i++ )
	{
		for( int j = 0 ; j < N ; j++ )
		{
			if(j==0 && i==0)
				printf("%c%c", 0xa6, 0xa3);
			if(j==0 && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==6)
				printf("%c%c", 0xa6, 0xa6);

			cout<<setw(8)<<inv_A[j][i]<<" ";

			if(j==6 && i==0)
				printf("%c%c", 0xa6, 0xa4);
			if(j==6 && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==6)
				printf("%c%c", 0xa6, 0xa5);
		}
		cout<<endl;
	}

	mtrxMultiply(mA, inv_A, res, N);

	cout<<"Res = A * Inv_A:"<<endl;	
	for( int i = 0 ; i < N ; i++ )
	{
		for( int j = 0 ; j < N ; j++ )
		{
			if(j==0 && i==0)
				printf("%c%c", 0xa6, 0xa3);
			if(j==0 && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==0 && i==6)
				printf("%c%c", 0xa6, 0xa6);

			cout<<setw(8)<<res[j][i]<<" ";

			if(j==6 && i==0)
				printf("%c%c", 0xa6, 0xa4);
			if(j==6 && i==1)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==2)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==3)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==4)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==5)
				printf("%c%c", 0xa6, 0xa2);
			if(j==6 && i==6)
				printf("%c%c", 0xa6, 0xa5);
		}
		cout<<endl;
	}



}

void InvMtrxGaussJordanElim(double mA[][SIZE_N],double inv_A[][SIZE_N], int N)
{
	int j, k, p = 0; // pivot index
	double pivot, w;
	double mAUG[SIZE_N][2*SIZE_N];
	// augment matrix in N x 2N size for { A | I }
	// Part 1. Prepare the work matrix mAUG[N][2N]
	for(j=0; j<N; j++) 
	{
		for (k=0; k<N; k++)
			mAUG[j][k] = (double) mA[j][k];
		for (k=N; k<2*N; k++)
			mAUG[j][k] = (k == (j+N)) ? 1.0 : 0.0;
	} // end for(j=0; . . . )12.//Part 2. Elimination of coefficients of above and below
	// the diagonal elements of mAUG[][]
	for (p=0; p<N; p++) 
	{
		if (mAUG[p][p] != 1.0) { // adjust pivot row, if the pivot is not 1.0
			pivot = mAUG[p][p]; // scaling value pivot row
			mAUG[p][p] = 1.0; // make the diagonal element at pivot row into 1.0
			for (k=p+1; k< 2*N; k++)
				mAUG[p][k] /= pivot; // scaling the elements in pivot row
		} // end if (mAUG[p][p] != 1.0)
		// eliminate coefficients above and below the pivot row
		for (j=0; j < N; j++) { // for j-th row
			if ((j != p) && (mAUG[j][p] != 0.0))
			{
				w = mAUG[j][p]; // weight
				mAUG[j][p] = 0.0; // eliminate coefficients, just except the pivot row
				for (k=p+1; k<2*N; k++)
					mAUG[j][k] -= w * mAUG[p][k]; // Rj = Rj – w * Rp
			} // end if ( j !=p)
		} // end for (j=0; … )
	} // end for (p=0; …)
	//Part 3. Copy the result inverse matrix to inv_A[][]
	for (j=0; j<N; j++) 
	{
		for (k=0; k<N; k++) 
		{
			inv_A[j][k] = mAUG[j][k + N];
		} // end for (k=0; … )
	} // end for (j=0; . . . )
}

void mtrxMultiply(double mA[][SIZE_N],double inv_A[][SIZE_N],double res[SIZE_N][SIZE_N], int N)

{
	int i,j,k;
	for(i=0; i<N; i++)
	{
		for( j=0; j<N; j++) 
		{
			for(k=0; k<N; k++)
			{
				res[i][j] = res[i][j] + ( mA[i][k] * inv_A[k][ j] );	
			}
		}
	}
}