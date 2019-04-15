#include "linearlist.h"

inline int LinearList::resize(size_t size)
{
	if (size < len)
		return -1;
	int *tmp = list;
	list = new int[size];
	if (!list)
		return -1;
	for (int i = 0; i < len; ++i)
	{
		list[i] = tmp[i];
	}
	delete []tmp;
	cap = size;
	return size;
}

bool LinearList::insert(int x, int pos)
{
	if (pos > len || pos < 0)
		return false;
	if (pos == len)
	{
		list[pos] = x;
		len += 1;
	}
	else
	{
		for (int i = len; i > pos; --i)
		{
			list[i] = list[i-1];
		}
		list[pos] = x;
		len += 1;
	}

	if (len == cap)
		if(resize(2*cap) == -1)
			return false;
	return true;
}

bool LinearList::remove(int &x, int pos)
{
	if (pos > len || pos < 1)
		return false;
	x = element(pos);
	for (int i = pos; i < len; ++i)
	{
		list[i-1] = list[i];
	}
	len -= 1;

	if (len > 0 && len == cap/4)
		if(resize(cap/2) == -1)
			return false;
	return true;
}

int LinearList::search(int x) const
{
	for (int i = 1; i <= len; ++i)
	{
		if (x == element(i))
			return i;
	}
	return 0;
}

std::ostream& operator<< (std::ostream& out, const LinearList& ll)
{
	out << "[";
	if (ll.length() > 1)
		out << ll.element(1);
	for (int i = 2; i <= ll.len; ++i)
	{
		out << ", " << ll.element(i);
	}
	out << "]";
	return out;
}