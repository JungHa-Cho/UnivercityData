/*
* File Name: "main.cpp"
* Description:
* - This program is Class
* Programmed by Jung-Ha Cho,
* Last updated: Version 1.0, May 09, 2012 (by Jung-Ha Cho).
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/05/09) Version Remarks
* J.H Cho 2012/05/09 1.0 Project & Main function is created
* ========================================================
*/
#include <iostream>
#include "Cmplx.h"
using namespace std;

void sortCmplx(Cmplx cmplxs[],int size); // proto-type

int main()
{
	const int SIZE_ARRAY = 6;
	Cmplx cmplxs[SIZE_ARRAY];

	cmplxs[0].inputCmplx();
	cmplxs[1].inputCmplx();
	cmplxs[2] = cmplxs[0].addCmplx(cmplxs[1]);
	cmplxs[3] = cmplxs[0].subtractCmplx(cmplxs[1]);
	cmplxs[4] = cmplxs[0].multiplyCmplx(cmplxs[1]);
	cmplxs[5] = cmplxs[0].divideCmplx(cmplxs[1]);

	for (int k=0; k<SIZE_ARRAY; k++) {
		cout<<"cmplxs["<<k<<"] : ";
		cmplxs[k].outputCmplx();
	}

	sortCmplx(cmplxs, SIZE_ARRAY);

	for (int k=0; k<SIZE_ARRAY; k++) {
		cout<<"Sort by Magnitude : ";
		cmplxs[k].outputCmplx();
	}

	double sumMag=0.0, sumReal=0.0, sumImagin=0.0, sumallmag = 0.0;

	cout<<"모두 더한값"<<endl;
	for(int k=0; k<SIZE_ARRAY; k++)
	{
		sumReal = sumReal + cmplxs[k].getReal();
		sumImagin=sumImagin + cmplxs[k].getImaginary();
		sumMag = sumMag + cmplxs[k].getMag();
	}
	cout<<"real : "<<sumReal<<endl;
	cout<<"imagin : "<<sumImagin<<endl;
	cout<<"Mag : "<<sumMag<<endl;

	sumallmag = sqrt((sumReal*sumReal) + (sumImagin*sumImagin));

	cout<<"Sum All Magnitude : "<<sumallmag<<endl;
	return 0;
}
void sortCmplx(Cmplx cmplxs[], int size)
{
	int iPos, jPos; //변수 선언
	int iMin;       //변수 선언

	Cmplx temp;

	for (iPos = 0; iPos < size; iPos++)  //반복문, n은 RANGE
	{

		iMin = iPos;                  //iMin에 iPos 치환
		for (jPos = iPos+1; jPos < size; jPos ++) //
		{
			if ((cmplxs+jPos)->getMag() < (cmplxs+iMin)->getMag()) 
			{
				iMin = jPos;
			} 
		}
		if ( iMin != iPos ) 
		{
			temp = cmplxs[iPos];
			cmplxs[iPos] = cmplxs[iMin];
			cmplxs[iMin]= temp;
		}
	}
}

