#ifndef _LEON_COMPLEX_H
#define _LEON_COMPLEX_H 1


#include <iostream>

class Complex
{
public:
	Complex(const Complex& c): real(c.real), img(c.img) {};
	Complex(double real, double img): real(real), img(img) {};
	Complex(double real): real(real), img(0.0) {};
	Complex(int real): real(real), img(0.0) {};
	Complex(): real(0.0), img(0.0) {};
private:
	double real;
	double img;
	friend std::ostream& operator<< (std::ostream& out, const Complex&);
	friend Complex& operator+= (Complex&, const Complex&);
	friend Complex& operator-= (Complex&, const Complex&);
	friend Complex& operator*= (Complex&, const Complex&);
	friend Complex& operator/= (Complex&, const Complex&);
	friend Complex operator+ (const Complex&, const Complex&);
	friend Complex operator- (const Complex&, const Complex&);
	friend Complex operator* (const Complex&, const Complex&);
	friend Complex operator/ (const Complex&, const Complex&);
	friend inline bool operator== (const Complex&, const Complex&);
	friend inline bool operator!= (const Complex&, const Complex&);
};

extern std::ostream& operator<< (std::ostream& out, const Complex&);
extern Complex& operator+= (Complex&, const Complex&);
extern Complex& operator-= (Complex&, const Complex&);
extern Complex& operator*= (Complex&, const Complex&);
extern Complex& operator/= (Complex&, const Complex&);
extern Complex operator+ (const Complex&, const Complex&);
extern Complex operator- (const Complex&, const Complex&);
extern Complex operator* (const Complex&, const Complex&);
extern Complex operator/ (const Complex&, const Complex&);
extern inline bool operator== (const Complex&, const Complex&);
extern inline bool operator!= (const Complex&, const Complex&);

#endif