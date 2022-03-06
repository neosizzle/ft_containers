#include "main.hpp"
#include "MapTests.hpp"
#include "SetTests.hpp"
#include "VectorTests.hpp"
#include "StackTests.hpp"
#include "SfinaeTests.hpp"
#include "Utils.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage : " << argv[0] << " map | set | vector | sfinae\n";
		return 1;
	}
	if (std::string(argv[1]).compare(std::string("map")) == 0)
		run_map_tests();
	else if (std::string(argv[1]).compare(std::string("set")) == 0)
		run_set_tests();
	else if (std::string(argv[1]).compare(std::string("vector")) == 0)
		run_vector_tests();
	else if (std::string(argv[1]).compare(std::string("sfinae")) == 0)
		run_sfinae_tests();
	else if (std::string(argv[1]).compare(std::string("stack")) == 0)
		run_stack_tests();
	else
		std::cout << "Usage : " << argv[0] << " map | set | vector | sfinae\n";
}
