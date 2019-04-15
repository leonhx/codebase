#include "timewithdate.h"

using namespace std;

int main(int argc, char const *argv[])
{
	TimeWithDate d(2012, 2, 28, 12, 30, 56);
	cout << d << endl;
	d.next_day();
	cout << d << endl;
	d.next_day();
	cout << d << endl;
	d.previous_day();
	cout << d << endl;
	return 0;
}