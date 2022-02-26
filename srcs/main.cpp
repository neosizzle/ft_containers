#include "Map.hpp"
#include "Set.hpp"
#include "Vector.hpp"
#include "main.hpp"
#include "MapTests.hpp"
#include "SetTests.hpp"
#include "VectorTests.hpp"
int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "usage : ./a.out [container]\n";
		return 1;
	}
	if (std::string(argv[1]).compare(std::string("map")) == 0)
		run_map_tests();
	else if (std::string(argv[1]).compare(std::string("set")) == 0)
		run_set_tests();
	else if (std::string(argv[1]).compare(std::string("vector")) == 0)
		run_vector_tests();
	else
		std::cout << "no such container\n";
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
