#ifndef BUILT_INS_HPP
#define BUILT_INS_HPP

#include "token.hpp"
#include <string>
#include <vector>

typedef struct {
	std::string target;
}	t_println;

typedef struct {
	std::vector<t_variable> variables;

	std::vector<t_println> println_calls;
}	t_code;

t_code	code_reader(const std::vector<t_token> &tokens);
void code_generator(const t_code &code);

#endif // BUILT_INS_HPP