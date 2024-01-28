#include <utility>
#include <stack>

#include "scm/parser.h"
#include "log/log.h"

using namespace std;

expr::expr(string atom):
    m_atom(std::move(atom)) {}

expr::expr(unique_ptr<expr> car, unique_ptr<expr> cdr): // NOLINT
    m_car(std::move(car)), m_cdr(std::move(cdr)) {}

auto expr::atom() -> string {
    return m_atom;
}

auto expr::car() -> expr* {
    return m_car.get();
}

auto expr::cdr() -> expr* {
    return m_cdr.get();
}

auto operator << (ostream& stream, expr* expr) -> ostream& {
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

static auto parse_list(queue<token> &tokens) -> unique_ptr<expr>;

auto parse_expr(queue<token> &tokens) -> unique_ptr<expr> {
    while (!tokens.empty()) {
        switch (token token = tokens.front(); token.type) {
            case token_type::RPAREN: {
                log::error("expecting identifier or '(', given ')'");
                return nullptr;
            }

            case token_type::LPAREN: {
                tokens.pop();
                return parse_list(tokens);
            }

            default:
                unique_ptr<expr> root = make_unique<expr>(token.literal);
                tokens.pop();
                return root;
        }
    }

    return nullptr;
}

static auto parse_list(queue<token> &tokens) -> unique_ptr<expr> {
    while (!tokens.empty()) {
        if (tokens.front().type == token_type::RPAREN) {
            tokens.pop();
            return nullptr;
        }

        unique_ptr<expr> car = parse_expr(tokens);
        unique_ptr<expr> cdr = parse_list(tokens);
        return make_unique<expr>(std::move(car), std::move(cdr));
    }

    return nullptr;
}
