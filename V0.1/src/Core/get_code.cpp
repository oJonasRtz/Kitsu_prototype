#include "Core.class.hpp"

static bool handle_declaration(const std::vector<t_token> &tokens, t_code &code, size_t &i, const std::string &origin = "") {
	if (tokens[i].type != TOKEN_DECLARATION)
		return false;

	t_variable var{};
	var.is_const = tokens[i].value == "const";
	var.origin.file = origin;
	var.origin.line = tokens[i].line;
	var.origin.column = tokens[i].column;

	const std::unordered_map<std::string, t_variable_type> type_map = {
		{"num", TYPE_NUM},
		{"string", TYPE_STRING},
		{"decimal", TYPE_DECIMAL},
		{"bool", TYPE_BOOL},
	};


	i++;
	while(i < tokens.size() && tokens[i].value != ";")
	{
		switch (tokens[i].type)
		{
			case TOKEN_IDENTIFIER:
				var.name = tokens[i].value;
				break;
			case TOKEN_TYPE:
				if (type_map.find(tokens[i].value) != type_map.end())
					var.type = type_map.at(tokens[i].value);
				else
					var.type = TYPE_UNKNOWN;
				break;

			case TOKEN_LITERAL:
				var.value = tokens[i].value;
				break;
			default:
				break;
		}
		i++;
	}

	code.variables.push_back(var);
	return true;
}

static bool handle_builtin(const std::vector<t_token> &tokens, t_code &code, size_t &i, const std::string &origin = "") 
{
	if (tokens[i].type != TOKEN_BUILTIN)
		return false;

	t_call call{};
	call.name = tokens[i].value;
	call.origin.file = origin;
	call.origin.line = tokens[i].line;
	call.origin.column = tokens[i].column;
	i++;

	while(i < tokens.size() && tokens[i].value != ";")
	{
		if (tokens[i].type == TOKEN_IDENTIFIER || tokens[i].type == TOKEN_LITERAL)
			call.args.push_back(tokens[i].value);
		i++;
	}
	code.calls.push_back(call);
	return true;
}

t_code KitsuCore::get_code(const std::string &source) {
	t_code code;

	// Code parsing logic goes here (similar to the code_reader in V0.0)
	// This will involve iterating through the tokens and building the t_code structure
	// based on variable declarations, function calls, etc.
	std::vector<t_token> tokens = KitsuCore::tokenize(source);

	size_t i = 0;
	while(i < tokens.size())
	{
		if (handle_declaration(tokens, code, i, source))
			continue;
		if (handle_builtin(tokens, code, i, source))
			continue;

		i++;
	}

	return code;
}
