#ifndef _LEON_INT_H
#define _LEON_INT_H 1

#include <iostream>
#include <string>

class Int
{
public:
	Int(): positive(true),
		 bits(new signed char[2]), len(0), cap(2){}
	~Int() {delete []bits;}
	Int(const Int&);
	Int(long long x);
	Int(const std::string& s);
	Int& operator= (const Int&);
	Int& operator++ () {return (*this) = (*this)+1;} 
	Int& operator-- () {return (*this) = (*this)-1;}
	Int operator++ (int) {
		Int t(*this);
		(*this) = (*this)+1;
		return t;
	}
	Int operator-- (int) {
		Int t(*this);
		(*this) = (*this)-1;
		return t;
	}
	Int operator- () const;
	void fit();

private:
	bool positive;
	signed char *bits;
	int len;
	int cap;

	inline int resize(size_t size);

	friend std::ostream& operator<< (std::ostream&, const Int&);
	friend std::istream& operator>> (std::istream&, Int&);
	friend inline Int& operator+= (Int&, const Int&);
	friend inline Int& operator-= (Int&, const Int&);
	friend inline Int& operator*= (Int&, const Int&);
	friend inline Int& operator/= (Int&, const Int&);
	friend inline Int& operator%= (Int&, const Int&);
	friend Int operator+ (const Int&, const Int&);
	friend Int operator- (const Int&, const Int&);
	friend Int operator* (const Int&, const Int&);
	friend Int operator/ (const Int&, const Int&);
	friend Int operator% (const Int&, const Int&);
	friend bool operator== (const Int&, const Int&);
	friend bool operator!= (const Int&, const Int&);
	friend bool operator< (const Int&, const Int&);
	friend bool operator> (const Int&, const Int&);
	friend bool operator<= (const Int&, const Int&);
	friend bool operator>= (const Int&, const Int&);
};

extern std::ostream& operator<< (std::ostream&, const Int&);
extern std::istream& operator>> (std::istream&, Int&);
extern Int operator+ (const Int&, const Int&);
extern Int operator- (const Int&, const Int&);
extern Int operator* (const Int&, const Int&);
extern Int operator/ (const Int&, const Int&);
extern Int operator% (const Int&, const Int&);
extern bool operator== (const Int&, const Int&);
extern bool operator!= (const Int&, const Int&);
extern bool operator< (const Int&, const Int&);
extern bool operator> (const Int&, const Int&);
extern bool operator<= (const Int&, const Int&);
extern bool operator>= (const Int&, const Int&);


inline Int& operator+= (Int& x1, const Int& x2) {
	return x1 = x1 + x2;
}
inline Int& operator-= (Int& x1, const Int& x2) {
	return x1 = x1 - x2;
}
inline Int& operator*= (Int& x1, const Int& x2) {
	return x1 = x1 * x2;
}
inline Int& operator/= (Int& x1, const Int& x2) {
	return x1 = x1 / x2;
}
inline Int& operator%= (Int& x1, const Int& x2) {
	return x1 = x1 % x2;
}


#endif