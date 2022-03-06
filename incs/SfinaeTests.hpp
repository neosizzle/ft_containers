#include "Utils.hpp"
#include "TestUtils.hpp"

// template <class T>
// void foo(T) { 
//     std::cout << "T is not integral" << std::endl; 
// }

// template <class T, class = typename ft::enable_if<ft::is_integral<T>::value>::type>
// void foo(T) {
//     std::cout << "T is integral" << std::endl; 
// }

template <class T> typename ft::enable_if<ft::is_integral<T>::value, bool>::type foo(const T& obj)
{
	(void) obj;
	//T is an integral
    return true;
}

template <class T> typename ft::enable_if<!ft::is_integral<T>::value, bool>::type foo(const T& obj)
{
	(void) obj;
	//T is not an integral
	return false;
}

//Substitution failure is not an error
void	run_sfinae_tests()
{
	std::cout << "==========is_integral test==============\n";
	test_line("ft::is_integral<bool>::value ", true, bool(ft::is_integral<bool>::value));
	test_line("ft::is_integral<char>::value ", true, bool(ft::is_integral<char>::value));
	test_line("ft::is_integral<double>::value ", false, bool(ft::is_integral<double>::value));
	test_line("ft::is_integral<float>::value ", false, bool(ft::is_integral<float>::value));
	test_line("ft::is_integral<long>::value ", true, bool(ft::is_integral<long>::value));
	test_line("ft::is_integral<unsigned long>::value ", true, bool(ft::is_integral<unsigned long>::value));
	test_line("ft::is_integral<short>::value ", true, bool(ft::is_integral<short>::value));
	test_line("ft::is_integral<unsigned short>::value ", true, bool(ft::is_integral<unsigned short>::value));
	test_line("ft::is_integral<int>::value ", true, bool(ft::is_integral<int>::value));
	test_line("ft::is_integral<unsigned int>::value ", true, bool(ft::is_integral<unsigned int>::value));
	test_line("ft::is_integral<std::string>::value ", false, bool(ft::is_integral<std::string>::value));
	test_line("ft::is_integral<int	*>::value ", false, bool(ft::is_integral<int	*>::value));

	std::cout << "==========enable_if test==============\n";
	test_line("foo(12.23) ", false, foo(12.23));
	test_line("foo(12) ", true, foo(12));
	test_line("foo(hello) ", false, foo("hello"));
	test_line("foo(true) ", true, foo(true));
	test_line("foo('a') ", true, foo('a'));
	test_line("foo(-123) ", true, foo(-123));
	test_line("foo(12.34f) ", false, foo(12.34f));
}
