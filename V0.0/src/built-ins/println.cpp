#include <string>
#include <vector>

const std::string	println(const std::vector<std::string> &args)
{
	std::string result = "std::cout << ";
	for (size_t i = 0; i < args.size(); ++i) {
		result += args[i];
		if (i < args.size() - 1) {
			result += " << ";
		}
	}
	result += " << std::endl";

	return result;
}
