#include "date.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	Date d1(2008, 2, 28);
	cout << d1 << endl;
	d1.increment();
	cout << d1 << endl;
	Date d(2008, 12, 31);
	cout << d << endl;
	d.increment();
	cout << d << endl;
	Date d2(1900, 2, 28);
	cout << d2 << endl;
	d2.increment();
	cout << d2 << endl;
	Date d3(1970, 11, 30);
	cout << d3 << endl;
	d3.increment();
	cout << d3 << endl;

	return 0;
}