#ifndef _LEON_LINEAR_LIST_H
#define _LEON_LINEAR_LIST_H 1

#include <iostream>

class LinearList
{
public:
	LinearList():list(new int[1]), len(0), cap(1){}
	~LinearList()
	{
		delete list;
	}
	bool insert(int x, int pos);//在位置pos之后插入一个元素x。
								//pos为0时，在第一个元素之前插入。
								//操作成功时返回true，否则返回false。
	bool remove(int &x, int pos);//删除位置pos处的元素。
								//操作成功时返回true，否则返回false。
	int element(int pos) const
	{
		return list[pos-1];
	}//返回位置pos处的元素。
	int search(int x) const;//查找值为x的元素，返回元素的位置
							//（第一个元素的位置为1）。未找到时返回0。
	int length() const
	{
		return len;
	}

private:
	LinearList(const LinearList&){}
	LinearList& operator= (const LinearList& ll){return *this;}
	friend std::ostream& operator<< (std::ostream&, const LinearList&);
	inline int resize(size_t size);
	int *list;
	int len;
	int cap;
};



extern std::ostream& operator<< (std::ostream& out, const LinearList& ll);

#endif // _LEON_LINEAR_LIST_H
