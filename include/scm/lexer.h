#ifndef SCM_LEXER_H
#define SCM_LEXER_H

#include <sstream>
#include <queue>

enum class token_type {
    ID, BOOL, NUMBER, CHAR, STRING, LPAREN, RPAREN, 
};

struct token {
    std::string literal;
    token_type type;
};

std::ostream& operator << (std::ostream& stream, token token);

std::queue<token> tokenize(std::string input);

#endif
