#include "Map.hpp"
#include "TestUtils.hpp"
#include <map>

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
	// std::cout << mine.find(1)->second << "\n";
	// std::cout << builtin.insert(std::make_pair(1, 1.0)).second << "\n";
}