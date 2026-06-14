#include "BadKitty.class.hpp"

std::string BadKitty::eprint(const std::vector<std::string> &args) {
	std::string result;

	result += "std::cerr ";
	for (const auto &arg : args)
		result += "<< " + arg;

	if (!result.empty())
		result += ";";

	return result;
}
