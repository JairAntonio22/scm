#ifndef SCM_PARSER_H
#define SCM_PARSER_H

#include <optional>
#include <memory>

#include "scm/lexer.h"

struct s_expr {
    std::optional<std::string> atom;
    std::shared_ptr<s_expr> car;
    std::shared_ptr<s_expr> cdr;

    s_expr(std::string atom);

    s_expr(std::shared_ptr<s_expr> car, std::shared_ptr<s_expr> cdr);
};

std::ostream& operator << (std::ostream& os, std::shared_ptr<s_expr> s);

std::optional<std::shared_ptr<s_expr>> parse(std::vector<token> tokens);

#endif
