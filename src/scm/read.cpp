#include <cctype>
#include <vector>
#include <stack>

#include "scm/scm.h"

static std::vector<std::string_view> tokenize(std::string_view input);

std::string_view scm::read(std::string_view input) {
	std::vector<std::string_view> tokens = tokenize(input);
	return input;
}

static bool isparen(char c) {
	return c == '(' || c == ')';
}

static size_t get_token_size(std::string_view input, size_t i) {
	size_t size = 0;

	while (!isparen(input[i + size]) && !isspace(input[i + size])) {
		size++;
	}

	return size;
}

static std::vector<std::string_view> tokenize(std::string_view input) {
	std::vector<std::string_view> tokens;

	for (size_t i = 0; i < input.size(); i++) {
		if (isspace(input[i])) {
			continue;

		} else if (input[i] == '(') {
			tokens.push_back("(");

		} else if (input[i] == ')') {
			tokens.push_back(")");

		} else {
			size_t size = get_token_size(input, i);
			tokens.push_back(input.substr(i, size));
			i += size - 1;
		}
	}

	return tokens;
}
