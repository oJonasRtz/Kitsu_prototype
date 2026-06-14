#ifndef BUILT_INS_HPP
#define BUILT_INS_HPP

#include "token.hpp"
#include <string>
#include <vector>

typedef struct {
	t_keywords	type;

	std::vector<std::string> args;
}	t_call;

typedef struct {
	std::vector<t_variable> variables;

	std::vector<t_call> calls;
}	t_code;

t_code	code_reader(const std::vector<t_token> &tokens);
void code_generator(const t_code &code);

// built-in functions
const std::string	println(const std::vector<std::string> &args);
const std::string	print(const std::vector<std::string> &args);
const std::string	eprintln(const std::vector<std::string> &args);
const std::string	eprint(const std::vector<std::string> &args);

#endif // BUILT_INS_HPP