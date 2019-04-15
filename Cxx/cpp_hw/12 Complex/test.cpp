#include "complex.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	// Complex ct1(0, 1);
	// Complex ct2(1, 0);
	// Complex ct3(0, 0);
	// Complex ct4(5);
	// Complex ct5(0);
	// Complex ct6;
	// cout << ct1 << endl;
	// cout << ct2 << endl;
	// cout << ct3 << endl;
	// cout << ct4 << endl;
	// cout << ct5 << endl;
	// cout << ct6 << endl;

	Complex c1(1, 2);
	// cout << c1 << endl;
	Complex c2(3, -2);
	// c1 -= c2;
	// cout << c1 << endl;
	int c3 = 5;
	// c1 += c3;
	// cout << c1 << endl;
	double c4 = 6;
	float c5 = 2;

	cout << c1 << " + " << c2 << " = " << c1+c2 << endl;
	cout << c1 << " - " << c2 << " = " << c1-c2 << endl;
	cout << c1 << " * " << c2 << " = " << c1*c2 << endl;
	cout << c1 << " / " << c2 << " = " << c1/c2 << endl;
	cout << c1 << " + " << c3 << " = " << c1+c3 << endl;
	cout << c1 << " - " << c3 << " = " << c1-c3 << endl;
	cout << c1 << " * " << c3 << " = " << c1*c3 << endl;
	cout << c1 << " / " << c3 << " = " << c1/c3 << endl;
	cout << c1 << " + " << c4 << " = " << c1+c4 << endl;
	cout << c1 << " - " << c4 << " = " << c1-c4 << endl;
	cout << c1 << " * " << c4 << " = " << c1*c4 << endl;
	cout << c1 << " / " << c4 << " = " << c1/c4 << endl;
	cout << c1 << " + " << c5 << " = " << c1+c5 << endl;
	cout << c1 << " - " << c5 << " = " << c1-c5 << endl;
	cout << c1 << " * " << c5 << " = " << c1*c5 << endl;
	cout << c1 << " / " << c5 << " = " << c1/c5 << endl;
	return 0;
}