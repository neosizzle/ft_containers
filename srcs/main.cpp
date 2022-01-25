#include "Map.hpp"
#include "main.hpp"

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
	if (expected == actual)
		std::cout << GREEN << cmd << " [PASS]" << RESET << std::endl;
	else
		std::cout << RED << cmd << " [FAIL] Different output" << std::endl;;
}

int	main()
{
	run_map_tests();
	//test_line_diffclass("1 + 1", m.get_allocator(), me.get_allocator());
	// ft::pair<int, int> pair = ft::make_pair(6, 9);
	// ft::pair<int, int> pair2 = ft::make_pair(6, 9);
	// ft::pair<int, int> pair3 = ft::make_pair(10, 9);
	// ft::pair<int, int> pair4 = ft::make_pair(1, 9);
	// std::cout << "pair made (6,9)\n";
	// std::cout << "pair2 made (6,9)\n";
	// std::cout << "pair3 made (10,9)\n";
	// std::cout << "pair4 made (1,9)\n";
	// std::cout << "pair.first " << pair.first << "\n";
	// std::cout << "pair.second " << pair.second << "\n";
	// std::cout << "pair == pair2 " << (pair == pair2) << "\n";
	// std::cout << "pair >= pair2 " << (pair >= pair2) << "\n";
	// std::cout << "pair <= pair2 " << (pair <= pair2) << "\n";
	// std::cout << "pair != pair2 " << (pair != pair2) << "\n";
	// std::cout << "pair < pair2 " << (pair < pair2) << "\n";
	// std::cout << "pair > pair2 " << (pair > pair2) << "\n";
	// std::cout << "pair3 > pair4 " << (pair3 > pair4) << "\n";
	// std::cout << "pair4 < pair3 " << (pair4 < pair3) << "\n";
	// std::cout << GREEN << "hello world" << RESET << std::endl;
}
