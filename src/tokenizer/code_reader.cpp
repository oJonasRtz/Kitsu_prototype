#include "built-ins.hpp"

t_code	code_reader(const std::vector<t_token> &tokens)
{
	t_code code;

	size_t i = 0;

	while (i < tokens.size())
	{
		if (tokens[i].type == TOKEN_VAR || tokens[i].type == TOKEN_CONST)
		{
			t_variable var{};
			var.is_const = (tokens[i].type == TOKEN_CONST);

			i++;

			while (i < tokens.size() && tokens[i].type != TOKEN_SEMICOLON)
			{
				switch (tokens[i].type)
				{
					case TOKEN_IDENTIFIER:
						var.name = tokens[i].value;
						break;

					case TOKEN_NUM:
					case TOKEN_STRING:
					case TOKEN_DECIMAL:
					case TOKEN_BOOL:
						var.type = tokens[i].type;
						break;

					case TOKEN_VALUE:
						var.value = tokens[i].value;
						break;

					default:
						break;
				}

				i++;
			}

			code.variables.push_back(var);
		}
		else if (tokens[i].type == TOKEN_PRINTLN)
		{
			t_println println{};

			i++;

			while (i < tokens.size() && tokens[i].type != TOKEN_SEMICOLON)
			{
				if (tokens[i].type == TOKEN_IDENTIFIER ||
					tokens[i].type == TOKEN_VALUE)
				{
					println.target = tokens[i].value;
				}

				i++;
			}

			code.println_calls.push_back(println);
		}

		i++;
	}
	return code;
}
