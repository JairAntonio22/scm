#include "io/io.h"

#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

optional<string> io::readln() {
    // TODO repl input mode
    return nullopt;
}

optional<string> io::read_file(string_view path) {
    ifstream input(path);
    
    if (!input.is_open()) {
        return nullopt;
    }
    
    string result;
    
    while (!input.eof()) {
        result.push_back(char(input.get()));
    }
    
    return result;
}


