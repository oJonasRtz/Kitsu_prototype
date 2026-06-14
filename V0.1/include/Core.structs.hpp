#ifndef CORE_STRUCTS_HPP
#define CORE_STRUCTS_HPP

#include "token.hpp"
#include <vector>
#include <unordered_map>

typedef struct {
	std::string file;
	std::string function = "global";
	int line;
	int column;
}	t_location;

typedef struct {
	std::string					name;
	std::vector<std::string>	args;
	t_location					origin;
}	t_call;

typedef enum {
	TYPE_NUM,
	TYPE_STRING,
	TYPE_DECIMAL,
	TYPE_BOOL,
	TYPE_UNKNOWN,
}	t_variable_type;

typedef struct {
	std::string		name;
	std::string		value;
	t_variable_type	type;
	bool			is_const;
	t_location		origin;
}	t_variable;

typedef struct {
	std::vector<t_variable> variables;

	std::vector<t_call> calls;
}	t_code;

#endif // CORE_STRUCTS_HPP
