#include <iostream> // TODO remove temporal dependency
#include <vector>

#include "scm/scm.h"
#include "scm/lexer.h"
#include "scm/parser.h"

using namespace scm;
using namespace std;

string scm::read(string input) {
    vector<token> tokens = tokenize(input);

    for (token t : tokens) {
        cout << t << '\n';
    }

    optional<shared_ptr<s_expr>> s = parse(tokens);
    cout << s.value() << '\n';
    return "";
}
