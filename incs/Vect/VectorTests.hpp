#include "Vector.hpp"
#include "Utils.hpp"
#include <vector>
#include <time.h>
#include "TestUtils.hpp"

void	testing()
{
	std::string	*str_arr;

	std::allocator<std::string> alloc;
	str_arr = alloc.allocate(5 * (sizeof(std::string) + 1));
	// str_arr[0] = std::string;
	for (int i = 0; i < 5; ++i) { new (str_arr + i) std::string; }
	str_arr[0] = "asdf";
	str_arr[1] = "asdf";
	str_arr[2] = "asdf";
	str_arr[3] = "asdf";
	str_arr[4] = "asdf";

	std::cout << str_arr[0] << "\n";
	alloc.deallocate(str_arr, 5);

 	// int	*str_arr;

	// std::allocator<int> alloc;
	// str_arr = alloc.allocate(5 * (sizeof(int) + 1));
	// // str_arr[0] = int;
	// for (int i = 0; i < 5; ++i) { new (str_arr + i) int; }
	// str_arr[0] = 12;
	// str_arr[1] = 12;
	// str_arr[2] = 12;
	// str_arr[3] = 12;
	// str_arr[4] = 12;

	// std::cout << str_arr[0] << "\n";
	// alloc.deallocate(str_arr, 5);
}

template <class T1>
void	test_init_vector(std::string message, int will_throw, T1 key_type)
{
	(void) key_type;
	try
	{
		std::vector<T1> builtin;
		ft::Vector<T1> mine;
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

template <class T>
static void	print_vect(ft::Vector<T> vect)
{
	typename ft::Vector<T>::iterator mine_iter;

	mine_iter = vect.begin();
	while (mine_iter != vect.end())
	{
		std::cout << *mine_iter << ", ";
		mine_iter++;
	}
	std::cout << "\n";
}

void	run_vector_tests()
{

	std::cout << "==========Initialization test==============\n";
	CustomClass cc;
	std::vector<int>	init_vect;

	cc.x = 1;
	cc.y = 2;
	test_init_set("ft_vector::<int>", 0, 0);
	test_init_set("ft_vector::<double>", 0, 1.1);
	test_init_set("ft_vector::<std::string>", 0, std::string("foo"));
	test_init_set("ft_vector::<NULL>", 0, NULL);
	test_init_set("ft_vector::<CustomClass>", 0, cc);
	test_init_set("ft_vector::<std::vector>", 0, init_vect);

	std::cout << "==========Modifier, Iterator and operation test==============\n";
	std::vector<int> builtin;
	ft::Vector<int> mine;
	std::vector<int>::iterator builtin_iter;
	ft::Vector<int>::iterator mine_iter;

	for (int i = 0; i < 100; ++i)
	{
		int result = 1 + (rand() % 100);
		
		builtin.push_back(result);
		mine.push_back(result);
	}

	builtin_iter = builtin.begin();
	mine_iter = mine.begin();
	int	i = -1;
	while ((builtin_iter != builtin.end()) && (mine_iter != mine.end()))
	{
		std::string msg;

		msg.append("*mine_iter == *builtin_iter at position ");
		msg.append(SSTR(++i));
		test_line(msg, *builtin_iter, *mine_iter);
		builtin_iter++;
		mine_iter++;
	}
	test_line_operation_success("mine.push_back() multiple", 1);
	test_line_diffclass("mine_iter == mine.end()", mine_iter, mine.end());
	test_line_diffclass("builtin_iter == builtin.end()", builtin_iter, builtin.end());

	for (int i = 0; i < 100; ++i)
	{
		builtin.pop_back();
		mine.pop_back();
	}

	builtin_iter = builtin.begin();
	mine_iter = mine.begin();
	i = -1;
	while ((builtin_iter != builtin.end()) && (mine_iter != mine.end()))
	{
		std::string msg;

		msg.append("*mine_iter == *builtin_iter at position ");
		msg.append(SSTR(++i));
		test_line(msg, *builtin_iter, *mine_iter);
		builtin_iter++;
		mine_iter++;
	}

	std::vector <int> swap_builtin; 
	ft::Vector <int> swap_mine;
	swap_builtin.push_back(100);
	swap_mine.push_back(100);
	
	try
	{
		builtin.swap(swap_builtin);
		mine.swap(swap_mine);
		test_line_operation_success("mine.swap(swap_mine)", 1);
		test_line("mine.begin()", *builtin.begin(), *mine.begin());
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.swap(swap_mine)", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}
	try
	{
		srand((unsigned) time(0));
		for (int i = 0; i < 100; ++i)
		{
			int result = 1 + (rand() % 100);
			
			builtin.insert(builtin.begin(), result);
			mine.insert(mine.begin() , result);
		}
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.insert() multiple ", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}

	builtin_iter = builtin.begin();
	mine_iter = mine.begin();
	i = -1;
	while (builtin_iter != builtin.end())
	{
		std::string msg;

		msg.append("*mine_iter position ");
		msg.append(SSTR(++i));
		test_line(msg, *builtin_iter, *mine_iter);
		builtin_iter++;
		mine_iter++;
	}

	std::vector<int>::reverse_iterator rev_builtin_iter;
	ft::Vector<int>::reverse_iterator rev_mine_iter;

	rev_builtin_iter = builtin.rbegin();
	rev_mine_iter = mine.rbegin();
	i = -1;
	while (rev_mine_iter != mine.rend())
	{
		std::string msg;

		msg.append("*rev_mine_iter position ");
		msg.append(SSTR(++i));
		test_line(msg, *rev_builtin_iter, *rev_mine_iter);
		++rev_builtin_iter;
		++rev_mine_iter;
	}
	test_line_diffclass("rev_mine_iter == mine.rend()", rev_mine_iter, mine.rend());

	builtin_iter = builtin.begin();
	mine_iter = mine.begin();
	test_line("mine_iter != mine.end()", builtin_iter != builtin.end(), mine_iter != mine.end());
	try
	{
		mine.clear();
		builtin.clear();
		test_line_operation_success("mine.clear()", 1);
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.clear() ", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}

	std::vector< int > vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	ft::Vector< int > vec_ft;
	vec_ft.push_back(1);
	vec_ft.push_back(2);
	vec_ft.push_back(3);
	vec_ft.push_back(4);

	try
	{
		builtin.insert(builtin.begin(), vec.begin(), vec.end());
		mine.insert(mine.begin(), vec_ft.begin(), vec_ft.end());
		test_line_operation_success("mine.insert(vec_ft.begin(), vec_ft.end())", 1);
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.insert(vec_ft.begin(), vec_ft.end()) ", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}
	test_line("*mine.begin()", *builtin.begin(), *mine.begin());
	test_line("*(--mine.end())", *(--builtin.end()), *(--mine.end()));

	for (int i = 0; i < 100; ++i)
	{
		int result = 1 + (rand() % 100);
		
		builtin.push_back(result);
		mine.push_back(result);
	}
	builtin.erase(builtin.begin());
	mine.erase(mine.begin());
	test_line_operation_success("mine.erase(mine.begin())", 1);
	test_line("*mine.begin()", *builtin.begin(), *mine.begin());

	builtin.erase(++builtin.begin(), --builtin.end());
	mine.erase(++mine.begin(), --mine.end());
	test_line_operation_success("mine.erase(mine.begin(), mine.end())", 1);
	test_line("*mine.begin()", *builtin.begin(), *mine.begin());
	std::cout << "==========Capacity test==============\n";
	test_line("mine.empty()", builtin.empty(), mine.empty());
	test_line("mine.size()", builtin.size(), mine.size());
	// test_line("mine.capacity()", builtin.capacity(), mine.capacity()); //ask issac
	try
	{
		builtin.clear();
		mine.clear();
		test_line_operation_success("mine.clear()", 1);
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.clear() ", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}
	builtin.clear();
	mine.clear();
	test_line("mine.empty()", builtin.empty(), mine.empty());
	test_line("mine.empty()", builtin.empty(), mine.empty());
	test_line("mine.size()", builtin.size(), mine.size());
	// not testing max_size() bcuz it varies on implementation. both can never be equal unless i c/p source code directly
	// test_line("mine.max_size()", builtin.max_size(), mine.max_size());

	std::cout << "==========Element access test==============\n";
	builtin.insert(builtin.begin(), vec.begin(), vec.end());
	mine.insert(mine.begin(), vec_ft.begin(), vec_ft.end());
	test_line("mine.at(1)", builtin.at(1), mine.at(1));
	test_line("mine.at(0)", builtin.at(0), mine.at(0));
	try
	{
		mine.at(2134);
	}
	catch(const std::exception &e)
	{
		test_line_operation_fail("mine.at(1234)", 1);
	}
	test_line("mine[1]", builtin[1], mine[1]);
	test_line("mine.front()", builtin.front(), mine.front());
	test_line("mine.back()", builtin.back(), mine.back());
	
	int	*builtin_data;
	int	*mine_data;

	builtin_data = builtin.data();
	mine_data = mine.data();

	test_line("mine.data()[0]", builtin_data[0], mine_data[0]);
	//test for throw err

	std::cout << "==========Comparison operator test==============\n";
	std::vector<int> builtin_cpy;
	ft::Vector<int> mine_cpy;

	builtin_cpy = builtin;
	mine_cpy = mine;
	test_line("mine_cpy == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	mine_cpy.pop_back();
	builtin_cpy.pop_back();
	test_line("mine_cpy (popped back) == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy (popped back) != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy (popped back) > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy (popped back) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy (popped back) < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy (popped back) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	builtin_cpy = builtin;
	mine_cpy = mine;
	mine_cpy.push_back(69);
	builtin_cpy.push_back(69);
	mine_cpy.push_back(420);
	builtin_cpy.push_back(420);
	test_line("mine_cpy (pushed back) == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy (pushed back) != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy (pushed back) > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy (pushed back) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy (pushed back) < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy (pushed back) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);


	std::cout << "==========Misc test==============\n";
	ft::Vector<std::string> misc_mine;
	std::vector<std::string> misc_builtin;

	misc_mine.push_back("123456789012345678901234567890123456789012345678901234567890");
	misc_builtin.push_back("123456789012345678901234567890123456789012345678901234567890");

	test_line("misc_mine.back()", misc_builtin.back(), misc_mine.back());
	// std::allocator<std::string> alloc;
	// alloc.allocate(123123456 * sizeof(std::string));


	std::cout << "==========Timing test==============\n";
	clock_t my_time;
	my_time = clock();
	mine.push_back(123);
	my_time = clock() - my_time;

	clock_t builtin_time;
	builtin_time = clock();
	builtin.push_back(123);
	builtin_time = clock() - builtin_time;
	compare_time("mine.push_back(123)", builtin_time, my_time);

	my_time = clock();
	mine.begin();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.begin();
	builtin_time = clock() - builtin_time;
	compare_time("mine.begin()", builtin_time, my_time);

	my_time = clock();
	mine.end();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.end();
	builtin_time = clock() - builtin_time;
	compare_time("mine.end()", builtin_time, my_time);

	my_time = clock();
	mine.rbegin();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.rbegin();
	builtin_time = clock() - builtin_time;
	compare_time("mine.rbegin()", builtin_time, my_time);

	my_time = clock();
	mine.rend();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.rend();
	builtin_time = clock() - builtin_time;
	compare_time("mine.rend()", builtin_time, my_time);

	my_time = clock();
	mine.end();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.end();
	builtin_time = clock() - builtin_time;
	compare_time("mine.end()", builtin_time, my_time);

	my_time = clock();
	mine.at(1);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.at(1);
	builtin_time = clock() - builtin_time;
	compare_time("mine.at(1)", builtin_time, my_time);

	// mine.clear();
	// builtin.clear();
	
	// my_time = clock();
	// mine.swap(swap_mine);
	// my_time = clock() - my_time;

	builtin_time = clock();
	builtin.swap(swap_builtin);
	builtin_time = clock() - builtin_time;
	compare_time("mine.swap(swap_mine)", builtin_time, my_time);

	my_time = clock();
	mine = swap_mine;
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin = swap_builtin;
	builtin_time = clock() - builtin_time;
	compare_time("mine = swap_mine", builtin_time, my_time);

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

	my_time = clock();
	mine.clear();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.clear();
	builtin_time = clock() - builtin_time;
	compare_time("mine.clear()", builtin_time, my_time);
}