#ifndef SCM_PARSER_H
#define SCM_PARSER_H

#include <optional>
#include <memory>

#include "scm/lexer.h"

class s_expr;
using s_expr_ptr = std::shared_ptr<s_expr>;

class s_expr {
    std::string atom;
    s_expr_ptr car;
    s_expr_ptr cdr;

public:
    s_expr(std::string atom);

    s_expr(std::pair<s_expr_ptr, s_expr_ptr> pair);

    std::optional<std::string> get_atom();

    std::optional<std::pair<s_expr_ptr, s_expr_ptr>> get_pair();
};

std::ostream& operator << (std::ostream& stream, s_expr_ptr expr);

s_expr_ptr parse(std::queue<token> &tokens);

#endif
