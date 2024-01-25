#include <utility>

#include "scm/parser.h"

using namespace std;

s_expr::s_expr(string atom): atom(std::move(atom)) {}

s_expr::s_expr(pair<s_expr_ptr, s_expr_ptr> pair):
    car(get<0>(pair)), cdr(get<1>(pair)) {}

optional<string> s_expr::get_atom() {
    return atom.empty() ? nullopt : optional(atom);
}

optional<pair<s_expr_ptr, s_expr_ptr>> s_expr::get_pair() {
    return atom.empty() ? optional(make_pair(car, cdr)) : nullopt;
}

ostream& operator << (ostream& stream, shared_ptr<s_expr> expr) {
    if (expr == nullptr) {
        stream << "()";
    }

    if (auto atom = expr->get_atom(); atom.has_value()) {
        return stream << *atom;
    }

    stream << '(';

    /*
    for (shared_ptr<s_expr> it = expr; it != nullptr; it = it->cdr) {
        stream << it->car;

        if (it->cdr != nullptr) {
            stream << ' ';
        }
    }
    */

    return stream << ')';
}

shared_ptr<s_expr> parse(queue<token> &tokens) {
    shared_ptr<s_expr> root;
    size_t nest = 0;

    while (!tokens.empty()) {
        switch (token tok = tokens.front(); tok.type) {
            case token_type::LPAREN: {
                nest++;
                tokens.pop();
            } break;

            case token_type::RPAREN: {
                nest--;
                tokens.pop();
            } break;

            case token_type::ID: {
                root = make_shared<s_expr>(tok.literal);
                return root;
            } break;

            default:
                tokens.pop();
                continue;
        }

        if (nest < 0) {
            return nullptr;
        }
    }

    return root;
}
