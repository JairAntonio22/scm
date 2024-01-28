#ifndef SCM_LEXER_H
#define SCM_LEXER_H

#include <sstream>
#include <string>
#include <queue>

enum class token_type {
    ID, LPAREN, RPAREN, 
};

auto to_string(token_type type) -> std::string;

struct token {
    std::string literal;
    token_type type;
};

auto operator << (std::ostream& stream, token token) -> std::ostream&;

auto tokenize(std::string input) -> std::queue<token>;

#endif
