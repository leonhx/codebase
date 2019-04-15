#include "date.h"

#include <string>

void Date::increment()
{
	int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year%400 == 0 || (year%100 !=0 && year%4 == 0))
		d[1] = 29;
	if (day < d[month-1])
		day += 1;
	else
	{
		day = 1;
		if (month < 12)
			month += 1;
		else
		{
			month = 1;
			year += 1;
		}
	}	
}


std::ostream& operator<< (std::ostream& out, const Date& d)
{
	std::string m[] = {"Jan.", "Feb.", "Mar.", "Apr.", "May",
					"Jun.", "Jul.", "Aug.", "Sept.", "Oct.",
					"Nov.", "Dec."};
	out << m[d.month-1] << " " << d.day << ", " << d.year;
	return out;
}