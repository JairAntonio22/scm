#include "scm/lexer.h"

#include <sstream>
#include <cctype>
#include <unordered_map>

using namespace std;

ostream& operator << (ostream& stream, token token) {
    stream << token.literal << '\t';

    switch (token.type) {
        case token_type::LPAREN: return stream << "LPAREN";
        case token_type::RPAREN: return stream << "RPAREN";
        case token_type::ID:     return stream << "ID";
        default:                 return stream;
    }
}

static bool isidentifier(char chr) {
    static const string extended_chars = "!$%&*+-./:<=>?@^_~";
    return bool(isalnum(chr)) || extended_chars.find(chr) != string::npos;
}

queue<token> tokenize(string input) {
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
