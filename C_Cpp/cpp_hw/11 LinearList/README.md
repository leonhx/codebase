LinearList
=========

定义一个由int型元素所构成的线性表类LinearList，它有下面的成员函数：
	bool insert(int x, int pos);//在位置pos之后插入一个元素x。
								//pos为0时，在第一个元素之前插入。
								//操作成功时返回true，否则返回false。
	bool remove(int &x, int pos);//删除位置pos处的元素。
								//操作成功时返回true，否则返回false。
	int element(int pos) const;//返回位置pos处的元素。
	int search(int x) const;//查找值为x的元素，返回元素的位置
							//（第一个元素的位置为1）。未找到时返回0。
	int length() const;//返回元素个数。