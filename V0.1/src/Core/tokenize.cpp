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
		{TOKEN_OPERATOR, "TOKEN_OPERATOR"},
	};

	auto it = token_type_strings.find(token.type);
	if (it != token_type_strings.end())
		return it->second;

	return "UNKNOWN_TOKEN: " + token.value;
}

static void push_token(std::vector<t_token> &tokens, t_token_type type, const std::string &value) {
	tokens.push_back({type, value});
}

std::vector<t_token> KitsuCore::tokenize(const std::string &source)
{
    std::vector<t_token> tokens;

    std::ifstream file(source);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + source);

    std::string code((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    size_t i = 0;

    while (i < code.size())
    {
        if (std::isspace(code[i]))
        {
            ++i;
            continue;
        }

        std::string match;
        t_token_type type;
        bool found = false;

        /*
        ======================================================
        1. TRY MAXIMAL MATCH FROM TOKEN MAP (operators/symbols)
        ======================================================
        */
        for (int len = 3; len > 0; --len)
        {
            if (i + len > code.size())
                continue;

            std::string candidate = code.substr(i, len);

            auto it = token_map.find(candidate);
            if (it != token_map.end())
            {
                match = candidate;
                type = it->second;
                i += len;
                found = true;
                break;
            }
        }

        if (found)
        {
            push_token(tokens, type, match);
            continue;
        }

        /*
        =====================
        2. STRING LITERAL
        =====================
        */
        if (code[i] == '"')
        {
            size_t start = i++;
            while (i < code.size() && code[i] != '"')
                ++i;

            if (i < code.size())
                ++i;

            push_token(tokens, TOKEN_LITERAL,
                        code.substr(start, i - start));
            continue;
        }

        /*
        =====================
        3. NUMBER
        =====================
        */
        if (std::isdigit(code[i]))
        {
            size_t start = i;
            bool dot = false;

            while (i < code.size())
            {
                if (std::isdigit(code[i]))
                    ++i;
                else if (code[i] == '.' && !dot)
                {
                    dot = true;
                    ++i;
                }
                else
                    break;
            }

            push_token(tokens, TOKEN_LITERAL,
                        code.substr(start, i - start));
            continue;
        }

        /*
        =====================
        4. WORD (IDENT / KEYWORD)
        =====================
        */
        if (std::isalpha(code[i]) || code[i] == '_')
        {
            size_t start = i;

            while (i < code.size() &&
                  (std::isalnum(code[i]) || code[i] == '_'))
                ++i;

            std::string word = code.substr(start, i - start);

            auto it = token_map.find(word);
            if (it != token_map.end())
                push_token(tokens, it->second, word);
            else if (word == "true" || word == "false")
                push_token(tokens, TOKEN_LITERAL, word);
            else
                push_token(tokens, TOKEN_IDENTIFIER, word);

            continue;
        }

        /*
        =====================
        5. FALLBACK SAFETY
        =====================
        */
        push_token(tokens, TOKEN_IDENTIFIER, std::string(1, code[i]));
        ++i;
    }

    /*
    =====================
    DEBUG LOG
    =====================
    */
    std::string log;
    for (const auto &t : tokens)
        log += token_to_string(t) + " : " + t.value + "\n";

    std::ofstream log_file("tokens.log");
    if (log_file.is_open())
        log_file << log;
    else
        std::cerr << "Could not open log file\n";

    return tokens;
}