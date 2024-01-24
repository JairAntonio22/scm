#include <iostream>

#include "io/io.h"
#include "scm/scm.h"

using namespace io;
using namespace scm;
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    optional<string> input = read_file(argv[1]);

    if (!input) {
        return 1;
    }

    string expr = read(input.value());
    // string result = eval(expr);
    // cout << result;
}
