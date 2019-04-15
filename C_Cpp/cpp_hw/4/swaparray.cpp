#include <iostream>

#define SIZE 10
#define M 7

void swap(int a[], int m, int n){
	for (int i = 0; i < m; ++i){
		int tmp = a[0];
		for (int j = 1; j < m+n; ++j){
			a[j-1] = a[j];
		}
		a[m+n-1] = tmp;
	}
}

int main(int argc, char const *argv[])
{
	int a[SIZE];
	for (int i = 0; i < SIZE; ++i){
		a[i] = i+1;
	}
	swap(a, M, SIZE-M);
	for (int i = 0; i < SIZE; ++i){
		std::cout<<a[i]<<std::endl;
	}
	
	return 0;
}