#include <iostream>
#include <queue>

#include "scm/scm.h"
#include "scm/read.h"

using namespace scm;
using namespace std;

expr::expr(string atom):
    m_atom(std::move(atom))
{}

expr::expr(unique_ptr<expr> car, unique_ptr<expr> cdr): // NOLINT
    m_car(std::move(car)),
    m_cdr(std::move(cdr))
{}

auto expr::atom() -> string {
    return m_atom;
}

auto expr::car() -> expr* {
    return m_car.get();
}

auto expr::cdr() -> expr* {
    return m_cdr.get();
}

auto scm::operator << (ostream& stream, expr* expr) -> ostream& {
    if (expr == nullptr) {
        stream << "()";
    }

    if (!expr->atom().empty()) {
        return stream << expr->atom();
    }

    stream << '(' << expr->car();

    for (auto* iter = expr->cdr(); iter != nullptr; iter = iter->cdr()) {
        stream << ' ' << iter->car(); 
    }

    return stream << ')';
}

auto scm::read(string input) -> unique_ptr<expr> {
    queue<token> tokens = tokenize(input);
    return parse_expr(tokens);
}

auto scm::eval(unique_ptr<expr> input) -> unique_ptr<expr> {
    return input;
}
