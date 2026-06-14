#include "BadKitty.class.hpp"

std::string BadKitty::eprintln(const std::vector<std::string> &args) {
	std::string result = "std::cerr ";

	for (const auto &arg : args)
		result += "<< " + arg;

	if (!result.empty())
		result += " << std::endl;";

	return result;
}
