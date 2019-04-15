#include "linearlist.h"

using namespace std;

int main(int argc, char const *argv[])
{
	LinearList ll;
	ll.insert(1, 0);
	ll.insert(2, 1);
	ll.insert(3, 2);
	ll.insert(9, 1);
	cout<<ll<<endl;

	return 0;
}