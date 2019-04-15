#ifndef _LEON_TIME_H
#define _LEON_TIME_H 1

#include <iostream>

class Time
{
public:
	typedef unsigned long time_t;
	typedef unsigned int hour_t;
	typedef unsigned int min_t;
	typedef unsigned int sec_t;

	Time(hour_t hour, min_t min, sec_t sec): hour(hour),
		min(min), sec(sec) {}
	explicit Time(time_t seconds): hour(seconds/3600),
		min((seconds%=3600)/60), sec(seconds%60) {}
	Time(const Time& t) {(*this) = t;}
	Time& operator= (const Time&);
	Time& operator++ () {return (*this) += 1;}
	Time& operator-- () {return (*this) -= 1;}
	Time operator++ (int) {
		Time t(*this);
		(*this) += 1;
		return t;
	}
	Time operator-- (int) {
		Time t(*this);
		(*this) -= 1;
		return t;
	}  

	Time& operator+= (const time_t);
	Time& operator-= (const time_t);

	time_t operator- (const Time& t) const {
		return this->seconds() - t.seconds();
	} 

	bool operator== (const Time& t) const {
		return this->seconds() == t.seconds();
	}
	bool operator!= (const Time& t) const {
		return this->seconds() != t.seconds();
	}
	bool operator< (const Time& t) const {
		return this->seconds() < t.seconds();
	} 
	bool operator> (const Time& t) const {
		return this->seconds() > t.seconds();
	}
	bool operator<= (const Time& t) const {
		return this->seconds() <= t.seconds();
	}
	bool operator>= (const Time& t) const {
		return this->seconds() >= t.seconds();
	}

private:
	inline time_t seconds() const;

	hour_t hour;
	min_t min;
	sec_t sec;

	friend std::ostream& operator<< (std::ostream&, const Time&);
};

extern std::ostream& operator<< (std::ostream&, const Time&);


#endif