#pragma once
#include <typeinfo>
#include <iostream>
#include <type_traits>
struct Cars{};
struct Shoes{};
struct People{};

template<class CategoryType, class ValueType, class DifferenceType, class PointerType, class ReferenceType>
struct TraitsTemplate
{
	typedef CategoryType my_category_traits;
	typedef ValueType my_value_traits;
	typedef DifferenceType my_difference_traits;
	typedef PointerType my_pointer_traits;
	typedef ReferenceType my_reference_traits;
};

template<class TraitsTemplate>
struct MyTraits
{
	typedef typename TraitsTemplate::my_category_traits my_category_traits;
	typedef typename TraitsTemplate::my_value_traits my_value_traits;
	typedef typename TraitsTemplate::my_difference_traits my_difference_traits;
	typedef typename TraitsTemplate::my_pointer_traits my_pointer_traits;
	typedef typename TraitsTemplate::my_reference_traits my_reference_traits;
};

template<class T>
struct MyTraits<T*>
{
	typedef People my_category_traits;
	typedef T  my_value_traits;
	typedef T* my_difference_traits;
	typedef T* my_pointer_traits;
	typedef T& my_reference_traits;
};

class A :public TraitsTemplate<Cars,A,A*,A*,A&>
{

};

class B :public TraitsTemplate<Shoes, B, B*, B*, B&>
{

};

void MyTraitsTest()
{
	A a;
	std::cout << typeid(a).name() << std::endl;
	MyTraits<A>::my_category_traits c;
	std::cout << typeid(c).name() << std::endl;
	std::cout << is_object(a)::value() << std::endl;
}