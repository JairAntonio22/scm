
#include <sstream>
#include <utility>
#include <cctype>
#include <stack>

#include "scm/read.h"
#include "log/log.h"

using namespace std;
using namespace scm;

auto to_string(token_type type) -> string {
    switch (type) {
        case token_type::LPAREN: return "LPAREN";
        case token_type::RPAREN: return "RPAREN";
        case token_type::ID:     return "ID";
    }
}

static auto isidentifier(char chr) -> bool {
    static const string extended_chars = "!$%&*+-./:<=>?@^_~";
    return bool(isalnum(chr)) || extended_chars.find(chr) != string::npos;
}

auto tokenize(string input) -> queue<token> {
    istringstream iss(input);
    queue<token> tokens;

    while (!iss.eof()) {
        if (char chr = char(iss.peek()); chr == '(') {
            tokens.push({string(1, char(iss.get())), token_type::LPAREN});

        } else if (chr == ')') {
            tokens.push({string(1, char(iss.get())), token_type::RPAREN});

        } else if (isidentifier(chr)) {
            ostringstream oss;

            do {
                oss.put(char(iss.get()));
            } while (isidentifier(char(iss.peek())));

            tokens.push({oss.str(), token_type::ID});

        } else {
            iss.ignore();
        }
    }

    return tokens;
}

static auto parse_list(queue<token> &tokens) -> unique_ptr<expr>;

auto parse_expr(queue<token> &tokens) -> unique_ptr<expr> {
    if (tokens.empty()) {
        return nullptr;
    }

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
            tokens.pop();
            return make_unique<expr>(token.literal);
    }
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
