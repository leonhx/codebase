#ifndef _LEON_SET_H
#define _LEON_SET_H 1

#include <iostream>

class Set
{
public:
	Set(): set(new int[1]), len(0), cap(1){};
	~Set()
	{
		delete []set;
	}
	Set(const Set&);
	Set& operator+= (int);
	Set& operator-= (int);
	bool operator!= (const Set& s) {return !(*this == s);} 
	bool operator== (const Set& s) {return (*this <= s) && (s <= *this);}
	bool operator<= (const Set&) const;
private:
	bool has(int) const;
	inline int resize(size_t size);
	int *set;
	int len;
	int cap;

	friend std::ostream& operator<< (std::ostream&, const Set&);
	friend Set operator- (const Set&, const Set&);
	friend Set operator& (const Set&, const Set&);
	friend Set operator| (const Set&, const Set&);
};

extern std::ostream& operator<< (std::ostream&, const Set&);
extern Set operator- (const Set& s1, const Set& s2);
extern Set operator& (const Set& s1, const Set& s2);
extern Set operator| (const Set& s1, const Set& s2);

#endif