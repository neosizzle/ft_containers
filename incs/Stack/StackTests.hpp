#include "Stack.hpp"
#include "Utils.hpp"
#include <stack>
#include <time.h>
#include "TestUtils.hpp"
#include <deque>

template <class T1>
void	test_init_stack(std::string message, int will_throw, T1 key_type)
{
	(void) key_type;
	try
	{
		std::stack<T1> builtin;
		ft::Stack<T1> mine;
		if (will_throw)
			std::cout << RED << message << " [FAIL] Should throw error" << RESET << std::endl;
		else
			std::cout << GREEN  << "[PASS] Initialization successful	" <<  message << RESET << std::endl;
	}
	catch (const std::exception& )
	{
		if (will_throw)
			std::cout << GREEN  << "[PASS] should throw error	" <<  message << RESET << std::endl;
		else
			std::cout << RED << message << " [FAIL] Initialization failed " << RESET << std::endl;
	}
}

void	run_stack_tests()
{
	std::cout << "==========Initialization test==============\n";
	CustomClass cc;
	std::stack<int>	init_vect;

	cc.x = 1;
	cc.y = 2;
	test_init_set("ft_stack::<int>", 0, 0);
	test_init_set("ft_stack::<double>", 0, 1.1);
	test_init_set("ft_stack::<std::string>", 0, std::string("foo"));
	test_init_set("ft_stack::<NULL>", 0, NULL);
	test_init_set("ft_stack::<CustomClass>", 0, cc);
	test_init_set("ft_stack::<std::stack>", 0, init_vect);

	std::cout << "==========Modifier, Iterator and operation test==============\n";
	std::stack<int> builtin;
	ft::Stack<int> mine;

	for (int i = 0; i < 100; ++i)
	{
		int result = 1 + (rand() % 100);
		
		builtin.push(result);
		mine.push(result);
	}
	test_line_operation_success("mine.push() multiple", 1);
	for (int i = 0; i < 100; ++i)
	{
		std::string	msg;

		msg.append("mine.top() == builtin.top() at element ");
		msg.append(SSTR(i));
		test_line(msg, builtin.top(), mine.top());
		mine.pop();
		builtin.pop();
	}

	std::cout << "==========Capacity test==============\n";
	for (int i = 0; i < 100; ++i)
	{
		int result = 1 + (rand() % 100);
		
		builtin.push(result);
		mine.push(result);
	}
	test_line("mine.empty()", builtin.empty(), mine.empty());
	test_line("mine.size()", builtin.size(), mine.size());
	
	std::cout << "==========Comparison operator test==============\n";
	std::stack<int> builtin_cpy;
	ft::Stack<int> mine_cpy;

	builtin_cpy = builtin;
	mine_cpy = mine;
	test_line("mine_cpy == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	mine_cpy.pop();
	builtin_cpy.pop();
	test_line("mine_cpy (popped back) == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy (popped back) != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy (popped back) > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy (popped back) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy (popped back) < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy (popped back) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	builtin_cpy = builtin;
	mine_cpy = mine;
	mine_cpy.push(69);
	builtin_cpy.push(69);
	mine_cpy.push(420);
	builtin_cpy.push(420);
	test_line("mine_cpy (pushed back) == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy (pushed back) != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy (pushed back) > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy (pushed back) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy (pushed back) < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy (pushed back) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);

	std::cout << "==========Timing test==============\n";
	clock_t my_time;
	my_time = clock();
	mine.push(123);
	my_time = clock() - my_time;

	clock_t builtin_time;
	builtin_time = clock();
	builtin.push(123);
	builtin_time = clock() - builtin_time;
	compare_time("mine.push(123)", builtin_time, my_time);

	my_time = clock();
	mine.pop();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.pop();
	builtin_time = clock() - builtin_time;
	compare_time("mine.pop()", builtin_time, my_time);

	my_time = clock();
	mine.top();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.top();
	builtin_time = clock() - builtin_time;
	compare_time("mine.top()", builtin_time, my_time);

	my_time = clock();
	mine.empty();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.empty();
	builtin_time = clock() - builtin_time;
	compare_time("mine.empty()", builtin_time, my_time);

	my_time = clock();
	mine.size();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.size();
	builtin_time = clock() - builtin_time;
	compare_time("mine.size()", builtin_time, my_time);



}