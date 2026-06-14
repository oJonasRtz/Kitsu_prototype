#include <string>
#include <vector>

const std::string	eprint(const std::vector<std::string> &args)
{
	std::string result = "std::cerr << ";
	for (size_t i = 0; i < args.size(); ++i) {
		result += args[i];
		if (i < args.size() - 1) {
			result += " << ";
		}
	}

	return result;
}