#include "BadKitty.class.hpp"
#include <fstream>

static std::string type_to_string(t_variable_type type) {
	switch (type) {
		case TYPE_NUM: return "num";
		case TYPE_STRING: return "string";
		case TYPE_DECIMAL: return "decimal";
		case TYPE_BOOL: return "bool";
		default: return "unknown";
	}
}

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

	// t_code logic here (e.g., optimization, code generation, etc.)
	std::string output;
	for (const auto& code : codes)
	{
		for (const auto& var : code.variables)
			output += (var.is_const ? "const " : "var ") + var.name + ": " + type_to_string(var.type) + " = " + var.value + ";\n";
		for (const auto& call : code.calls)
		{
			output += call.name + "(";
			for (size_t i = 0; i < call.args.size(); ++i)
			{
				output += call.args[i];
				if (i < call.args.size() - 1)
					output += ", ";
			}
			output += ");\n";
		}		
	}
	std::ofstream output_file("t_code.log");
	output_file << output;
	output_file.close();

	return true;
}
