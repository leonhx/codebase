#include "complex.h"

#include <climits>

std::ostream& operator<< (std::ostream& out, const Complex& c1)
{
	bool r = (c1.real != 0.0);
	bool i = (c1.img != 0.0);
	if ( !r && !i)
	{
		out << 0;
		return out;
	}
	if (r)
		out << c1.real;
	if (r && i && c1.img > 0)
		out << "+";
	if (i)
	{
		if (c1.img == 1.0)
			out << "i";
		else
			out << c1.img << "i";
	}
	return out;
}

Complex& operator+= (Complex& c1, const Complex& c2)
{
	c1.real += c2.real;
	c1.img += c2.img;
	return c1;
}

Complex& operator-= (Complex& c1, const Complex& c2)
{
	c1.real -= c2.real;
	c1.img -= c2.img;
	return c1;
}

Complex& operator*= (Complex& c1, const Complex& c2)
{
	double a = c1.real;
	double b = c1.img;
	c1.real = a*c2.real - b*c2.img;
	c1.img = b*c2.real + a*c2.img;
	return c1;
}

Complex& operator/= (Complex& c1, const Complex& c2)
{
	double a = c1.real;
	double b = c1.img;
	double c = c2.real;
	double d = c2.img;
	double deno = c*c + d*d;
	c1.real = (a*c + b*d) / deno;
	c1.img = (b*c - a*d) / deno;
	return c1;
}

Complex operator+ (const Complex& c1, const Complex& c2)
{
	Complex c(c1);
	c += c2;
	return c;
}

Complex operator- (const Complex& c1, const Complex& c2)
{
	Complex c(c1);
	c -= c2;
	return c;
}

Complex operator* (const Complex& c1, const Complex& c2)
{
	Complex c(c1);
	c *= c2;
	return c;
}

Complex operator/ (const Complex& c1, const Complex& c2)
{
	Complex c(c1);
	c /= c2;
	return c;
}

inline bool operator== (const Complex& c1, const Complex& c2)
{
	return c1.real == c2.real && c1.img == c2.img;
}

inline bool operator!= (const Complex& c1, const Complex& c2)
{
	return c1.real != c2.real || c1.img != c2.img;
}
