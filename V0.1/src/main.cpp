#include <iostream>
#include "BadKitty.class.hpp"
#include "utils.hpp"

int main(int ac, char **av)
{
	if (ac < 2) {
		std::cout << "Usage: " << av[0] << " <source_files...>" << std::endl;
		return 1;
	}

	if (!check_files_extension(std::vector<std::string>(av + 1, av + ac)))
		return 1;

	if (!BadKitty::compile(std::vector<std::string>(av + 1, av + ac))) {
		std::cerr << "Compilation failed." << std::endl;
		return 1;
	}

	return 0;
}
