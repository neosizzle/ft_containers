#ifndef __TESTUTILS__H_
#define __TESTUTILS__H_
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#include <iostream>
#include <vector>

void	print_fail_msg(std::string cmd, std::string msg)
{
	std::cout << RED << cmd << msg << std::endl;
}

template <class T1>
void	test_line(std::string cmd, T1 expected, T1 actual)
{
	if (expected == actual)
		std::cout << GREEN << "[PASS] Value match		" << cmd << RESET << std::endl;
	else
		std::cout << RED << "[FAIL] expected: " << expected << ". actual: " << actual << "	" << cmd << RESET << std::endl;
}

template <class T1, class T2>
void	test_line_diffclass(std::string cmd, T1 expected, T2 actual)
{
	if (expected == actual)
		std::cout << GREEN << "[PASS] Value match		" << cmd << RESET << std::endl;
	else
		print_fail_msg(cmd, "[FAIL] Different output");
}

void	test_line_operation_success(std::string cmd, int should_success)
{
	if (should_success)
		std::cout << GREEN << "[PASS] Operation success	" << cmd << RESET << std::endl;
	else
		print_fail_msg(cmd, "[FAIL] Operation should fail");
}

void	test_line_operation_fail(std::string cmd, int should_fail)
{
	if (should_fail)
		std::cout << GREEN << "[PASS] Operation failed successfully	" << cmd << RESET << std::endl;
	else
		print_fail_msg(cmd, "[FAIL] Operation did not fail");
}

void	compare_time (std::string cmd, clock_t builtin_time, clock_t my_time)
{
 
	if (builtin_time == 0)
	{
		if (my_time > 20)
			std::cout << RED << "[FAIL] Time test exceeded		" << cmd << " - builtin_time : " << builtin_time << " my_time : " << my_time <<  RESET << std::endl;
		else
			std::cout << GREEN << "[PASS] Time test passed		" << cmd << RESET << std::endl;
	}
	else if (my_time / builtin_time > 20)
			std::cout << RED << "[FAIL] Time test exceeded		" << cmd << " - builtin_time : " << builtin_time << " my_time : " << my_time <<  RESET << std::endl;
	else
		std::cout << GREEN << "[PASS] Time test passed		" << cmd << RESET << std::endl;
}

class CustomClass
{
	public:
		int	x;
		int	y;
};

std::ostream&	operator<<(std::ostream &os, CustomClass &other)
{
	os << other.x << ", " << other.y << "\n";
	return os;
}

#endif  //!__TESTUTILS__H
