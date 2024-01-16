#include <iostream>

#include "io/io.h"
#include "scm/scm.h"

int main() {
	while (1) {
		std::optional<std::string> input = io::read_stdin();
		
		if (!input.has_value()) {
			continue;
		}

		std::string_view expr = scm::read(input.value());
		std::string_view result = scm::eval(expr);
		std::cout << result << '\n';
	}
}
