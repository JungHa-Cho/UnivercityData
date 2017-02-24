#include <iostream>

class Cmplx {
public:
	Cmplx (); // constructor
	//~Cmplx();
	void inputCmplx();
	void outputCmplx();
	void sumall();
	Cmplx addCmplx(const Cmplx &) const; // addition
	Cmplx subtractCmplx(const Cmplx &) const; // subtraction
	Cmplx multiplyCmplx(const Cmplx &) const; // multiplication
	Cmplx divideCmplx(const Cmplx &) const; // division
	double getMag();
	double getReal();
	double getImaginary();
private:
	double real;
	double imaginary;
	double magnitude;
};