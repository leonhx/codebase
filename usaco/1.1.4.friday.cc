/*
ID: xerxes.1
PROG: friday
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef enum {
    MON = 0,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN,
} Weekday;

class Year {
private:
    int year;
    int day_of_months[12];
    int n_days;
    Weekday start_day;
    bool leap() {
        return (year % 100 != 0 && year % 4 == 0) || year % 400 == 0;
    }
public:

    int COUNT[7];

    Year(int year, Weekday start_day): year(year), start_day(start_day), day_of_months { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, COUNT { 0, 0, 0, 0, 0, 0, 0 }, n_days(365) {
        if (leap()) {
            day_of_months[1] = 29;
            n_days = 366;
        }
    }

    Weekday first_day_of_next_year() {
        return (Weekday)((start_day + n_days) % 7);
    }

    void count() {
        Weekday day = (Weekday)((start_day + 12) % 7);
        COUNT[day] ++;
        for (int month = 0; month < 11; ++month) {
            day = (Weekday)((day + day_of_months[month]) % 7);
            COUNT[day] ++;
        }
    }
};

int main() {
    ifstream fin ("friday.in");
    ofstream fout ("friday.out");

    int N;
    fin >> N;

    int start_year = 1900;
    Weekday start_day = MON;

    int COUNT[7] = { 0, 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < N; ++i) {
        Year year(start_year+i, start_day);
        year.count();
        for (int i = 0; i < 7; ++i) {
            COUNT[i] += year.COUNT[i];
        }

        start_day = year.first_day_of_next_year();
    }

    for (int i = 0; i < 7; ++i) {
        fout << COUNT[(i + 5) % 7];
        if (i != 6) {
            fout << " ";
        } else {
            fout << endl;
        }
    }

    return 0;
}

