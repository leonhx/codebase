#include "timewithdate.h"

const TimeWithDate::time_t SECS_IN_A_DAY = 24*60*60;

TimeWithDate& TimeWithDate::operator= (const TimeWithDate& t)
{
	this->year = t.year;
	this->month = t.month;
	this->month = t.month;
	this->hour = t.hour;
	this->min = t.min;
	this->sec = t.sec;
	return *this;
}

void TimeWithDate::next_day()
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

void TimeWithDate::previous_day()
{
	int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year%400 == 0 || (year%100 !=0 && year%4 == 0))
		d[1] = 29;
	if (day > 1)
		day -= 1;
	else
	{
		if (month > 1)
			month -= 1;
		else
		{
			month = 12;
			year -= 1;
		}
		day = d[month-1];
	}
}

TimeWithDate& TimeWithDate::operator+= (time_t t)
{
	t += this->seconds();
	int d = t/SECS_IN_A_DAY;
	for (int i = 0; i < d; ++i)
		next_day();
	t /= SECS_IN_A_DAY;
	return *this = TimeWithDate(year, month, day, t);
}

TimeWithDate& TimeWithDate::operator-= (time_t t)
{
	t -= this->seconds();
	int d = 0;
	while(t < 0)
	{
		d++;
		t += SECS_IN_A_DAY;
	}
	for (int i = 0; i < d; ++i)
		previous_day();
	return *this = TimeWithDate(year, month, day, t);
}

TimeWithDate::time_t TimeWithDate::operator- (const TimeWithDate& t) const
{
	if (*this < t)
		return - (t - (*this));
	else if (*this > t)
	{
		TimeWithDate twd(t);
		int days = 0;
		while(!same_day(twd))
		{
			twd.next_day();
			days++;
		}
		return days*SECS_IN_A_DAY + this->seconds() - twd.seconds();
	}
	else
		return 0;
}

bool TimeWithDate::operator== (const TimeWithDate& t) const
{
	return year == t.year && month == t.month &&
		day == t.day && seconds() == t.seconds();
}

bool TimeWithDate::operator!= (const TimeWithDate& t) const
{
	return !(*this == t);
}

bool TimeWithDate::operator< (const TimeWithDate& t) const
{
	return year < t.year || month < t.month ||
		day < t.day || seconds() < t.seconds();
}

bool TimeWithDate::operator> (const TimeWithDate& t) const
{
	return year > t.year || month > t.month ||
		day > t.day || seconds() > t.seconds();
}

bool TimeWithDate::operator<= (const TimeWithDate& t) const
{
	return year <= t.year || month <= t.month ||
		day <= t.day || seconds() <= t.seconds();
}

bool TimeWithDate::operator>= (const TimeWithDate& t) const
{
	return year >= t.year || month >= t.month ||
		day >= t.day || seconds() >= t.seconds();
}


std::ostream& operator<< (std::ostream& out, const TimeWithDate& d)
{
	std::string m[] = {"Jan.", "Feb.", "Mar.", "Apr.", "May",
					"Jun.", "Jul.", "Aug.", "Sept.", "Oct.",
					"Nov.", "Dec."};
	out << d.hour << ":" << d.min << ":" << d.sec << ", "
		<< m[d.month-1] << " " << d.day << ", " << d.year;
	return out;
}

inline TimeWithDate::time_t TimeWithDate::seconds() const
{
	return hour*60*60 + min*60 + sec;
}

inline bool TimeWithDate::same_day(const TimeWithDate& t) const
{
	return year == t.year && month == t.month &&
		day == t.day;
}