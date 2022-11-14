#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <iostream>
#include "unique.hpp"

template <typename T>
struct X
{
	T m_x;
	X ( const T & x ) : m_x(x){}
	bool operator < ( const X & rhs ) const
	{
		return m_x < rhs.m_x;
	}
};

template <typename T1, typename T2>
struct Y
{
	T1 m_x;
	T2 m_y;
	Y ( const T1 & x, const T2 & y ) : m_x(x), m_y(y){}
	bool operator < ( const Y & rhs ) const
	{
		return std::tie(m_x, m_y) < std::tie(rhs.m_x, rhs.m_y);
	}
};

template <typename T, typename Comp >
bool test ( std::vector<T> c1, std::vector<T> c2, const Comp & cmp  )
{
	std::sort(c1.begin(), c1.end());
	std::sort(c2.begin(), c2.end());
	return std::equal(c1.begin(), c1.end(), c2.begin(), c2.end(), cmp);
}

int main ( void )
{
	auto compare = [](auto & lhs, auto & rhs){ return !(lhs<rhs) && !(rhs<lhs); };
	std::vector<int> v0;
	assert ( test(v0, unique_elements(v0), compare) );

	std::list<int> l0;
	assert ( test(v0, unique_elements(l0), compare) );

	std::vector v1 {1,2,3,4,5};
	assert ( test(v1, unique_elements(v1), compare) );

	std::vector v2 {5,4,3,2,1};
	assert ( test(unique_elements(v2), v2, compare) );

	std::vector v3 {1,1,5,3,2,5,1,3,4,2};
	assert ( test(unique_elements(v3), {1,2,3,4,5}, compare) );

	std::vector v4 {8, 7, 5, 5, 4, 5, 3, 2, 1};
	assert ( test(unique_elements(v4), {1,2,3,4,5,7,8}, compare) );

	std::list l1(v4.begin(), v4.end());
	assert ( test(unique_elements(l1), {1,2,3,4,5,7,8}, compare) );

	
	std::vector<std::string> v5 {"a", "b", "c", "d", "ee", "f", "f", "ee", "a", "aa", "d"};
	assert ( test(unique_elements(v5), {"a", "b", "c", "d", "ee", "f", "aa"}, compare) );
	
	
	std::vector<X<int>> v6 {1, 2, 3, 4, 5};
	assert ( test(unique_elements(v6), v6, compare) );
	
	
	std::vector<X<int>> v7 = v6;
	v7.emplace_back(1); v7.emplace_back(5); v7.emplace_back(5); v7.emplace_back(1);
	assert ( test(unique_elements(v7), v6, compare) );
	
	
	std::vector<X<std::string>> v8 {{"a"}, {"b"}, {"c"}, {"d"}, {"ee"}, {"f"}, {"aa"}};
	assert ( test(unique_elements(v8), v8, compare) );

	std::vector<X<std::string>> v9 = v8;
	v9.emplace_back("ee"); v9.emplace_back("aa"); v9.emplace_back("f"); v9.emplace_back("c");
	assert ( test(unique_elements(v9), v8, compare) );
	
	
	std::vector<Y<int, std::string>> v10 = {{1,"a"}, {2,"b"}, {3,"c"}};
	assert ( test(unique_elements(v10), v10, compare) ); 

	using Y_inst = Y<int, std::string>;
	auto compare2 = [](const Y_inst & lhs, const Y_inst & rhs){
		return lhs.m_x < rhs.m_x;
	};
	auto compare2_equal = [&](const auto & l, const auto & r ) { return !compare2(l,r) && !compare2(r,l); };
	assert ( test(unique_elements(v10, compare2), v10, compare2_equal) );
	
	
	auto v11 = v10; v11.emplace_back(3, "c");
	assert ( test(unique_elements(v11, compare2), v10, compare2_equal) );
	
	return 0;
}
