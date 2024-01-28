#include "io/io.h"

#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

auto io::readln() -> optional<string> {
    // TODO repl input mode
    return nullopt;
}

auto io::read_file(string_view path) -> optional<string> {
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


