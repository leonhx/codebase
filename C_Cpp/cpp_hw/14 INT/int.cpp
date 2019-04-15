#include "int.h"
#include <cmath>
#include <cstring>
#include <stdexcept>

Int::Int(const Int& x)
{
	positive = x.positive;
	len = x.len;
	cap = 2*len;
	bits = new signed char[cap];
	for (int i = 0; i < len; ++i)
		bits[i] = x.bits[i];
}

Int::Int(long long x)
{
	if (x == 0)
	{
		len = 0;
		cap = 2;
		bits = new signed char[cap];
		positive = true;
	}
	else
	{
		if (x < 0)
		{
			positive = false;
			x = -x;
		}
		else
			positive = true;
		cap = 2*ceil(log10(x));
		bits = new signed char[cap];
	
		len = 0;
		while (x)
		{
			bits[len++] = x%10;
			x /= 10;
		}
	}
}

Int::Int(const std::string& s)
{
	int l = s.size();
	int i = 0;
	if (l == 0)
	{
		len = 0;
		cap = 2;
		positive = true;
		bits = new signed char[cap];
	}
	else
	{
		if (s[i] == '-')
		{
			positive = false;
			i++;
		}
		else
		{
			positive = true;
			if (s[i] == '+')
				i++;
		}
		while (i < l && s[i] == '0')
			i++;
		if (i == l)
		{
			len = 0;
			cap = 2;
			positive = true;
			bits = new signed char[cap];
		}
		else
		{
			len = l - i;
			cap = 2*len;
			bits = new signed char[cap];
			for (int i = 0; i < len; ++i)
				bits[i] = s[l-1-i] - '0';
		}
	}
}

Int& Int::operator= (const Int& x)
{
	positive = x.positive;
	len = x.len;
	if (len == 0)
		cap = 2;
	else
		cap = 2*len;
	bits = new signed char[cap];
	for (int i = 0; i < len; ++i)
		bits[i] = x.bits[i];
	return *this;
}

Int Int::operator- () const
{
	if (this->len == 0)
		return (*this);
	Int i(*this);
	i.positive ^= true;
	return i;
}

Int operator+ (const Int& x1, const Int& x2)
{
	if (x1.len == 0)
		return x2;
	if (x2.len == 0)
		return x1;
	if (x1.positive && x2.positive)
	{
		Int x;
		int c = 0;
		int i = 0;
		for (; i < x1.len && i < x2.len; ++i)
		{
			int t = x1.bits[i] + x2.bits[i] + c;
			c = t/10;
			x.bits[x.len++] = t%10;
			x.fit();
		}
		if (x1.len > x2.len)
			for (; i < x1.len; ++i)
			{
				int t = x1.bits[i] + c;
				c = t/10;
				x.bits[x.len++] = t%10;
				x.fit();
			}
		else if (x1.len < x2.len)
			for (; i < x2.len; ++i)
			{
				int t = x2.bits[i] + c;
				c = t/10;
				x.bits[x.len++] = t%10;
				x.fit();
			}
		if (c != 0)
		{
			x.bits[x.len++] = c;
			x.fit();
		}
		return x;
	}
	else if (x1.positive && !x2.positive)
		return x1-(-x2);
	else if (!x1.positive && x2.positive)
		return x2-(-x1);
	else
		return -((-x1)+(-x2));
}

Int operator- (const Int& x1, const Int& x2)
{
	if (x1.len == 0)
		return -x2;
	if (x2.len == 0)
		return x1;
	if (x1 == x2)
		return 0;
	if (x1.positive && x2.positive)
	{
		if (x1 > x2)
		{
			Int x;
			int c = 0;
			int i = 0;
			for (; i < x1.len && i < x2.len; ++i)
			{
				int t = x1.bits[i] - x2.bits[i] + c;
				c = floor(t/10.0);
				x.bits[x.len++] = t-c*10;
				x.fit();
			}
			if (x1.len > x2.len)
				for (; i < x1.len; ++i)
				{
					int t = x1.bits[i] + c;
					c = floor(t/10.0);
					x.bits[x.len++] = t-c*10;
					x.fit();
				}
			else if (x1.len < x2.len)
				for (; i < x2.len; ++i)
				{
					int t = x2.bits[i] + c;
					c = floor(t/10.0);
					x.bits[x.len++] = t-c*10;
					x.fit();
				}
			if (c != 0)
			{
				std::cout << "Error: carriage remains" << std::endl;
			}
			while(x.len > 0 && x.bits[x.len-1] == 0)
				x.len--;
			return x;
		}
		else
			return -(x2-x1);
	}
	else if (x1.positive && !x2.positive)
		return x1+(-x2);
	else if (!x1.positive && x2.positive)
		return -(x2+(-x1));
	else
		return -((-x1)-(-x2));
}

Int operator* (const Int& x1, const Int& x2)
{
	if (x1.len == 0 || x2.len == 0)
		return 0;
	bool p = !(x1.positive^x2.positive);
	Int a(x1.positive?x1:-x1);
	Int b(x2.positive?x2:-x2);
	Int r;
	if (a >= b)
		while(b-- > 0)
			r += a;
	else
		while(a-- > 0)
			r += b;
	r.positive = p;
	return r;
}

Int operator/ (const Int& x1, const Int& x2)
{
	if (x2.len == 0)
		throw std::runtime_error("div-by-zero: the second paramter is 0");
	if (x1.len == 0)
		return 0;
	bool p = !(x1.positive^x2.positive);
	Int a(x1.positive?x1:-x1);
	Int b(x2.positive?x2:-x2);
	if (a < b)
		return 0;
	Int r;
	while((a-=b) >= 0)
		r++;
	r.positive = p;
	return r;
}

Int operator% (const Int& x1, const Int& x2)
{
	if (x2.len == 0)
		throw std::runtime_error("div-by-zero: the second paramter is 0");
	if (x1.len == 0)
		return 0;
	Int a(x1.positive?x1:-x1);
	Int b(x2.positive?x2:-x2);
	if (a > b)
		while(a >= b)
			a -= b;
	a.positive = x1.positive;
	return a;
}

bool operator== (const Int& x1, const Int& x2)
{
	if (x1.len != x2.len)
		return false;
	if (x1.len == 0 && x2.len == 0)
		return true;
	if (x1.positive != x2.positive)
		return false;
	for (int i = 0; i < x1.len; ++i)
		if (x1.bits[i] != x2.bits[i])
			return false;
	return true;
}

bool operator!= (const Int& x1, const Int& x2)
{
	if (x1.len != x2.len)
		return true;
	if (x1.len == 0 && x2.len == 0)
		return false;
	if (x1.positive != x2.positive)
		return true;
	for (int i = 0; i < x1.len; ++i)
		if (x1.bits[i] != x2.bits[i])
			return true;
	return false;
}

bool operator< (const Int& x1, const Int& x2)
{
	if (x1.positive ^ x2.positive)
		return x2.positive;
	else
	{
		bool ab = true;// whether abs(x1) < abs(x2)
		if (x1.len > x2.len)
			ab = false;
		else if (x1.len == x2.len)
		{
			if (x1.len == 0)
				return false;
			int i = x1.len-1;
			while(i >=0 && x1.bits[i] == x2.bits[i])
				i--;
			if (i < 0)
				return false;
			if(x1.bits[i] > x2.bits[i])
				ab = false;
		}
		return !(ab ^ x1.positive);
	}
}

bool operator> (const Int& x1, const Int& x2)
{
	if (x1.positive ^ x2.positive)
		return x1.positive;
	else
	{
		bool ab = true;// whether abs(x1) > abs(x2)
		if (x1.len < x2.len)
			ab = false;
		else if (x1.len == x2.len)
		{
			if (x1.len == 0)
				return false;
			int i = x1.len-1;
			while(i >=0 && x1.bits[i] == x2.bits[i])
				i--;
			if (i < 0)
				return false;
			if(x1.bits[i] < x2.bits[i])
				ab = false;
		}
		return !(ab ^ x1.positive);
	}
}

bool operator<= (const Int& x1, const Int& x2)
{
	if (x1.len == x2.len && x1.len == 0)
		return true;
	if (x1.positive ^ x2.positive)
		return x2.positive;
	else
	{
		bool ab = true;// whether abs(x1) <= abs(x2)
		if (x1.len > x2.len)
			ab = false;
		else if (x1.len == x2.len)
		{
			int i = x1.len-1;
			while(i >=0 && x1.bits[i] == x2.bits[i])
				i--;
			if (i < 0)
				return true;
			if(x1.bits[i] > x2.bits[i])
				ab = false;
		}
		return !(ab ^ x1.positive);
	}
}

bool operator>= (const Int& x1, const Int& x2)
{
	if (x1.len == x2.len && x1.len == 0)
		return true;
	if (x1.positive ^ x2.positive)
		return x1.positive;
	else
	{
		bool ab = true;// whether abs(x1) >= abs(x2)
		if (x1.len < x2.len)
			ab = false;
		else if (x1.len == x2.len)
		{
			int i = x1.len-1;
			while(i >=0 && x1.bits[i] == x2.bits[i])
				i--;
			if (i < 0)
				return true;
			if(x1.bits[i] < x2.bits[i])
				ab = false;
		}
		return !(ab ^ x1.positive);
	}
}

inline int Int::resize(size_t size)
{
	if (size < len)
		return -1;
	signed char *tmp = bits;
	bits = new signed char[size];
	if (!bits)
		return -1;
	for (int i = 0; i < len; ++i)
	{
		bits[i] = tmp[i];
	}
	delete []tmp;
	cap = size;
	return size;
}

void Int::fit()
{
	if (len == cap)
		resize(2*cap);
	else if (len > 0 && len == cap/4)
		resize(cap/2);
}

std::ostream& operator<< (std::ostream& out, const Int& x)
{
	if (x.len == 0)
		out << 0;
	else
	{
		if (!x.positive)
			out << '-';
		int i = x.len-1;
		while (i >= 0)
			out << int(x.bits[i--]);
	}
	return out;
}

std::istream& operator>> (std::istream& in, Int& x)
{
	std::string s;
	in >> s;
	x = Int(s);
	return in;
}