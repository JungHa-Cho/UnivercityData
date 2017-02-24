#include <iostream>
#include <iomanip>
#include "Cmplx.h"

using namespace std;

Cmplx::Cmplx(){
	real = 0.0;
	imaginary = 0.0;
}
void Cmplx::inputCmplx(){ 
	cout<<"실수부와 허수부를 입력하세요\n";
	cout<<"real : "; cin>>real; 
	cout<<"imaginary : "; cin>>imaginary;
	magnitude = sqrt((real*real) + (imaginary*imaginary));
}
void Cmplx::outputCmplx(){
	char i;
	if(imaginary < 0 ){ i = '-'; } else { i = '+'; };
	cout<<setw(8)<<real<<" "<<i<<" j"<<imaginary;
	cout<<" ( magnitude : "<<magnitude<<" )"<<endl;
}
double Cmplx::getMag(){return magnitude;}
double Cmplx::getReal(){return real;}
double Cmplx::getImaginary(){return imaginary;}
Cmplx Cmplx::addCmplx(const Cmplx &c) const
{
	Cmplx Complete;

	Complete.real = real + c.real;
	Complete.imaginary = imaginary + c.imaginary;
	Complete.magnitude = sqrt((Complete.real*Complete.real) + (Complete.imaginary*Complete.imaginary));
	return Complete;
}
Cmplx Cmplx::subtractCmplx(const Cmplx &c) const
{
	Cmplx Complete;

	Complete.real = real - c.real ;
	Complete.imaginary = imaginary - c.imaginary ;
	Complete.magnitude = sqrt( (Complete.real * Complete.real) + (Complete.imaginary * Complete.imaginary) ) ;
	return Complete;
}
Cmplx Cmplx::multiplyCmplx(const Cmplx &c) const
{
	Cmplx Complete;

	Complete.real = ( real * c.real ) + ( ( imaginary * c.imaginary ) * -1 ) ;
	Complete.imaginary = ( real * c.imaginary ) + ( imaginary * c.real ) ;
	Complete.magnitude = sqrt( Complete.real * Complete.real + Complete.imaginary * Complete.imaginary ) ;
	return Complete;
}
Cmplx Cmplx::divideCmplx(const Cmplx &c) const
{
	Cmplx Complete;

	Complete.real = ( ( real * c.real ) + ( imaginary * c.imaginary ) ) / ( ( c.real * c.real ) + (c.imaginary * c.imaginary) );
	Complete.imaginary = (-1 * ( real * c.imaginary ) + ( imaginary * c.real ) ) / ( ( c.real * c.real ) + ( c.imaginary * c.imaginary ) );
	Complete.magnitude = sqrt(( Complete.real * Complete.real ) + ( Complete.imaginary * Complete.imaginary )) ;
	return Complete;
}