#ifndef SCM_PARSER_H
#define SCM_PARSER_H

#include <string>
#include <optional>
#include <memory>

#include "scm/lexer.h"

class expr {
    std::string m_atom;
    std::unique_ptr<expr> m_car = nullptr;
    std::unique_ptr<expr> m_cdr = nullptr;

public:
    expr(std::string atom);

    expr(std::unique_ptr<expr> car, std::unique_ptr<expr> cdr);

    auto atom() -> std::string;

    auto car() -> expr*;

    auto cdr() -> expr*;
};

auto operator << (std::ostream& stream, expr* expr) -> std::ostream&;

auto parse_expr(std::queue<token> &tokens) -> std::unique_ptr<expr>;

#endif
