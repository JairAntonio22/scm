#include "io/io.h"

#include <iostream>
#include <stack>

std::optional<std::string> io::read_stdin() {
	std::stack<char> parens;
	std::string result;

	/* skip whitespace */ {
		char c;
		while ((c = std::cin.get()) != '(');
		std::cin.unget();
	}

	do {
		result.push_back(std::cin.get());

		if (result.back() == '(') {
			parens.push('(');

		} else if (result.back() == ')') {
			parens.pop();
		}

	} while (!parens.empty());

	return result;
}
