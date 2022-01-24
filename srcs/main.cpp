#include <iostream>
#include "Map.hpp"
int	main()
{
	ft::pair<int, int> pair = ft::make_pair(6, 9);
	ft::pair<int, int> pair2 = ft::make_pair(6, 9);
	ft::pair<int, int> pair3 = ft::make_pair(10, 9);
	ft::pair<int, int> pair4 = ft::make_pair(1, 9);
	std::cout << "pair made (6,9)\n";
	std::cout << "pair2 made (6,9)\n";
	std::cout << "pair3 made (10,9)\n";
	std::cout << "pair4 made (1,9)\n";
	std::cout << "pair.first " << pair.first << "\n";
	std::cout << "pair.second " << pair.second << "\n";
	std::cout << "pair == pair2 " << (pair == pair2) << "\n";
	std::cout << "pair >= pair2 " << (pair >= pair2) << "\n";
	std::cout << "pair <= pair2 " << (pair <= pair2) << "\n";
	std::cout << "pair != pair2 " << (pair != pair2) << "\n";
	std::cout << "pair < pair2 " << (pair < pair2) << "\n";
	std::cout << "pair > pair2 " << (pair > pair2) << "\n";
	std::cout << "pair3 > pair4 " << (pair3 > pair4) << "\n";
	std::cout << "pair4 < pair3 " << (pair4 < pair3) << "\n";
	std::cout << GREEN << "hello world" << RESET << std::endl;
}
