#ifndef TOKEN
#define TOKEN

#include "keywords.hpp"
#include <string>
#include <vector>

typedef struct {
	t_keywords	type;
	std::string	value;
}	t_token;

typedef struct {
	std::string name;
	std::string value;

	t_keywords type;
	bool is_const;
}	t_variable;


const char *token_type_to_string(t_keywords type);
std::vector<t_token> tokenize(const std::string &source);

#endif // TOKEN