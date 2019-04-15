/*
ID: xerxes.1
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct {
    int price;
    int amount;
} Farmer;

bool cmp_price(const Farmer &f1, const Farmer &f2) {
    return f1.price < f2.price;
}

int main() {
    ifstream fin ("milk.in");
    ofstream fout ("milk.out");

    int N, M;
    fin >> N >> M;

    Farmer *farmers = new Farmer[M];

    int p, a;
    for (int i = 0; i < M; ++i) {
        fin >> p >> a;
        farmers[i] = Farmer{p, a};
    }

    sort(farmers, farmers+M, cmp_price);
    int pay = 0;
    for (int i = 0; i < M && N > 0; ++i) {
        Farmer farmer = farmers[i];
        if (farmer.amount > N) {
            pay += N  * farmer.price;
            N = 0;
        } else {
            N -= farmer.amount;
            pay += farmer.price * farmer.amount;
        }
    }

    fout << pay << endl;

    delete[] farmers;
    return 0;
}
