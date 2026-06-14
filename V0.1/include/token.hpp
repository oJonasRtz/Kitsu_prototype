#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

typedef enum {
    TOKEN_TYPE,
    TOKEN_DECLARATION,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL,
    TOKEN_SYMBOL,
    TOKEN_BUILTIN,
	TOKEN_KEYWORD,
	TOKEN_OPERATOR,
}	t_token_type;

typedef struct {
	t_token_type	type;

	const std::string value;
}	t_token;

#include <unordered_map>
static const std::unordered_map<std::string, t_token_type> token_map = {
	// Readability declarations
	{"var", TOKEN_DECLARATION},
	{"const", TOKEN_DECLARATION},
	
	// Types
	{"num", TOKEN_TYPE},
	{"string", TOKEN_TYPE},
	{"decimal", TOKEN_TYPE},
	{"bool", TOKEN_TYPE},
	{"none", TOKEN_TYPE},

	//keywords
	{"export", TOKEN_KEYWORD},
	{"if", TOKEN_KEYWORD},
	{"else", TOKEN_KEYWORD},
	{"fn", TOKEN_KEYWORD},
	{"return", TOKEN_KEYWORD},

	// built-in functions
	{"println", TOKEN_BUILTIN},
	{"print", TOKEN_BUILTIN},
	{"eprintln", TOKEN_BUILTIN},
	{"eprint", TOKEN_BUILTIN},

	// Markers
	{":", TOKEN_SYMBOL},
	{"(", TOKEN_SYMBOL},
	{")", TOKEN_SYMBOL},
	{";", TOKEN_SYMBOL},
	{",", TOKEN_SYMBOL},
	{"?", TOKEN_SYMBOL},
	{"{", TOKEN_SYMBOL},
	{"}", TOKEN_SYMBOL},
	{"[", TOKEN_SYMBOL},
	{"]", TOKEN_SYMBOL},
	{"?", TOKEN_SYMBOL},

	// Operators
		// Assignment
	{"=", TOKEN_OPERATOR},
	{"+=", TOKEN_OPERATOR},
	{"-=", TOKEN_OPERATOR},
	{"*=", TOKEN_OPERATOR},
	{"/=", TOKEN_OPERATOR},
	{"%=", TOKEN_OPERATOR},
	{"&=", TOKEN_OPERATOR},
	{"|=", TOKEN_OPERATOR},
	{"^=", TOKEN_OPERATOR},
	{"<<=", TOKEN_OPERATOR},
	{">>=", TOKEN_OPERATOR},

		// Arithmetic
	{"+", TOKEN_OPERATOR},
	{"-", TOKEN_OPERATOR},
	{"*", TOKEN_OPERATOR},
	{"/", TOKEN_OPERATOR},
	{"%", TOKEN_OPERATOR},

		// Logical
	{"<", TOKEN_OPERATOR},
	{">", TOKEN_OPERATOR},
	{"!", TOKEN_OPERATOR},
	{"&&", TOKEN_OPERATOR},
	{"||", TOKEN_OPERATOR},
	{"==", TOKEN_OPERATOR},
	{"!=", TOKEN_OPERATOR},
	{">=", TOKEN_OPERATOR},
	{"<=", TOKEN_OPERATOR},

		// bitwise
	{"&", TOKEN_OPERATOR},
	{"|", TOKEN_OPERATOR},
	{"^", TOKEN_OPERATOR},
	{"<<", TOKEN_OPERATOR},
	{">>", TOKEN_OPERATOR},
	{"~", TOKEN_OPERATOR},
};

#endif // TOKEN_HPP