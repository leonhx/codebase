#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Queen {
	int column;
	int row;
};

struct Queen* NewQueen(int column) {
	struct Queen* q = new struct Queen;
	if(column < 0 || column >= 8)
		return NULL;
	q->column = column;
	q->row = 0;
	return q;
}

struct EightQueens {
	struct Queen* queens[8];
};

struct EightQueens* NewEightQueens() {
	struct EightQueens* eq = new struct EightQueens;
	for (int i = 0; i < 8; ++i){
		struct Queen* q = NewQueen(i);
		eq->queens[i] = q;
	}
	return eq;
}

void DeleteEightQueens(struct EightQueens* eq) {
	for (int i = 0; i < 8; ++i){
		struct Queen* q = eq->queens[i];
		delete q;
	}
	delete eq;
}

bool conflict(struct Queen* q1, struct Queen* q2) {
	if(q1->row == q2->row)
		return true;
	if(abs(q1->column - q2->column) == abs(q1->row - q2->row))
		return true;
	if(q1->column == q2->column)
		return true;

	return false;
}

// whether the first `eq->valid` queens conflict
// `valid`: 安放好了的皇后数目，列（column）索引小于这个的所有皇后不互相冲突
bool anyConflict(struct EightQueens* eq, int valid) {
	for (int i = 0; i < valid; ++i){
		for (int j = i+1; j < valid; ++j){
			if(conflict(eq->queens[i], eq->queens[j]))
				return true;
		}
	}

	return false;
}

// return `false` only when its `row` index roll back to 0
bool Reput(struct Queen* q) {
	return (q->row = (q->row + 1)%8) == 0 ? false : true;
}

// put the queens of which the indeces >= i
// return `true` when there is a solution, `false` when no solution
bool Solve(struct EightQueens* eq, int i) {
	if(i >= 8){
		return true;
	}
puti:
	while(anyConflict(eq, i+1)) {
		if(!Reput(eq->queens[i]))
			return false;
	}
	if(!Solve(eq, i+1)) {
		if(!Reput(eq->queens[i]))
			return false;
		goto puti;
	} else
		return true;
}

void Print(struct EightQueens* eq) {
	string div = "+-+-+-+-+-+-+-+-+";
	cout << div << endl;
	for (int i = 0; i < 8; ++i){
		for (int k = 0; k < 8; ++k){
			cout << '|';
			if(eq->queens[k]->row == i)
				cout << 'Q';
			else
				cout << ' ';
		}
		cout << '|' << endl << div << endl;
	}
}

int main(int argc, char const *argv[])
{
	struct EightQueens* eq = NewEightQueens();
	while(Solve(eq, 0)){
		Print(eq);
ask:
		cout << "There may be other solution(s), continue? [Y/n] ";
		string s;
		cin >> s;
		if(s == "N" || s == "n")
			break;
		else if (s != "Y" && s!= "y") {
			cout << "Sorry, I can't understand your mind. Please reinput..." << endl;
			goto ask;
		}
		int n = 7;
		while(!Reput(eq->queens[n])){
			n--;
			if(n < 0)
				break;
		}
	}
	DeleteEightQueens(eq);
	
	return 0;
}
