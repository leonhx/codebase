#include "set.h"

Set::Set(const Set& s)
{
	len = s.len;
	cap = 2 * len;
	set = new int[cap];
	for (int i = 0; i < len; ++i)
		set[i] = s.set[i];
}

inline int Set::resize(size_t size)
{
	if (size < len)
		return -1;
	int *tmp = set;
	set = new int[size];
	if (!set)
		return -1;
	for (int i = 0; i < len; ++i)
	{
		set[i] = tmp[i];
	}
	delete []tmp;
	cap = size;
	return size;
}

std::ostream& operator<< (std::ostream& out, const Set& set)
{
	out << "[";
	if (set.len > 1)
		out << set.set[0];
	for (int i = 1; i < set.len; ++i)
	{
		out << ", " << set.set[i];
	}
	out << "]";
	return out;
}

Set& Set::operator+= (int x)
{
	if (has(x))
		return *this;
	set[len] = x;
	len++;
	if (len == cap)
		resize(2*cap);
	return *this;
}

Set& Set::operator-= (int x)
{
	for (int i = 0; i < len; ++i)
	{
		if (set[i] == x)
		{
			len--;
			for (int j = i; j < len; ++j)
				set[j] = set[j+1];
			break;
		}
	}
	if (len > 0 && len == cap/4)
		resize(cap/2);
	return *this;
}

bool Set::has(int x) const
{
	for (int i = 0; i < len; ++i)
		if (set[i] == x)
			return true;
	return false;
}

Set operator- (const Set& s1, const Set& s2)
{
	Set s(s1);
	for (int i = 0; i < s2.len; ++i)
		s -= s2.set[i];
	return s;
}

Set operator& (const Set& s1, const Set& s2)
{
	Set s;
	for (int i = 0; i < s1.len; ++i)
		if (s2.has(s1.set[i]))
			s += s1.set[i];

	return s;
}

Set operator| (const Set& s1, const Set& s2)
{
	Set s(s1);
	for (int i = 0; i < s2.len; ++i)
		if (!s.has(s2.set[i]))
			s += s2.set[i];

	return s;
}

bool Set::operator<= (const Set& s1) const
{
	for (int i = 0; i < len; ++i)
		if (!s1.has(set[i]))
			return false;
	return true;
}
