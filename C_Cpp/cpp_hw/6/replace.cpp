#include <iostream>
#include <cstring>

#define MAXLINE 1000

using namespace std;
// find string `target` in the string `inwhich`
// beginning at index `start`;
// return the index in the string `inwhich`
// of the first element of string `target`
int find(const char* target, const char* inwhich, int start);
int find_replace_str(char str[], const char find_str[], const char replace_str[]){
	char temp[MAXLINE];
	int i, count = 0;
	const int flen = strlen(find_str), rlen = strlen(replace_str);
	while((i = find(find_str, str, 0)) != -1){
		strcpy(temp, &str[i+flen]);
		strcpy(&str[i], replace_str);
		strcpy(&str[i+rlen], temp);
		count++;
	}
	return count;
}

int main(int argc, char const *argv[])
{
	char s[MAXLINE];
	char s1[MAXLINE];
	char s2[MAXLINE];
	cout<<"Original: ";
	cin.getline(s, MAXLINE);
	cout<<"Find: ";
	cin.getline(s1, MAXLINE);
	cout<<"Replace: ";
	cin.getline(s2, MAXLINE);
	cout<<find_replace_str(s, s1, s2)<<"\nAfter: "<<s<<endl;
	
	return 0;
}

int find(const char* target, const char* inwhich, int start){
	int i = start-1;
	char t, s, t0 = target[0];
	bool match = false;
	while((s = inwhich[++i]) != '\0'){
		if(s == t0){
			match = true;
			for (int j = 1; (t = target[j]) != '\0'; ++j){
				if (t != (s = inwhich[i+j]) || s == '\0'){
					match = false;
					break;
				}
			}
		}
		if(match == true)
			return i;
	}

	return -1;
}