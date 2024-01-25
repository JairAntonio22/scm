#include <iostream> // TODO remove temporal dependency
#include <queue>

#include "scm/scm.h"
#include "scm/lexer.h"
#include "scm/parser.h"

using namespace scm;
using namespace std;

string scm::read(string input) {
    queue<token> tokens = tokenize(input);

    queue<token> view(tokens);
    while (!view.empty()) {
        cout << view.front() << '\n';
        view.pop();
    }

    s_expr_ptr expr = parse(tokens);
    cout << expr << '\n';
    return "";
}
