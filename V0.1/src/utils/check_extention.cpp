#include "utils.hpp"

bool check_files_extension(const std::vector<std::string> &files)
{
	const std::string extension = ".kit";

	for (const auto &file : files) {
		if (file.size() < extension.size() ||
			file.substr(file.size() - extension.size()) != extension) {
			std::cerr << "Error: File '" << file << "' does not have the '"
					  << extension << "' extension." << std::endl;
			return false;
		}
	}
	return true;
}
