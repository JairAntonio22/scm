#include <utility>

#include "scm/parser.h"

using namespace std;

s_expr::s_expr(string atom): atom(atom) {}

s_expr::s_expr(shared_ptr<s_expr> car, shared_ptr<s_expr> cdr):
    car(car), cdr(cdr){}

ostream& operator << (ostream& os, shared_ptr<s_expr> s) {
    if (s->atom) {
        return os << s->atom.value();
    }

    os << '(';

    for (shared_ptr<s_expr> it = s; it != nullptr; it = it->cdr) {
        os << it->car;

        if (it->cdr != nullptr) {
            os << ' ';
        }
    }

    return os << ')';
}

optional<shared_ptr<s_expr>> parse(vector<token> tokens) {
    shared_ptr<s_expr> root;
    size_t nest = 0;

    for (token t : tokens) {
        switch (t.type) {
            case token_type::LPAREN: {
                nest++;
            } break;

            case token_type::RPAREN: {
                nest--;
            } break;

            case token_type::ID: {
                root = make_shared<s_expr>(t.literal);
                return root;
            } break;

            default:
                continue;
        }

        if (nest < 0) {
            return nullopt;
        }
    }

    return root;
}
