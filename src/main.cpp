#include <iostream>

#include "io/io.h"
#include "scm/scm.h"

using namespace io;
using namespace scm;
using namespace std;

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        return 1;
    }

    optional<string> raw_input = read_file(argv[1]);

    if (!raw_input.has_value()) {
        return 1;
    }

    unique_ptr<expr> input = read(raw_input.value());
    unique_ptr<expr> output = eval(std::move(input));
    cout << output;
}
