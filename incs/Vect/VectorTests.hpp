#include "Vector.hpp"
#include "Utils.hpp"
#include <vector>
#include <time.h>
#include "TestUtils.hpp"

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

void	testing()
{
	srand((unsigned) time(0));
	for (int i = 0; i < 100; ++i)
	{
		int result = 1 + (rand() % 100);

		std::cout << result << '\n';
	}
	
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

	// std::cout << "==========Modifier, Iterator and operation test==============\n";
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
	// std::set <int> swap_builtin; 
	// ft::Vector <int> swap_mine;
	// swap_builtin.insert(100);
	// swap_mine.insert(100);
	
	// try
	// {
	// 	builtin.swap(swap_builtin);
	// 	mine.swap(swap_mine);
	// 	test_line_operation_success("mine.swap(swap_mine)", 1);
	// 	test_line("mine.begin()", *builtin.begin(), *mine.begin());
	// }
	// catch(const std::exception& e)
	// {
	// 	print_fail_msg("mine.swap(swap_mine)", " [FAIL] Operation failed unexpectedly");
	// 	std::cout << e.what();
	// }
	// // i wont test iterator.end()++ because that causes undef behaviour even in std::set
	// try
	// {
	// 	srand((unsigned) time(0));
	// 	for (int i = 0; i < 100; ++i)
	// 	{
	// 		int result = 1 + (rand() % 100);
			
	// 		builtin.insert(result);
	// 		mine.insert(result);
	// 	}
	// 	test_line_operation_success("mine.insert() multiple", 1);

	// }
	// catch(const std::exception& e)
	// {
	// 	print_fail_msg("mine.insert() multiple ", " [FAIL] Operation failed unexpectedly");
	// 	std::cout << e.what();
	// }
	// std::set<int>::iterator builtin_iter;
	// ft::Vector<int>::iterator mine_iter;
	// int	i;

	// builtin_iter = builtin.begin();
	// mine_iter = mine.begin();
	// i = -1;
	// while (builtin_iter != builtin.end())
	// {
	// 	std::string msg;

	// 	msg.append("*mine_iter position ");
	// 	msg.append(SSTR(++i));
	// 	test_line(msg, *builtin_iter, *mine_iter);
	// 	builtin_iter++;
	// 	mine_iter++;
	// }
	// test_line_diffclass("mine_iter == mine.end()", mine_iter, mine.end());

	// std::set<int>::reverse_iterator rev_builtin_iter;
	// ft::Vector<int>::reverse_iterator rev_mine_iter;

	// rev_builtin_iter = builtin.rbegin();
	// rev_mine_iter = mine.rbegin();
	// i = -1;
	// while (rev_mine_iter != mine.rend())
	// {
	// 	std::string msg;

	// 	msg.append("*rev_mine_iter position ");
	// 	msg.append(SSTR(++i));
	// 	test_line(msg, *rev_builtin_iter, *rev_mine_iter);
	// 	++rev_builtin_iter;
	// 	++rev_mine_iter;
	// }
	// test_line_diffclass("rev_mine_iter == mine.rend()", rev_mine_iter, mine.rend());

	// builtin_iter = builtin.begin();
	// mine_iter = mine.begin();
	// test_line("mine_iter != mine.end()", builtin_iter != builtin.end(), mine_iter != mine.end());
	// try
	// {
	// 	mine.clear();
	// 	builtin.clear();
	// 	test_line_operation_success("mine.clear()", 1);
	// }
	// catch(const std::exception& e)
	// {
	// 	print_fail_msg("mine.clear() ", " [FAIL] Operation failed unexpectedly");
	// 	std::cout << e.what();
	// }
	// std::vector< int > vec;
	// vec.push_back(1);
	// vec.push_back(2);
	// vec.push_back(3);
	// vec.push_back(4);


	// std::vector< int > vec_ft;
	// vec_ft.push_back(1);
	// vec_ft.push_back(2);
	// vec_ft.push_back(3);
	// vec_ft.push_back(4);

	// try
	// {
	// 	builtin.insert(vec.begin(), vec.end());
	// 	mine.insert(vec_ft.begin(), vec_ft.end());
	// 	test_line_operation_success("mine.insert(vec_ft.begin(), vec_ft.end())", 1);
	// }
	// catch(const std::exception& e)
	// {
	// 	print_fail_msg("mine.insert(vec_ft.begin(), vec_ft.end()) ", " [FAIL] Operation failed unexpectedly");
	// 	std::cout << e.what();
	// }
	// test_line("*mine.begin()", *builtin.begin(), *mine.begin());
	// test_line("*(--mine.end())", *(--builtin.end()), *(--mine.end()));

	// std::cout << "==========Capacity test==============\n";
	// test_line("mine.empty()", builtin.empty(), mine.empty());
	// test_line("mine.size()", builtin.size(), mine.size());
	// try
	// {
	// 	builtin.clear();
	// 	mine.clear();
	// 	test_line_operation_success("mine.clear()", 1);
	// }
	// catch(const std::exception& e)
	// {
	// 	print_fail_msg("mine.clear() ", " [FAIL] Operation failed unexpectedly");
	// 	std::cout << e.what();
	// }
	// builtin.clear();
	// mine.clear();
	// test_line("mine.empty()", builtin.empty(), mine.empty());
	// test_line("mine.empty()", builtin.empty(), mine.empty());
	// test_line("mine.size()", builtin.size(), mine.size());
	// // not testing max_size() bcuz it varies on implementation. both can never be equal unless i c/p source code directly
	// // test_line("mine.max_size()", builtin.max_size(), mine.max_size());

	// std::cout << "==========Lookup test==============\n";
	// builtin.insert(vec.begin(), vec.end());
	// mine.insert(vec_ft.begin(), vec_ft.end());
	// test_line("mine.count(1)", builtin.count(1), mine.count(1));
	// test_line("mine.count(123)", builtin.count(123), mine.count(123));
	// test_line("mine.count(-123)", builtin.count(-123), mine.count(-123));
	// test_line("*mine.find(1)", *builtin.find(1), *mine.find(1));
	// test_line("*mine.find(1)", *builtin.find(1), *mine.find(1));
	// test_line("*mine.find(3)", *builtin.find(3), *mine.find(3));
	// test_line("*mine.find(3)", *builtin.find(3), *mine.find(3));
	// // accessing end() causes undef bahaviour. see https://en.cppreference.com/w/cpp/container/set/end
	// // test_line("mine.find(-1)->first", builtin.find(-1)->first, mine.find(-1)->first);
	// // test_line("mine.find(123456)->first", builtin.find(123456)->first, mine.find(123456)->first);
	// test_line("*mine.lower_bound(3)", *builtin.lower_bound(3), *mine.lower_bound(3));
	// test_line("*mine.lower_bound(3)", *builtin.lower_bound(3), *mine.lower_bound(3));
	// test_line("*mine.lower_bound(1)", *builtin.lower_bound(1), *mine.lower_bound(1));
	// test_line("*mine.lower_bound(1)", *builtin.lower_bound(1), *mine.lower_bound(1));
	// test_line("*mine.lower_bound(4)", *builtin.lower_bound(4), *mine.lower_bound(4));
	// test_line("*mine.lower_bound(4)", *builtin.lower_bound(4), *mine.lower_bound(4));
	
	// test_line("*mine.upper_bound(3)", *builtin.upper_bound(3), *mine.upper_bound(3));
	// test_line("*mine.upper_bound(3)", *builtin.upper_bound(3), *mine.upper_bound(3));
	// test_line("*mine.upper_bound(1)", *builtin.upper_bound(1), *mine.upper_bound(1));
	// test_line("*mine.upper_bound(1)", *builtin.upper_bound(1), *mine.upper_bound(1));
	// // accessing end() causes undef bahaviour. see https://en.cppreference.com/w/cpp/container/set/end
	// // test_line("mine.upper_bound(4)->first", builtin.upper_bound(4)->first, mine.upper_bound(4)->first);
	// // std::cout << "( " << builtin.upper_bound(4)->first << ", " << builtin.upper_bound(4)->second << " )" << "\n";
	// // std::cout << "( " << mine.upper_bound(4)->first << ", " << mine.upper_bound(4)->second << " )" << "\n";
	// // test_line("mine.upper_bound(4)->second", builtin.upper_bound(4)->second, mine.upper_bound(4)->second);

	// test_line("*mine.equal_range(3).first", *builtin.equal_range(3).first, *mine.equal_range(3).first);
	// test_line("*mine.equal_range(3).second", *builtin.equal_range(3).second, *mine.equal_range(3).second);
	
	// test_line("*mine.equal_range(1).first", *builtin.equal_range(1).first, *mine.equal_range(1).first);
	// test_line("*mine.equal_range(1).second", *builtin.equal_range(1).second, *mine.equal_range(1).second);

	// // accessing end() causes undef bahaviour. see https://en.cppreference.com/w/cpp/container/set/end
	// // test_line("mine.equal_range(4).first->first", builtin.equal_range(4).first->first, mine.equal_range(4).first->first);
	// // test_line("mine.equal_range(4).first->second", builtin.equal_range(4).first->second, mine.equal_range(4).first->second);
	// // test_line("mine.equal_range(4).second->first", builtin.equal_range(4).second->first, mine.equal_range(4).second->first);
	// // test_line("mine.equal_range(4).second->second", builtin.equal_range(4).second->second, mine.equal_range(4).second->second);

	// std::cout << "==========Comparison operator test==============\n";
	// std::set<int> builtin_cpy;
	// ft::Vector<int> mine_cpy;

	// builtin_cpy = builtin;
	// mine_cpy = mine;
	// test_line("mine_cpy == mine", builtin_cpy == builtin, mine_cpy == mine);
	// test_line("mine_cpy != mine", builtin_cpy != builtin, mine_cpy != mine);
	// test_line("mine_cpy > mine", builtin_cpy > builtin, mine_cpy > mine);
	// test_line("mine_cpy >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	// test_line("mine_cpy < mine", builtin_cpy < builtin, mine_cpy < mine);
	// test_line("mine_cpy <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	// mine_cpy.erase(1);
	// builtin_cpy.erase(1);
	// test_line("mine_cpy(erased 1) == mine", builtin_cpy == builtin, mine_cpy == mine);
	// test_line("mine_cpy(erased 1) != mine", builtin_cpy != builtin, mine_cpy != mine);
	// test_line("mine_cpy(erased 1) > mine", builtin_cpy > builtin, mine_cpy > mine);
	// test_line("mine_cpy(erased 1) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	// test_line("mine_cpy(erased 1) < mine", builtin_cpy < builtin, mine_cpy < mine);
	// test_line("mine_cpy(erased 1) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	// builtin_cpy = builtin;
	// mine_cpy = mine;
	// mine_cpy.insert(69);
	// builtin_cpy.insert(69);
	// mine_cpy.insert(420);
	// builtin_cpy.insert(420);
	// test_line("mine_cpy(added 1) == mine", builtin_cpy == builtin, mine_cpy == mine);
	// test_line("mine_cpy(added 1) != mine", builtin_cpy != builtin, mine_cpy != mine);
	// test_line("mine_cpy(added 1) > mine", builtin_cpy > builtin, mine_cpy > mine);
	// test_line("mine_cpy(added 1) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	// test_line("mine_cpy(added 1) < mine", builtin_cpy < builtin, mine_cpy < mine);
	// test_line("mine_cpy(added 1) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);

	// std::cout << "==========Observer test==============\n";
	// ft::Vector<int> set_mine;

	// set_mine.insert(1001);
	// set_mine.insert(2002);
	// set_mine.insert(3003);

	// std::set<int> set_builtin;

	// set_builtin.insert(1001);
	// set_builtin.insert(2002);
	// set_builtin.insert(3003);


	// int highest = *set_mine.rbegin();
	// ft::Vector<int>::iterator it = set_mine.begin();
	// int highest_builtin = *set_builtin.rbegin();        
	// std::set<int>::iterator it_builtin = set_builtin.begin();

	// do {
	// 	test_line("*it", *it, *it_builtin);
	// 	test_line("set_mine.value_comp()(*it, highest)", set_builtin.value_comp()(*it_builtin, highest_builtin),
	// 	set_mine.value_comp()(*it, highest));
	// } while ( set_mine.value_comp()(*it++, highest)  &&  set_builtin.value_comp()(*it_builtin++, highest_builtin));

	// std::set<int>::key_compare builtincomp = set_builtin.key_comp();
	// ft::Vector<int>::key_compare mycomp = set_mine.key_comp();

	// int firstmine = *set_mine.rbegin();
	// int firstbuiltin = *set_builtin.rbegin(); 

	// it = set_mine.begin();
	// it_builtin = set_builtin.begin();
	// do {
	// 	test_line("*it", *it, *it_builtin);
	// 	test_line("mycomp((*it).first, firstmine)", builtincomp((*it_builtin), firstbuiltin),
	// 	mycomp((*it), firstmine));
	// } while ( builtincomp((*it_builtin++), firstbuiltin) && mycomp((*it++), firstmine) );

	// std::cout << "==========Timing test==============\n";
	// clock_t my_time;
	// my_time = clock();
	// mine.insert(123);
	// my_time = clock() - my_time;

	// clock_t builtin_time;
	// builtin_time = clock();
	// builtin.insert(123);
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.insert(123)", builtin_time, my_time);

	// my_time = clock();
	// mine.begin();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.begin();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.begin()", builtin_time, my_time);

	// my_time = clock();
	// mine.end();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.end();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.end()", builtin_time, my_time);

	// my_time = clock();
	// mine.rbegin();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.rbegin();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.rbegin()", builtin_time, my_time);

	// my_time = clock();
	// mine.rend();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.rend();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.rend()", builtin_time, my_time);

	// my_time = clock();
	// mine.end();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.end();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.end()", builtin_time, my_time);

	// my_time = clock();
	// mine.find(1);
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.find(1);
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.find(1)", builtin_time, my_time);

	// mine.clear();
	// builtin.clear();
	
	// my_time = clock();
	// mine.swap(swap_mine);
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.swap(swap_builtin);
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.swap(swap_mine)", builtin_time, my_time);

	// my_time = clock();
	// mine = swap_mine;
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin = swap_builtin;
	// builtin_time = clock() - builtin_time;
	// compare_time("mine = swap_mine", builtin_time, my_time);

	// my_time = clock();
	// mine.empty();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.empty();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.empty()", builtin_time, my_time);

	// my_time = clock();
	// mine.size();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.size();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.size()", builtin_time, my_time);

	// my_time = clock();
	// mine.count(1);
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.count(1);
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.count(1)", builtin_time, my_time);

	// my_time = clock();
	// mine.lower_bound(3);
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.lower_bound(3);
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.lower_bound(3)", builtin_time, my_time);

	// my_time = clock();
	// mine.upper_bound(1);
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.upper_bound(1);
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.upper_bound(1)", builtin_time, my_time);

	// my_time = clock();
	// mine.equal_range(2);
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.equal_range(2);
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.equal_range(2)", builtin_time, my_time);

	// my_time = clock();
	// mine.clear();
	// my_time = clock() - my_time;

	// builtin_time = clock();
	// builtin.clear();
	// builtin_time = clock() - builtin_time;
	// compare_time("mine.clear()", builtin_time, my_time);
}