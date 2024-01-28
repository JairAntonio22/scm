#include <iostream>
#include <queue>

#include "scm/scm.h"
#include "scm/lexer.h"
#include "scm/parser.h"

using namespace scm;
using namespace std;

auto scm::read(string input) -> string {
    queue<token> tokens = tokenize(input);
    unique_ptr<expr> expr = parse_expr(tokens);
    cout << expr << '\n';
    return "";
}
