#ifndef SCM_READ_H
#define SCM_READ_H

#include <memory>
#include <sstream>
#include <optional>
#include <string>
#include <queue>

#include "scm/scm.h"

enum class token_type {
    ID, LPAREN, RPAREN, 
};

auto to_string(token_type type) -> std::string;

struct token {
    std::string literal;
    token_type type;
};

auto tokenize(std::string input) -> std::queue<token>;

auto parse_expr(std::queue<token> &tokens) -> std::unique_ptr<scm::expr>;

#endif
