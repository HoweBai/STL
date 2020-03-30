// Allocator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory>
#include  <iostream>
#include <vector>

using namespace std;

class A
{
public:
	void show()
	{
		cout << "A::show()" << endl;
	}
	~A() { std::cout << "A destruct" << std::endl; }
};

int main()
{
	A x;
	vector<A> a(10);
	auto_ptr<A> b;
	auto_ptr<A> c;
	b.reset(c.release());
	uninitialized_fill(a.begin(), a.end(), x);

	b->show();
	return 0;
}

