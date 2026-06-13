#include "built-ins.hpp"
#include <fstream>

void code_generator(const t_code &code)
{
	std::ofstream file("main.cpp");

	file << "#include <iostream>\n\n";
	file << "int main() {\n";
	for (const auto &var : code.variables) {
		file << "    " << (var.is_const ? "const " : "");
		switch (var.type) {
			case TOKEN_NUM:
				file << "long long int";
				break;
			case TOKEN_STRING:
				file << "std::string ";
				break;
			case TOKEN_DECIMAL:
				file << "long double ";
				break;
			case TOKEN_BOOL:
				file << "bool ";
				break;
			default:
				file << "auto ";
				break;
		}
		file << " " << var.name << " = " << var.value << ";\n";
	}
	for (const auto &println_call : code.println_calls) {
		file << "    std::cout << " << println_call.target << " << std::endl;\n";
	}

	file << "}\n";

	file.close();

	//call gcc
	std::system("g++ main.cpp -o main");
}