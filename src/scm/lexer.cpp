#include "scm/lexer.h"

#include <sstream>
#include <cctype>
#include <unordered_map>

using namespace std;

token::token(string literal, token_type type):
    literal(literal), type(type) {}

ostream& operator << (ostream& os, token t) {
    os << t.literal << '\t';

    switch (t.type) {
        case token_type::LPAREN: return os << "LPAREN";
        case token_type::RPAREN: return os << "RPAREN";
        case token_type::ID:     return os << "ID";
        default:                 return os;
    }
}

static bool isidentifier(char c) {
    static const string extended_chars = "!$%&*+-./:<=>?@^_~";
    return isalnum(c) || extended_chars.find(c) != string::npos;
}

vector<token> tokenize(string input) {
    istringstream iss(input);
    vector<token> tokens;

    while (!iss.eof()) {
        if (char c = iss.peek(); isspace(c)) {
            iss.ignore();

        } else if (c == '(') {
            tokens.emplace_back(string(1, iss.get()), token_type::LPAREN);

        } else if (c == ')') {
            tokens.emplace_back(string(1, iss.get()), token_type::RPAREN);

        } else if (isidentifier(c)) {
            ostringstream oss;

            do {
                oss.put(iss.get());
            } while (isidentifier(iss.peek()));

            tokens.emplace_back(oss.str(), token_type::ID);

        } else {
            iss.ignore();
        }
    }

    return tokens;
}
