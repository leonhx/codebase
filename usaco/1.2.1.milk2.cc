/*
ID: xerxes.1
PROG: milk2
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct {
    int start;
    int end;
} milk_interval;

bool cmp_start(const milk_interval &x, const milk_interval &y) {
    return x.start < y.start;
}

bool cmp_end(const milk_interval &x, const milk_interval &y) {
    return x.end < y.end;
}

bool cmp_len(const milk_interval &x, const milk_interval &y) {
    return x.end - x.start < y.end - y.start;
}

int main() {
    ifstream fin ("milk2.in");
    ofstream fout ("milk2.out");

    int N;
    fin >> N;

    milk_interval* intervals = new milk_interval[N];
    for (int i = 0; i < N; ++i) {
        int x, y;
        fin >> x >> y;
        intervals[i] = (milk_interval) { x, y };
    }

    sort(intervals, intervals + N, cmp_start);

    vector<milk_interval> non_cross_intervals;
    int i = 0;
    while (i < N) {
        milk_interval x = intervals[i];
        int j = 1;
        if (i+j < N) {
            milk_interval y = intervals[i+j];
            while (y.start <= x.end) {
                if (y.end > x.end) {
                    x.end = y.end;
                }
                j++;
                if (i+j < N) {
                    y = intervals[i+j];
                } else {
                    break;
                }
            }
        }
        i += j;
        non_cross_intervals.push_back(x);
    }

    milk_interval mi = *max_element(non_cross_intervals.begin(), non_cross_intervals.end(), cmp_len);
    int mmi = mi.end - mi.start;

    int mfi = 0;
    for (int i = 0; i < N-1; ++i) {
        int t = non_cross_intervals[i+1].start - non_cross_intervals[i].end;
        if (t > mfi) {
            mfi = t;
        }
    }

    fout << mmi << " " << mfi << endl;

    delete[] intervals;
    return 0;
}

