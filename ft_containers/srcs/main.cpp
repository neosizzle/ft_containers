#include <iostream>
#include "util.hpp"
int	main()
{
	int	data;
	std::string	str;

	data = 12345;
	str = ft::to_string(data);
	std::cout << str[0];
}
