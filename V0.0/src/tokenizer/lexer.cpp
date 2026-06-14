#include "token.hpp"
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

const char *token_type_to_string(t_keywords type)
{
	switch (type) {
		case TOKEN_VAR:
			return "TOKEN_VAR";
		case TOKEN_CONST:
			return "TOKEN_CONST";

		case TOKEN_NUM:
			return "TOKEN_NUM";
		case TOKEN_STRING:
			return "TOKEN_STRING";
		case TOKEN_DECIMAL:
			return "TOKEN_DECIMAL";
		case TOKEN_BOOL:
			return "TOKEN_BOOL";

		case TOKEN_IDENTIFIER:
			return "TOKEN_IDENTIFIER";
		case TOKEN_VALUE:
			return "TOKEN_VALUE";

		case TOKEN_COLON:
			return "TOKEN_COLON";
		case TOKEN_EQUALS:
			return "TOKEN_EQUALS";
		case TOKEN_LPAREN:
			return "TOKEN_LPAREN";
		case TOKEN_RPAREN:
			return "TOKEN_RPAREN";
		case TOKEN_SEMICOLON:
			return "TOKEN_SEMICOLON";
		case TOKEN_COMMA:
			return "TOKEN_COMMA";

		case TOKEN_PRINTLN:
			return "TOKEN_PRINTLN";
	}

	return "UNKNOWN_TOKEN";
}

static void push_token(std::vector<t_token> &tokens, t_keywords type, const std::string &value)
{
	t_token token;
	token.type = type;
	token.value = value;
	tokens.push_back(token);
}

std::vector<t_token> tokenize(const std::string &source)
{
	std::vector<t_token> tokens;

	std::ifstream file(source);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file '" 
		          << source << "'." << std::endl;
		return tokens;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string code = buffer.str();

	for (size_t i = 0; i < code.size(); ) {
		unsigned char current = static_cast<unsigned char>(code[i]);

		if (std::isspace(current)) {
			++i;
			continue;
		}

		if (std::isalpha(current) || code[i] == '_') {
			std::string word;
			while (i < code.size()) {
				unsigned char c = static_cast<unsigned char>(code[i]);
				if (!std::isalnum(c) && code[i] != '_')
					break;
				word += code[i++];
			}

			auto it = keywords_map.find(word);
			if (it != keywords_map.end()) {
				push_token(tokens, it->second, word);
			} else if (word == "true" || word == "false") {
				push_token(tokens, TOKEN_VALUE, word);
			} else {
				push_token(tokens, TOKEN_IDENTIFIER, word);
			}
			continue;
		}

		if (std::isdigit(current)) {
			std::string value;
			bool has_decimal = false;

			while (i < code.size()) {
				unsigned char c = static_cast<unsigned char>(code[i]);

				if (std::isdigit(c)) {
					value += code[i++];
					continue;
				}

				if (c == '.' && !has_decimal) {
					has_decimal = true;
					value += code[i++];
					continue;
				}

				break;
			}

			push_token(tokens, TOKEN_VALUE, value);
			continue;
		}

		if (code[i] == '"') {
			std::string text;

			text += code[i++]; 

			while (i < code.size() && code[i] != '"') {
				text += code[i++];
			}

			if (i < code.size()) {
				text += code[i++]; 
			}

			push_token(tokens, TOKEN_VALUE, text);
			continue;
		}

		switch (code[i]) {
			case ':':
				push_token(tokens, TOKEN_COLON, ":");
				break;
			case '=':
				push_token(tokens, TOKEN_EQUALS, "=");
				break;
			case '(':
				push_token(tokens, TOKEN_LPAREN, "(");
				break;
			case ')':
				push_token(tokens, TOKEN_RPAREN, ")");
				break;
			case ';':
				push_token(tokens, TOKEN_SEMICOLON, ";");
				break;
			case ',':
				push_token(tokens, TOKEN_COMMA, ",");
				break;
			default:
				std::cerr << "Error: Unexpected character '" << code[i]
				          << "'." << std::endl;
				return tokens;
		}

		++i;
	}


	file.close();
	return tokens;
}
