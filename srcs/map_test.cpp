#include "Map.hpp"
#include "TestUtils.hpp"
#include <map>
#include <time.h>

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

template <class T1, class T2>
void	test_init_map(std::string message, int will_throw, T1 key_type, T2 mapped_type)
{
	(void) key_type;
	(void) mapped_type;
	try
	{
		std::map<T1, T2> builtin;
		ft::Map<T1, T2> mine;
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

void	run_map_tests()
{

	std::cout << "==========Initialization test==============\n";
	CustomClass cc;

	cc.x = 1;
	cc.y = 2;
	test_init_map("ft_map::<int, int>", 0, 0, 0);
	test_init_map("ft_map::<double, double>", 0, 1.1, 0.0);
	test_init_map("ft_map::<std::string, std::string>", 0, std::string("foo"), std::string("foo"));
	test_init_map("ft_map::<NULL, NULL>", 0, NULL, NULL);
	test_init_map("ft_map::<std::string, int>", 0, std::string("foo"), 1);
	test_init_map("ft_map::<NULL, int>", 0, NULL, 1);
	test_init_map("ft_map::<CustomClass, CustomClass>", 0, cc, cc);
	test_init_map("ft_map::<CustomClass, int>", 0, cc, 1);

	std::cout << "==========Modifier, Iterator and operation test==============\n";
	std::map<int, std::string> builtin;
	ft::Map<int, std::string> mine;
	test_line("mine.insert(ft::make_pair(1, \"one\")).second ", builtin.insert(std::make_pair(1, "one")).second, mine.insert(ft::make_pair(1, "one")).second);
	test_line("mine.begin()->first", builtin.begin()->first, mine.begin()->first);
	test_line("mine.begin()->second", builtin.begin()->second, mine.begin()->second);
	test_line("mine.insert(ft::make_pair(2, \"two\")).second ", builtin.insert(std::make_pair(2, "two")).second, mine.insert(ft::make_pair(2, "two")).second);
	test_line("mine.begin()->first", builtin.begin()->first, mine.begin()->first);
	test_line("mine.begin()->second", builtin.begin()->second, mine.begin()->second);
	test_line("mine.insert(ft::make_pair(1, \"two\")).second", builtin.insert(std::make_pair(1, "two")).second, mine.insert(ft::make_pair(1, "two")).second);
	test_line("mine.insert(ft::make_pair(1, \"three\")).second", builtin.insert(std::make_pair(1, "three")).second, mine.insert(ft::make_pair(1, "three")).second);
	test_line("mine.find(1)->second", builtin.find(1)->second, mine.find(1)->second);
	test_line("mine.find(2)->second", builtin.find(2)->second, mine.find(2)->second);
	std::map <int, std::string> swap_builtin; 
	ft::Map <int, std::string> swap_mine;
	swap_builtin.insert(std::make_pair(1, "one_swapped"));
	swap_mine.insert(ft::make_pair(1, "one_swapped"));
	
	try
	{
		builtin.swap(swap_builtin);
		mine.swap(swap_mine);
		test_line_operation_success("mine.swap(swap_mine)", 1);
		test_line("mine.begin()->first", builtin.begin()->first, mine.begin()->first);
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.swap(swap_mine)", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}
	// i wont test iterator.end()++ because that causes undef behaviour even in std::map
	try
	{
		builtin.insert(std::make_pair(2, "two"));
		mine.insert(ft::make_pair(2, "two"));
		builtin.insert(std::make_pair(3, "three"));
		mine.insert(ft::make_pair(3, "three"));
		builtin.insert(std::make_pair(4, "four"));
		mine.insert(ft::make_pair(4, "four"));
		builtin.insert(std::make_pair(5, "five"));
		mine.insert(ft::make_pair(5, "five"));
		builtin.insert(std::make_pair(6, "six"));
		mine.insert(ft::make_pair(6, "six"));
		builtin.insert(std::make_pair(7, "seven"));
		mine.insert(ft::make_pair(7, "seven"));
		builtin.insert(std::make_pair(8, "eight"));
		mine.insert(ft::make_pair(8, "eight"));
		builtin.insert(std::make_pair(9, "nine"));
		mine.insert(ft::make_pair(9, "nine"));
		builtin.insert(std::make_pair(10, "ten"));
		mine.insert(ft::make_pair(10, "ten"));
		test_line_operation_success("mine.insert() multiple", 1);

	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.insert() multiple ", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}
	std::map<int, std::string>::iterator builtin_iter;
	ft::Map<int, std::string>::iterator mine_iter;
	int	i;

	builtin_iter = builtin.begin();
	mine_iter = mine.begin();
	i = -1;
	while (builtin_iter != builtin.end())
	{
		std::cout << "iter at position " << ++i << "\n";
		test_line("mine_iter->first", builtin_iter->first, mine_iter->first);
		test_line("mine_iter->second", builtin_iter->second, mine_iter->second);
		builtin_iter++;
		mine_iter++;
	}
	test_line_diffclass("mine_iter == mine.end()", mine_iter, mine.end());

	std::map<int, std::string>::reverse_iterator builtin_rev_iter;
	ft::Map<int, std::string>::reverse_iterator mine_rev_iter;

	builtin_rev_iter = builtin.rbegin();
	mine_rev_iter = mine.rbegin();
	i = -1;
	while (builtin_rev_iter != builtin.rend())
	{
		std::cout << "iter at position " << ++i << "\n";
		test_line("mine_rev_iter->first", builtin_rev_iter->first, mine_rev_iter->first);
		test_line("mine_rev_iter->second", builtin_rev_iter->second, mine_rev_iter->second);
		builtin_rev_iter++;
		mine_rev_iter++;
	}
	test_line_diffclass("mine_rev_iter == mine.rend()", mine_rev_iter, mine.rend());
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
	std::vector<std::pair<int, std::string> > vec;
	vec.push_back(std::make_pair(1, std::string("one from vect")));
	vec.push_back(std::make_pair(2, std::string("two from vect")));
	vec.push_back(std::make_pair(3, std::string("three from vect")));
	vec.push_back(std::make_pair(4, std::string("four from vect")));


	std::vector<ft::pair<int, std::string> > vec_ft;
	vec_ft.push_back(ft::make_pair(1, std::string("one from vect")));
	vec_ft.push_back(ft::make_pair(2, std::string("two from vect")));
	vec_ft.push_back(ft::make_pair(3, std::string("three from vect")));
	vec_ft.push_back(ft::make_pair(4, std::string("four from vect")));

	try
	{
		builtin.insert(vec.begin(), vec.end());
		mine.insert(vec_ft.begin(), vec_ft.end());
		test_line_operation_success("mine.insert(vec_ft.begin(), vec_ft.end())", 1);
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine.insert(vec_ft.begin(), vec_ft.end()) ", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}
	test_line("mine.begin()->second", builtin.begin()->second, mine.begin()->second);
	test_line("(--mine.end())->second", (--builtin.end())->second, (--mine.end())->second);

	std::cout << "==========Element access test==============\n";
	test_line("mine[0]", builtin[0], mine[0]);
	test_line("mine[1]", builtin[1], mine[1]);
	test_line("mine[2]", builtin[2], mine[2]);
	test_line("mine[3]", builtin[3], mine[3]);
	test_line("mine[4]", builtin[4], mine[4]);
	try
	{
		builtin[12] = std::string("!!!");
		mine[12] = std::string("!!!");
		test_line_operation_success("mine[12] = std::string(\"!!!\");", 1);
	}
	catch(const std::exception& e)
	{
		print_fail_msg("mine[12] = std::string(\"!!!\") ", " [FAIL] Operation failed unexpectedly");
		std::cout << e.what();
	}
	test_line("mine[12]", builtin[12], mine[12]);
	test_line("mine.at(12)", builtin.at(12), mine.at(12));

	std::cout << "==========Capacity test==============\n";
	test_line("mine.empty()", builtin.empty(), mine.empty());
	test_line("mine.size()", builtin.size(), mine.size());
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

	std::cout << "==========Lookup test==============\n";
	builtin.insert(vec.begin(), vec.end());
	mine.insert(vec_ft.begin(), vec_ft.end());
	test_line("mine.count(1)", builtin.count(1), mine.count(1));
	test_line("mine.count(123)", builtin.count(123), mine.count(123));
	test_line("mine.count(-123)", builtin.count(-123), mine.count(-123));
	test_line("mine.find(1)->second", builtin.find(1)->second, mine.find(1)->second);
	test_line("mine.find(1)->first", builtin.find(1)->first, mine.find(1)->first);
	test_line("mine.find(3)->second", builtin.find(3)->second, mine.find(3)->second);
	test_line("mine.find(3)->first", builtin.find(3)->first, mine.find(3)->first);
	// accessing end() causes undef bahaviour. see https://en.cppreference.com/w/cpp/container/map/end
	// test_line("mine.find(-1)->first", builtin.find(-1)->first, mine.find(-1)->first);
	// test_line("mine.find(123456)->first", builtin.find(123456)->first, mine.find(123456)->first);
	test_line("mine.lower_bound(3)->first", builtin.lower_bound(3)->first, mine.lower_bound(3)->first);
	test_line("mine.lower_bound(3)->second", builtin.lower_bound(3)->second, mine.lower_bound(3)->second);
	test_line("mine.lower_bound(1)->first", builtin.lower_bound(1)->first, mine.lower_bound(1)->first);
	test_line("mine.lower_bound(1)->second", builtin.lower_bound(1)->second, mine.lower_bound(1)->second);
	test_line("mine.lower_bound(4)->first", builtin.lower_bound(4)->first, mine.lower_bound(4)->first);
	test_line("mine.lower_bound(4)->second", builtin.lower_bound(4)->second, mine.lower_bound(4)->second);
	
	test_line("mine.upper_bound(3)->first", builtin.upper_bound(3)->first, mine.upper_bound(3)->first);
	test_line("mine.upper_bound(3)->second", builtin.upper_bound(3)->second, mine.upper_bound(3)->second);
	test_line("mine.upper_bound(1)->first", builtin.upper_bound(1)->first, mine.upper_bound(1)->first);
	test_line("mine.upper_bound(1)->second", builtin.upper_bound(1)->second, mine.upper_bound(1)->second);
	// accessing end() causes undef bahaviour. see https://en.cppreference.com/w/cpp/container/map/end
	// test_line("mine.upper_bound(4)->first", builtin.upper_bound(4)->first, mine.upper_bound(4)->first);
	// std::cout << "( " << builtin.upper_bound(4)->first << ", " << builtin.upper_bound(4)->second << " )" << "\n";
	// std::cout << "( " << mine.upper_bound(4)->first << ", " << mine.upper_bound(4)->second << " )" << "\n";
	// test_line("mine.upper_bound(4)->second", builtin.upper_bound(4)->second, mine.upper_bound(4)->second);

	test_line("mine.equal_range(3).first->first", builtin.equal_range(3).first->first, mine.equal_range(3).first->first);
	test_line("mine.equal_range(3).first->second", builtin.equal_range(3).first->second, mine.equal_range(3).first->second);
	test_line("mine.equal_range(3).second->first", builtin.equal_range(3).second->first, mine.equal_range(3).second->first);
	test_line("mine.equal_range(3).second->second", builtin.equal_range(3).second->second, mine.equal_range(3).second->second);
	
	test_line("mine.equal_range(1).first->first", builtin.equal_range(1).first->first, mine.equal_range(1).first->first);
	test_line("mine.equal_range(1).first->second", builtin.equal_range(1).first->second, mine.equal_range(1).first->second);
	test_line("mine.equal_range(1).second->first", builtin.equal_range(1).second->first, mine.equal_range(1).second->first);
	test_line("mine.equal_range(1).second->second", builtin.equal_range(1).second->second, mine.equal_range(1).second->second);

	// accessing end() causes undef bahaviour. see https://en.cppreference.com/w/cpp/container/map/end
	// test_line("mine.equal_range(4).first->first", builtin.equal_range(4).first->first, mine.equal_range(4).first->first);
	// test_line("mine.equal_range(4).first->second", builtin.equal_range(4).first->second, mine.equal_range(4).first->second);
	// test_line("mine.equal_range(4).second->first", builtin.equal_range(4).second->first, mine.equal_range(4).second->first);
	// test_line("mine.equal_range(4).second->second", builtin.equal_range(4).second->second, mine.equal_range(4).second->second);

	std::cout << "==========Comparison operator test==============\n";
	std::map<int, std::string> builtin_cpy;
	ft::Map<int, std::string> mine_cpy;

	builtin_cpy = builtin;
	mine_cpy = mine;
	test_line("mine_cpy == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	mine_cpy.erase(1);
	builtin_cpy.erase(1);
	test_line("mine_cpy(erased 1) == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy(erased 1) != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy(erased 1) > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy(erased 1) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy(erased 1) < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy(erased 1) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);
	builtin_cpy = builtin;
	mine_cpy = mine;
	mine_cpy.insert(ft::make_pair(69, "fav number"));
	builtin_cpy.insert(std::make_pair(69, "fav number"));
	mine_cpy.insert(ft::make_pair(420, "fav number 2"));
	builtin_cpy.insert(std::make_pair(420, "fav number 2"));
	test_line("mine_cpy(added 1) == mine", builtin_cpy == builtin, mine_cpy == mine);
	test_line("mine_cpy(added 1) != mine", builtin_cpy != builtin, mine_cpy != mine);
	test_line("mine_cpy(added 1) > mine", builtin_cpy > builtin, mine_cpy > mine);
	test_line("mine_cpy(added 1) >= mine", builtin_cpy >= builtin, mine_cpy >= mine);
	test_line("mine_cpy(added 1) < mine", builtin_cpy < builtin, mine_cpy < mine);
	test_line("mine_cpy(added 1) <= mine", builtin_cpy <= builtin, mine_cpy <= mine);

	std::cout << "==========Timing test==============\n";
	clock_t my_time;
	my_time = clock();
	mine.insert(ft::make_pair(123, "time"));
	my_time = clock() - my_time;

	clock_t builtin_time;
	builtin_time = clock();
	builtin.insert(std::make_pair(123, "time"));
	builtin_time = clock() - builtin_time;
	compare_time("mine.insert(ft::make_pair(123, \"time\"))", builtin_time, my_time);

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
	mine.find(1);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.find(1);
	builtin_time = clock() - builtin_time;
	compare_time("mine.find(1)", builtin_time, my_time);

	my_time = clock();
	mine.swap(swap_mine);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.swap(swap_builtin);
	builtin_time = clock() - builtin_time;
	std::cout << my_time << "\n";
	std::cout << builtin_time << "\n";
	compare_time("mine.swap(swap_mine)", builtin_time, my_time);

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
	mine.at(1);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.at(1);
	builtin_time = clock() - builtin_time;
	compare_time("mine.at(1)", builtin_time, my_time);

	my_time = clock();
	mine.count(1);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.count(1);
	builtin_time = clock() - builtin_time;
	compare_time("mine.count(1)", builtin_time, my_time);

	my_time = clock();
	mine.lower_bound(3);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.lower_bound(3);
	builtin_time = clock() - builtin_time;
	compare_time("mine.lower_bound(3)", builtin_time, my_time);

	my_time = clock();
	mine.upper_bound(1);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.upper_bound(1);
	builtin_time = clock() - builtin_time;
	compare_time("mine.upper_bound(1)", builtin_time, my_time);

	my_time = clock();
	mine.equal_range(2);
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.equal_range(2);
	builtin_time = clock() - builtin_time;
	compare_time("mine.equal_range(2)", builtin_time, my_time);

	my_time = clock();
	mine.clear();
	my_time = clock() - my_time;

	builtin_time = clock();
	builtin.clear();
	builtin_time = clock() - builtin_time;
	compare_time("mine.clear()", builtin_time, my_time);
}