/*
* File Name: "StructCmplx.cpp"
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
#include <math.h>
#include <iomanip>

using namespace std;

struct Cmplx{
	double real;
	double imaginary;
	double magnitude;
};

Cmplx cmplxAdd(Cmplx c1,Cmplx c2);
Cmplx cmplxSubtract(Cmplx c1, Cmplx c2);
Cmplx cmplxMultiply(Cmplx c1, Cmplx c2);
Cmplx cmplxDivide(Cmplx c1, Cmplx c2);

int main()
{
	Cmplx cmplxs[6];
	char i;

	cout<<"첫번째 실수부와 허수부를 입력하세요\n";
	cout<<"real : "; cin>>cmplxs[0].real; 
	cout<<"imaginary : "; cin>>cmplxs[0].imaginary;
	cmplxs[0].magnitude = sqrt((cmplxs[0].real*cmplxs[0].real) + (cmplxs[0].imaginary * cmplxs[0].imaginary));

	cout<<"두번째 실수부와 허수부를 입력하세요\n";
	cout<<"real : "; cin>>cmplxs[1].real; 
	cout<<"imaginary : "; cin>>cmplxs[1].imaginary; cout<<endl;
	cmplxs[1].magnitude = sqrt((cmplxs[1].real*cmplxs[1].real) + (cmplxs[1].imaginary * cmplxs[1].imaginary));
	
	if(cmplxs[0].imaginary < 0) {i = '-';}else{i = '+';};
	cout<<"cmplxs[0]: "<<setw(8)<<cmplxs[0].real<<" "<<i<<" j"<<fabs(cmplxs[0].imaginary);
	cout<<" (magnitude : "<<cmplxs[0].magnitude<<" )"<<endl;

	if(cmplxs[1].imaginary < 0) {i = '-';}else{i = '+';};
	cout<<"cmplxs[1]: "<<setw(8)<<cmplxs[1].real<<" "<<i<<" j"<<fabs(cmplxs[1].imaginary);
	cout<<" (magnitude : "<<cmplxs[1].magnitude<<" )"<<endl;

	/********************Add**********************/
	cmplxs[2] = cmplxAdd(cmplxs[0], cmplxs[1]);
	if(cmplxs[2].imaginary < 0) {i = '-';}else{i = '+';};
	cout<<"cmplxs[2]: "<<setw(8)<<cmplxs[2].real<<" "<<i<<" j"<<fabs(cmplxs[2].imaginary);
	cout<<" (magnitude : "<<cmplxs[2].magnitude<<" )"<<endl;
	/********************Substract**********************/
	cmplxs[3] = cmplxSubtract(cmplxs[0], cmplxs[1]);
	if(cmplxs[3].imaginary < 0) {i = '-';}else{i = '+';};
	cout<<"cmplxs[3]: "<<setw(8)<<cmplxs[3].real<<" "<<i<<" j"<<fabs(cmplxs[3].imaginary);
	cout<<" (magnitude : "<<cmplxs[0].magnitude<<" )"<<endl;

	/********************Multiply**********************/
	cmplxs[4] = cmplxMultiply(cmplxs[0], cmplxs[1]);
	if(cmplxs[4].imaginary < 0) {i = '-';}else{i = '+';};
	cout<<"cmplxs[0]: "<<setw(8)<<cmplxs[4].real<<" "<<i<<" j"<<fabs(cmplxs[4].imaginary);
	cout<<" (magnitude : "<<cmplxs[4].magnitude<<" )"<<endl;
	/********************Divide**********************/
	cmplxs[5] = cmplxDivide(cmplxs[0], cmplxs[1]);
	if(cmplxs[5].imaginary < 0) {i = '-';}else{i = '+';};
	cout<<"cmplxs[0]: "<<setw(8)<<cmplxs[5].real<<" "<<i<<" j"<<fabs(cmplxs[5].imaginary);
	cout<<" (magnitude : "<<cmplxs[5].magnitude<<" )"<<endl;
}

Cmplx cmplxAdd(Cmplx c1, Cmplx c2)
{ //*****************************더하기************************//
	Cmplx Complete;

	Complete.real = c1.real + c2.real;
	Complete.imaginary = c1.imaginary + c2.imaginary;
	Complete.magnitude = sqrt(Complete.real*Complete.real + Complete.imaginary*Complete.imaginary);
	return Complete;
}
Cmplx cmplxSubtract(Cmplx c1, Cmplx c2)
{  //**********************빼기********************//
	Cmplx Complete;

	Complete.real = c1.real - c2.real ;
	Complete.imaginary = c1.imaginary - c2.imaginary ;
	Complete.magnitude = sqrt(Complete.real*Complete.real + Complete.imaginary*Complete.imaginary);
	return Complete;
}
Cmplx cmplxMultiply(Cmplx c1, Cmplx c2)
{ //*******************분배법칙적용 곱하기***********************/
	Cmplx Complete;

	Complete.real = ( c1.real * c2.real ) + ( ( c1.imaginary * c2.imaginary ) * -1 ) ;
	Complete.imaginary = ( c1.real * c2.imaginary ) + ( c1.imaginary * c2.real ) ;
	Complete.magnitude = sqrt(Complete.real*Complete.real + Complete.imaginary*Complete.imaginary);
	return Complete;
}
Cmplx cmplxDivide(Cmplx c1, Cmplx c2)
{  //**********************분배법칙적용 나누기*********************//
	Cmplx Complete;

	Complete.real = ( ( c1.real * c2.real ) + ( c1.imaginary * c2.imaginary ) ) / ( ( c2.real * c2.real ) + (c2.imaginary * c2.imaginary) );
	Complete.imaginary = (-1 * ( c1.real * c2.imaginary ) + ( c1.imaginary * c2.real ) ) / ( ( c2.real * c2.real ) + ( c2.imaginary * c2.imaginary ) );
	Complete.magnitude = sqrt(Complete.real*Complete.real + Complete.imaginary*Complete.imaginary);
	return Complete;
}