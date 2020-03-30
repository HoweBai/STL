#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void VectorTest()
{
	vector<int> vet;
	cout << vet.size() << " " << vet.capacity() << endl;
	for (int i = 0; i < 20; ++i)
	{
		vet.push_back(i);
		//cout << vet.size() << " " << vet.capacity() << endl;
	}
	auto itor = vet.begin();
	std::advance(itor, 5);
	cout << *itor << endl;
	vet.insert(itor, 100);
	cout << *itor << endl;
	//cout << vet.size() << " " << vet.capacity() << endl;
	
	std::copy(vet.begin(), vet.end(), std::ostream_iterator<int>{cout, " "});
}

void ListTest()
{
	list<int> lst;
	for (int i = 0; i <= 20; ++i)
	{
		lst.push_back(i);
	}
	copy(lst.begin(), lst.end(), std::ostream_iterator<int>{cout, " "});

	auto itor = find(lst.begin(), lst.end(), 10);
	auto temp_itor = itor;
	cout << *itor << endl;
	temp_itor = lst.insert(itor, 100);
	cout << *itor << endl;
	cout << *temp_itor << endl;
	cout << *(lst.erase(itor)) << endl;
	copy(lst.begin(), lst.end(), std::ostream_iterator<int>{cout, " "});
	cout << endl;
	list<int> insert_list{ 101,102,103 };
	auto ist = temp_itor;
	std::advance(ist, 1);
	lst.splice(temp_itor, lst, lst.begin(), temp_itor);
	copy(lst.begin(), lst.end(), std::ostream_iterator<int>{cout, " "});
}