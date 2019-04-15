#include <iostream>

#define MAXLINE 1000

using namespace std;


int squeeze(char s1[], const char s2[]){
	int i = -1;
	int j = 0;
	char c, t;
	bool match = false;
	while((c = s1[++i]) != '\0'){
		for (int k = 0; (t = s2[k]) != '\0'; ++k){
			if(t == c){
				match = true;
				break;
			}
		}
		if(!match){
			s1[j++] = c;
		}
		match = false;
	}
	s1[j] = '\0';
	return i-j;
}

int main(int argc, char const *argv[])
{
	char s1[MAXLINE];
	char s2[MAXLINE];
	cout<<"s1: ";
	cin.getline(s1, MAXLINE);
	cout<<"s2: ";
	cin.getline(s2, MAXLINE);
	cout<<squeeze(s1, s2)<<"\ts1: "<<s1<<endl;
	
	return 0;
}