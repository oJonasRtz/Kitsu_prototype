#include "built-ins.hpp"
#include <fstream>
#include <unordered_map>
#include "keywords.hpp"

const std::unordered_map<t_keywords, std::string> var_mapping = {
	{TOKEN_NUM, "long long int"},
	{TOKEN_STRING, "std::string"},
	{TOKEN_DECIMAL, "long double"},
	{TOKEN_BOOL, "bool"},
};

const std::unordered_map<t_keywords, const std::string(*)(const std::vector<std::string> &)> call_mapping = {
	{TOKEN_PRINTLN, println},
	{TOKEN_PRINT, print},
	{TOKEN_EPRINTLN, eprintln},
	{TOKEN_EPRINT, eprint},
};

void code_generator(const t_code &code)
{
	std::ofstream file("main.cpp");


	file << "#include <iostream>\n\n";
	file << "int main() {\n";
	for (const auto &var : code.variables)
	{
		file << "    " << var_mapping.at(var.type) << " " << var.name;
		if (!var.value.empty())
			file << " = " << var.value;
		file << ";\n";
	}

	for (const auto &call : code.calls)
	{
		if (call_mapping.find(call.type) != call_mapping.end())
		{
			file << "    " << call_mapping.at(call.type)(call.args) << ";\n";
		}
	}
	file << "    return 0;\n";
	file << "}\n";

	file.close();

	//call gcc
	std::system("g++ main.cpp -o main");
}