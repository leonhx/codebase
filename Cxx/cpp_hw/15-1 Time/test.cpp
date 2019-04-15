#include "time.h"
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	Time t(3600);
	cout << t << endl;
	cout << (t+=3673) << endl;
	return 0;
}