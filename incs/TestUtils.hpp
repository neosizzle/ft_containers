#include "main.hpp"
#include <typeinfo>

template <class T1>
void	test_line(std::string cmd, T1 expected, T1 actual)
{
	if (expected == actual)
		std::cout << GREEN << cmd << " [PASS]" << RESET << std::endl;
	else
		std::cout << RED << cmd << " [FAIL] expected " << expected << " actual " << actual << RESET << std::endl;
}

template <class T1, class T2>
void	test_line_diffclass(std::string cmd, T1 expected, T2 actual)
{
	//this is assuming both types have operator ==
	if (expected == actual)
		std::cout << GREEN << cmd << " [PASS]" << RESET << std::endl;
	else
		std::cout << RED << cmd << " [FAIL] Different output" << std::endl;
}