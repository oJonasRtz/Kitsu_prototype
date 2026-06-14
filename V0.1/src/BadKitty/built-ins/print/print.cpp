#include "BadKitty.class.hpp"

std::string BadKitty::print(const std::vector<std::string> &args) {
	std::string result = "std::cout ";

	for (const auto &arg : args)
		result += "<< " + arg;

	if (!result.empty())
		result += ";";

	return result;
}
