#include "scm/lexer.h"

#include <sstream>
#include <cctype>
#include <unordered_map>

using namespace std;

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
