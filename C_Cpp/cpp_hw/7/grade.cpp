#include <iostream>
#include <string>

#define MAXREC 1000

using namespace std;

struct Grade {
	string id;
	string name;
	double grade1;
	double grade2;
	double grade3;
};

struct Grade* NewGrade(string id, string name, double grade1, double grade2, double grade3){
	struct Grade* g = new struct Grade;
	g->id = id;
	g->name = name;
	g->grade1 = grade1;
	g->grade2 = grade2;
	g->grade3 = grade3;

	return g;
}

void swap(void *v[], int i, int j){
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1, comp);
	qsort(v, last+1, right, comp);
}


double average(double d1, double d2, double d3) {
	return d1/3 + d2/3 + d3/3;
}

int avgcomp(struct Grade *g1, struct Grade *g2) {
	double d1 = average(g1->grade1, g1->grade2, g1->grade3);
	double d2 = average(g2->grade1, g2->grade2, g2->grade3);

	if(d1 < d2)
		return 1;
	else if(d1 > d2)
		return -1;
	else
		return 0;
}

int main(int argc, char const *argv[])
{
	struct Grade* grades[MAXREC];
	int n = 0;
	cout<<"Format: id name grade1 grade2 grade3"<<endl;
	cout<<"`ok` to end input"<<endl;
	while(true){
		cout<<">>> ";
		string id, name;
		double g1, g2, g3;
		cin>>id;
		if(id == "ok")
			break;
		cin>>name>>g1>>g2>>g3;
		grades[n++] = NewGrade(id, name, g1, g2, g3);
	}

	qsort((void **)grades, 0, n-1, (int (*)(void *, void *))avgcomp);

	cout<<"======sorted======"<<endl;
	cout<<"id\tname\tgrade1\tgrade2\tgrade3"<<endl;
	for (int i = 0; i < n; ++i){
		struct Grade* g = grades[i];
		cout<<g->id<<'\t'<<g->name<<'\t'<<g->grade1<<'\t'<<g->grade2<<'\t'<<g->grade3<<endl;
		delete g;
	}
	return 0;
}