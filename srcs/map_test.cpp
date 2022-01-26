#include "Map.hpp"
#include "main.hpp"
#include "TestUtils.hpp"
#include <map>
#include "main.hpp"

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
			std::cout << RED << message << " [FAIL], Should throw error" << RESET << std::endl;
		else
			std::cout << GREEN << message << " [PASS], Initialization successful" << RESET << std::endl;
	}
	catch (const std::exception& )
	{
		if (will_throw)
			std::cout << GREEN << message << " [PASS], should throw error" << RESET << std::endl;
		else
			std::cout << RED << message << " [FAIL], Initialization failed " << RESET << std::endl;
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

	std::cout << "==========Iterator and operation test==============\n";
	std::map<int, std::string> builtin;
	ft::Map<int, std::string> mine;
	// std::cout << mine.begin()->first << "\n";
	// std::cout << mine.begin()->second << "\n";
	test_line("mine.insert(ft::make_pair(1, \"one\")).second ", builtin.insert(std::make_pair(1, "one")).second, mine.insert(ft::make_pair(1, "one")).second);
	test_line("mine.begin()->first", builtin.begin()->first, mine.begin()->first);
	test_line("mine.begin()->second", builtin.begin()->second, mine.begin()->second);
	test_line("mine.insert(ft::make_pair(2, \"two\")).second ", builtin.insert(std::make_pair(2, "two")).second, mine.insert(ft::make_pair(2, "two")).second);
	test_line("mine.begin()->first", builtin.begin()->first, mine.begin()->first);
	test_line("mine.begin()->second", builtin.begin()->second, mine.begin()->second);
	builtin.insert(std::make_pair(1, "two"));
	builtin.insert(std::make_pair(1, "three"));
	std::cout << builtin.find(1)->second << "\n";
	// std::cout << builtin.insert(std::make_pair(1, 1.0)).second << "\n";
}