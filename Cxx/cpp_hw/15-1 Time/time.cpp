#include "time.h"

Time& Time::operator= (const Time& t)
{
	this->hour = t.hour;
	this->min = t.min;
	this->sec = t.sec;
	return *this;
}

Time& Time::operator+= (const time_t sec)
{
	Time t(seconds()+sec);
	*this = t;
	return *this;
}

Time& Time::operator-= (const time_t sec)
{
	Time t(seconds()-sec);
	*this = t;
	return *this;
}

std::ostream& operator<< (std::ostream& out, const Time& t)
{
	out << t.hour << ":" << t.min << ":" << t.sec;
	return out;
}

inline Time::time_t Time::seconds() const
{
	return hour*60*60 + min*60 + sec;
}