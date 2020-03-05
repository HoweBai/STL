// ConfigTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <memory>
#include <string>

using namespace std;

/************************************************************************/
/* __STL_STATIC_TEMPLATE_MEMBER_BUG                                                                     */
/************************************************************************/
template<typename T>
class StaticMemberInTemplateClass {
public:
	static int _data;
};

template<typename T>
int StaticMemberInTemplateClass<T>::_data = 1;

void StaticMemberInTemplateClassTest()
{
	cout << StaticMemberInTemplateClass<int>::_data << endl;
	StaticMemberInTemplateClass<char>::_data = 2;
	cout << StaticMemberInTemplateClass<int>::_data << endl;
	cout << StaticMemberInTemplateClass<char>::_data << endl;
}

/************************************************************************/
/* __STL_CLASS_PARTIAL_SPECIALIZATION                                                                     */
/************************************************************************/
template<class I, class O>
struct ClassPartialSpecialization {
	ClassPartialSpecialization() { cout << "I, O" << endl; }
};

template<class I, class O>
struct ClassPartialSpecialization<I*, O*> {
	ClassPartialSpecialization() { cout << "I*, O*" << endl; }
};

template<class I, class O>
struct ClassPartialSpecialization<const I*, O*> {
	ClassPartialSpecialization<const I *, O *>() { cout << "const I*, O*" << endl; }
};

void ClassPartialSpecializationTest()
{
	ClassPartialSpecialization<int, char> obj1;
	ClassPartialSpecialization<int*, char*> obj2;
	ClassPartialSpecialization<const int*, char> obj3;
}

/************************************************************************/
/* __STL_FUNCTION_TMPL_PARTIAL_ORDER                                                                     */
/************************************************************************/
class alloc {
};

template<class T, class E = alloc>
class FunctionTmplPartialOrder {
public:
	void swap(FunctionTmplPartialOrder<T, E>&) {
		cout << "swap()" << endl;
	}
};

#ifdef __STL_FUNCTION_TMPL_ORDER
template<class T, class E>
inline void swap(FunctionTmplPartialOrder<T, E>& x, FunctionTmplPartialOrder<T, E>& y) {
	x.swap(y);
}
#endif // __STL_FUNCTION_TMPL_ORDER

void FunctionTmplPartialOrderTest() {
	FunctionTmplPartialOrder<int> x, y;
	swap(x, y);
}

/************************************************************************/
/* __STL_NULL_TMPL_ARGS                                                                     */
/************************************************************************/
template<class T, class Alloc = alloc, size_t BufSiz = 0>
class NullTmplArgs {
public:
	NullTmplArgs() { cout << "NullTmplArgs" << endl; }
};

template<class T, class NTA = NullTmplArgs<T>>
class NullTmplArgsStack {
	friend bool operator ==  (const NullTmplArgs<T>&, const NullTmplArgs<T>&);
};

template<class T, class E>
bool operator ==(const NullTmplArgs<T, E>& x, const NullTmplArgs<T, E>& y) {
	cout << "operator ==" << endl;
	return true;
}

void NullTmplArgsTest()
{
	NullTmplArgs<int> x;
	NullTmplArgs<int> y;
	NullTmplArgs<char> z;

	cout << (x == y) << endl;
	//cout << (x == z) << endl;
}

/************************************************************************/
/* __STL_TEMPLATE_NULL                                                                     */
/************************************************************************/

#define __STL_TEMPLATE_NULL template<> /*blank*/

template<class T> struct TemplateNull {
	void operator()() { cout << "operator(T)" << endl; }
};

__STL_TEMPLATE_NULL struct TemplateNull<char> {
	void operator()() { cout << "operator(char)" << endl; }
};

__STL_TEMPLATE_NULL struct TemplateNull<unsigned char> {
	void operator()() { cout << "operator(unsigned char)" << endl; }
};

void TemplateNullTest() {
	TemplateNull<int> t1;
	TemplateNull<char> t2;
	TemplateNull<unsigned char> t3;

	t1();
	t2();
	t3();
}

/************************************************************************/
/* 临时对象                                                                     */
/************************************************************************/
template<class T>
class TempObj {
public:
	void operator()(T& i) { cout << i << ";"; }
};

void TempObjTest()
{
	//vector<int> iv = { 1,2,3,4,5 };
	int ia[] = { 1,2,3,4,5,6 };
	vector<int> iv(ia, ia + 6);
	for_each(iv.begin(), iv.end(), TempObj<int>());
	//for_each(iv.begin(), iv.end(), [](int i) { cout << i << ","; });
}

/************************************************************************/
/* set_new_handler                                                                     */
/************************************************************************/
void NewHandler()
{
	cout << "This is a set_new_handler test" << endl;
	//exit(0);
}

void NewHandlerTest()
{
	std::set_new_handler(NewHandler);
	int* i = new int[1024ll *1024ll * 1024ll * 2ll];
	cout << i << endl;
	delete[] i;
}

/************************************************************************/
/* Unintialized                                                                     */
/************************************************************************/
void UninitializedTest()
{
	std::vector<int> veca{ 1,2,3,4,5,6,7,8,9 };
	std::vector<int> vecb;

	//std::copy(veca.begin(), veca.end(), std::back_inserter(vecb));
	//uninitialized_copy(veca.begin(), veca.end(), vecb);
	//std::copy(vecb.begin(), vecb.end(), std::ostream_iterator<int>{ std::cout, " "});
}

/************************************************************************/
/* private member variable                                                                     */
/************************************************************************/
class PrivateMemberVariable1 {
private:
	int num;
public:
	PrivateMemberVariable1() :num(100) {}
};

class PrivateMemberVariable {
private:
	int num;
public:
	explicit PrivateMemberVariable():num(10){}
	/*PrivateMemberVariable(PrivateMemberVariable& n):num(n.num){
		cout << "PrivateMemberVariable construct" << endl;
	}*/
	PrivateMemberVariable(PrivateMemberVariable& n, PrivateMemberVariable& m) {
		num = n.num + m.num;
		cout << "PrivateMemberVariable construct" << endl;
	}
	void show(PrivateMemberVariable n){
		cout << "PrivateMemberVariable show" << n.num << endl;
	}
};


void PrivateMemberVariableTest()
{
	PrivateMemberVariable pmv1,pmv2;
	PrivateMemberVariable pmv(pmv1,pmv2);
	pmv.show(pmv1);
}

/************************************************************************/
/* auto_ptr test                                                                     */
/************************************************************************/
void AutoPtrTest()
{
	//auto_ptr<string> ps(new string("Humphrey Bacon"));
	//cout << *ps << endl;
	//cout << ps->size() << endl;
	auto_ptr<char> ps4char(new char[6]{"12345"});
	cout << *ps4char << endl;
	//cout << *(ps4char++) << endl;
	auto_ptr<string> ps = ps4char;
}


/************************************************************************/
/* private constructor                                                                     */
/************************************************************************/
class PrivateConstructor
{
	friend class CreatePrivate;

private:
	PrivateConstructor() { cout << "PrivateConstructor construct" << endl; }
	PrivateConstructor(const PrivateConstructor&){ cout << "PrivateConstructor copy construct" << endl; }
	~PrivateConstructor(){ cout << "PrivateConstructor destruct" << endl; }
};

class CreatePrivate
{
public:
	CreatePrivate() { pc_ = new PrivateConstructor(); }
	~CreatePrivate() { if (pc_) delete pc_; }
	PrivateConstructor& operator()() { return *pc_; }
	void show() { cout << "CreatePrivate show" << endl; }
private:
	PrivateConstructor *pc_;
};

void CreatePrivateTest()
{
	CreatePrivate().show();
	getchar();
}
/************************************************************************/
/* operator ->                                                                     */
/************************************************************************/
class OperatorOpe {
public:
	explicit OperatorOpe(CreatePrivate* cp) :cp_(cp) {};
	CreatePrivate* operator->() {	return cp_;	}
	~OperatorOpe() { if (cp_) delete cp_; }
private:
	CreatePrivate* cp_;
};

void OperatorOpeTest() {
	OperatorOpe oo(new CreatePrivate());
	oo->show();
}


/************************************************************************/
/* Main                                                                     */
/************************************************************************/
int main()
{
	//StaticMemberInTemplateClassTest();
	//ClassPartialSpecializationTest();
	//FunctionTmplPartialOrderTest();
	//NullTmplArgsTest();
	//TemplateNullTest();
	//TempObjTest();
	//NewHandlerTest();
	//UninitializedTest();
	//PrivateMemberVariableTest();
	//AutoPtrTest();
	//CreatePrivateTest();
	OperatorOpeTest();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
