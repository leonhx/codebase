#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int hour;
	int min;
	while(true){
		cout<<"hour: ";
		cin>>hour;
		if(0 <= hour && hour <= 23)
			break;
		cout<<"error: invalid hour "<<hour<<endl;
	}

	while(true){
		cout<<"minute: ";
		cin>>min;
		if(0 <= min && min <= 59)
			break;
		cout<<"error: invalid minute "<<min<<endl;
	}

	if(0 <= hour && hour <= 12)
		cout<<hour;
	else
		cout<<hour-12;

	cout<<":"<<min;

	if(0 <= hour && hour <= 11)
		cout<<"am";
	else
		cout<<"pm";

	cout<<endl;

	return 0;
}