#include <iostream>
#include <string>

using namespace std;

string int_to_str(int x){
	string s;
	unsigned u;
	if(x < 0){
		u = -x;
	} else {
		u = x;
	}

	string n[] = {"0", "1", "2", "3", 
					"4", "5", "6", "7",
					"8", "9"};
	do{
		s = n[u%10] + s;
	} while ((u/=10) != 0);

	return x < 0 ? "-" + s : s;
}

int main(int argc, char const *argv[])
{
	int i;
	while(true){
		cout<<">>> ";
		cin>>i;
		cout<<int_to_str(i)<<endl;
	}

	return 0;
}