#include <iostream>
#include <stack>
#include <cstdlib>

#define MAXLINE 1000

using namespace std;

bool isOperator(char c) {
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	default:
		return false;
	}
}

bool isOperand(char c) {
	return ('0' <= c && c <= '9') || c == '.';
}

int priority(char c) {
	switch(c) {
	case '+':
	case '-':
		return 13;
	case '*':
	case '/':
		return 14;
	default:
		return 0;
	}
}

double popOut(stack<double> &operands, stack<char> &operators) {
	const char op = operators.top();
	operators.pop();
	const double second = operands.top();
	operands.pop();
	const double first = operands.top();
	operands.pop();

	switch(op) {
	case '+':
		return first + second;
	case '-':
		return first - second;
	case '*':
		return first * second;
	case '/':
		return first / second;
	default:
		cerr<<"error: fail to pop out"<<endl;
		return 0;
	}
}

double calc(const char s[]){
	stack<double> N;
	stack<char> O;
	int i = 0;
	char c;
	bool number = true;
	while((c = s[i]) != '\0') {
		while(c == ' ' || c == '\t')
			c = s[++i];
		if(isOperand(c) || (number && c == '-')){
			char dd[MAXLINE];
			int j = 0;
			dd[j] = c;
			while(isOperand(dd[++j] = s[++i]))
				;
			dd[j] = '\0';
			N.push(atof(dd));
			number = false;
		} else if(c == '(') {
			O.push(c);
			i++;
			number = true;
		} else if(c == ')') {
			if(O.top() == '(') {
				O.pop();
			} else {
				while(O.top() != '(' && isOperator(O.top()) && priority(c) <= priority(O.top())) {
					N.push(popOut(N, O));
					if(O.empty()) {
						cerr<<"error: parentheses not match!"<<endl;
						return 0;
					}
				}
				O.pop();
			}
			i++;
			number = true;
		} else if(isOperator(c)) {
			if(O.empty()){
				O.push(c);
			} else if(O.top() == '('){
				O.push(c);
			} else if(priority(c) > priority(O.top())){
				O.push(c);
			} else {
				N.push(popOut(N, O));
				if(!O.empty()) {
					while(!O.empty() && isOperator(O.top()) && priority(c) <= priority(O.top())) {
						N.push(popOut(N, O));
					}
				}
				O.push(c);
			}
			i++;
			number = true;
		} else if(c != '\n' && c != '\0') {
			cerr<<"error: unidentified symbol!"<<endl;
			return 0;
		}
	}

	while(!O.empty()){
		double t = popOut(N, O);
		N.push(t);
	}
		
	return N.top();
}

int main(int argc, char const *argv[]){
	char s[MAXLINE];
	while(true) {
		cout<<">>> ";
		cin.getline(s, MAXLINE);
		if (s[0] == 'q')
			return 0;

		cout<<calc(s)<<endl;
	}

	return 0;
}