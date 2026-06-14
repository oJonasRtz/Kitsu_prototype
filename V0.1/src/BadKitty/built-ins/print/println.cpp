#include "BadKitty.class.hpp"

std::string BadKitty::println(const std::vector<std::string> &args) {
	std::string result = "std::cout ";

	for (const auto &arg : args)
		result += "<< " + arg;

	if (!result.empty())
		result += " << std::endl;";

	return result;
}
