#include "BadKitty.class.hpp"

std::string BadKitty::transpile(const std::vector<t_code> &code) {
	(void)code; // Suppress unused parameter warning
	return {};
}

bool BadKitty::compile(
	const std::vector<std::string>  &source_files,
	const t_options &options
) {
	std::vector<t_code> codes;

	(void)options; // Suppress unused parameter warning

	for (const auto &file : source_files) {
		t_code code = KitsuCore::get_code(file);
		codes.push_back(code);
	}

	// const std::string cpp_files = BadKitty::transpile(codes);

	// std::system("g++ " + cpp_files + " -o " + options.output_file);
	return true;
}
