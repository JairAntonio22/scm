#ifndef SCM_LEXER_H
#define SCM_LEXER_H

#include <sstream>
#include <vector>
#include <unordered_map>

enum class token_type {
    ID, BOOL, NUMBER, CHAR, STRING, LPAREN, RPAREN, 
};

struct token {
    std::string literal;
    token_type type;

    token(std::string literal, token_type type);
};

std::ostream& operator << (std::ostream& os, token t);

std::vector<token> tokenize(std::string input);

#endif
