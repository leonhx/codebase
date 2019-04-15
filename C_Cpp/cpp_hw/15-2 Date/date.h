#ifndef _LEON_DATE_H
#define _LEON_DATE_H 1

#include <iostream>

class Date
{
public:
	Date(int year, int month, int day): year(year),
		month(month), day(day) {}
	void increment();

private:
	int year;
	int month;
	int day;

	friend std::ostream& operator<< (std::ostream&, const Date&);
};

extern std::ostream& operator<< (std::ostream&, const Date&);


#endif