#include "Core.class.hpp"
#include <fstream>
#include <iostream>

std::string token_to_string(const t_token &token)
{
	const std::unordered_map<t_token_type, std::string> token_type_strings = {
		{TOKEN_TYPE, "TOKEN_TYPE"},
		{TOKEN_DECLARATION, "TOKEN_DECLARATION"},
		{TOKEN_IDENTIFIER, "TOKEN_IDENTIFIER"},
		{TOKEN_LITERAL, "TOKEN_LITERAL"},
		{TOKEN_SYMBOL, "TOKEN_SYMBOL"},
		{TOKEN_BUILTIN, "TOKEN_BUILTIN"},
		{TOKEN_KEYWORD, "TOKEN_KEYWORD"},
	};

	auto it = token_type_strings.find(token.type);
	if (it != token_type_strings.end())
		return it->second;

	return "UNKNOWN_TOKEN: " + token.value;
}

static bool	issign(unsigned char c) {
	return c == ':' || c == '='
		|| c == '(' || c == ')'
		|| c == ';' || c == ','
		|| c == '+' || c == '-'
		|| c == '*' || c == '/'
		|| c == '%'
		|| c == '!' || c == '&'
		|| c == '|' || c == '^'
		|| c == '<' || c == '>'
		|| c == '{' || c == '}';
}

static void push_token(std::vector<t_token> &tokens, t_token_type type, const std::string &value) {
	tokens.push_back({type, value});
}

std::vector<t_token> KitsuCore::tokenize(const std::string &source)
{
	std::vector<t_token> tokens;

	// open file
	std::ifstream file(source);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + source);
	}

	std::string code((std::istreambuf_iterator<char>(file)),
					 std::istreambuf_iterator<char>());

	// Tokenization logic goes here (similar to the lexer in V0.0)
	for (size_t i = 0; i < code.size(); )
	{
		unsigned char current = static_cast<unsigned char>(code[i]);

		if (std::isspace(current)) {
			++i;
			continue;
		}

		// Taking signs
		if (issign(current)) {
			std::string symbol(1, code[i++]);
			push_token(tokens, TOKEN_SYMBOL, symbol);
			continue;
		}

		// Taking strings
		if (code[i] == '"')
		{
			std::string literal;
			literal += code[i++]; // include the opening quote

			while (i < code.size() && code[i] != '"')
				literal += code[i++];

			if (i < code.size())
				literal += code[i++]; // include the closing quote

			push_token(tokens, TOKEN_LITERAL, literal);
			continue;
		}

		// Taking digits
		if (std::isdigit(current))
		{
			std::string number;
			bool has_decimal = false;

			while (i < code.size()) {
				unsigned char c = static_cast<unsigned char>(code[i]);

				if (std::isdigit(c)) {
					number += code[i++];
					continue;
				}

				if (c == '.' && !has_decimal) {
					has_decimal = true;
					number += code[i++];
					continue;
				}

				break;
			}

			push_token(tokens, TOKEN_LITERAL, number);
			continue;
		}

		// Taking words (identifiers, keywords)
		if (std::isalpha(current) || current == '_')
		{
			std::string word;
			while (i < code.size()) {
				unsigned char c = static_cast<unsigned char>(code[i]);
				if (!std::isalnum(c) && c != '_')
					break;
				word += code[i++];
			}

			auto it = token_map.find(word);
			if (it != token_map.end())
				push_token(tokens, it->second, word);
			else if (word == "true" || word == "false")
				push_token(tokens, TOKEN_LITERAL, word);
			else
				push_token(tokens, TOKEN_IDENTIFIER, word);
			continue;
		}
	}

	// Print Tokens for debugging
	std::string log;
	for (const auto &token : tokens)
		log += token_to_string(token) + " : " + token.value + "\n";
	std::ofstream log_file("tokens.log");
	if (log_file.is_open())
		log_file << log;
	else
		std::cerr << "Could not open log file for writing." << std::endl;
	log_file.close();

	file.close();
	return tokens;
}
