#include "token.hpp"
#include <iostream>
#include <vector>
#include "built-ins.hpp"

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

int main(int ac, char **av)
{
	if (ac < 2) {
		std::cerr << "Usage: " << av[0] << " <source_files>" << std::endl;
		return 1;
	}

	if (!check_files_extension(std::vector<std::string>(av + 1, av + ac)))
		return 1;

	std::cout << "Files to compile:" << std::endl;
	for (int i = 1; i < ac; ++i) {
		std::cout << " - " << av[i] << std::endl;
	}

	std::vector<t_token> tokens = tokenize(av[1]);

	std::cout << "Tokens:" << std::endl;
	for (const auto &token : tokens) {
		std::cout << "Type: " << token_type_to_string(token.type)
				  << ", Value: " << token.value << std::endl;
	}

	t_code code = code_reader(tokens);

	std::cout << "Variables:" << std::endl;
	for (const auto &var : code.variables) {
		std::cout << "Name: " << var.name
				  << ", Type: " << token_type_to_string(var.type)
				  << ", Const: " << (var.is_const ? "true" : "false") << std::endl;
	}

	std::cout << "Println calls:" << std::endl;
	for (const auto &println_call : code.println_calls) {
		std::cout << "Target: " << println_call.target << std::endl;
	}

	code_generator(code);

	return 0;
}