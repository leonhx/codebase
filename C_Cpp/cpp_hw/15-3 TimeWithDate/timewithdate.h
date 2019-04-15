#ifndef _LEON_TimeWithDate_WITH_DATE_H
#define _LEON_TimeWithDate_WITH_DATE_H 1

#include <iostream>

class TimeWithDate
{
public:
	typedef long long time_t;

	TimeWithDate(int year, int month, int day, int hour,
		int min, int sec): year(year), month(month), day(day),
		hour(hour), min(min), sec(sec) {}
	TimeWithDate(int year, int month, int day, time_t secs):
		year(year), month(month), day(day), hour(secs/3600),
		min((secs%=3600)/60), sec(secs%60) {}
	TimeWithDate(const TimeWithDate& t) {(*this) = t;}

	TimeWithDate& operator= (const TimeWithDate&);

	void next_day();
	void previous_day();

	TimeWithDate& operator+= (time_t);
	TimeWithDate& operator-= (time_t);

	time_t operator- (const TimeWithDate& t) const;

	bool operator== (const TimeWithDate& t) const;
	bool operator!= (const TimeWithDate& t) const;
	bool operator< (const TimeWithDate& t) const;
	bool operator> (const TimeWithDate& t) const;
	bool operator<= (const TimeWithDate& t) const;
	bool operator>= (const TimeWithDate& t) const;

private:
	inline time_t seconds() const;
	inline bool same_day(const TimeWithDate& t) const;

	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	friend std::ostream& operator<< (std::ostream&, const TimeWithDate&);
};


extern std::ostream& operator<< (std::ostream&, const TimeWithDate&);

#endif