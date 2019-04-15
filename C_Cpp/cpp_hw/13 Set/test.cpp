#include "set.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	Set s1, s2;
	s1 += 1;
	s1 += 1;
	s1 += 2;
	s1 += 6;
	cout << s1 << endl;
	s1 -= 2;
	s1 -= 7;
	cout << s1 << endl;
	s2 += 3;
	s2 += 7;
	s2 += 1;
	s2 += 2;
	s2 += 6;
	s2 += 9;

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s1-s2 << endl;
	cout << (s1&s2) << endl;
	cout << (s1|s2) << endl;
	cout << (s1!=s2) << endl;
	s2 -= 9;
	s2 -= 3;
	s2 -= 7;
	cout << (s1==s2) <<endl;
	cout << (s1<=s2) <<endl;
	return 0;
}