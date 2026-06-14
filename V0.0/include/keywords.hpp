#ifndef KEYWORDS_HPP
#define KEYWORDS_HPP

#include <unordered_map>
#include <string>

typedef enum {
	// Declaration
	TOKEN_VAR,
	TOKEN_CONST,

	// Types
	TOKEN_NUM,
	TOKEN_STRING,
	TOKEN_DECIMAL,
	TOKEN_BOOL,

	// Identifiers and literals
	TOKEN_IDENTIFIER,
	TOKEN_VALUE,

	// Symbols
	TOKEN_COLON,
	TOKEN_EQUALS,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_SEMICOLON,
	TOKEN_COMMA,

	// built-in functions
	TOKEN_PRINTLN,
	TOKEN_PRINT,
	TOKEN_EPRINTLN,
	TOKEN_EPRINT,
}	t_keywords;

static const std::unordered_map<std::string, t_keywords> keywords_map = {
	{"var", TOKEN_VAR},
	{"const", TOKEN_CONST},
	{"num", TOKEN_NUM},
	{"string", TOKEN_STRING},
	{"decimal", TOKEN_DECIMAL},
	{"bool", TOKEN_BOOL},
	{"println", TOKEN_PRINTLN},
	{"print", TOKEN_PRINT},
	{"eprintln", TOKEN_EPRINTLN},
	{"eprint", TOKEN_EPRINT},
};

#endif // KEYWORDS_HPP