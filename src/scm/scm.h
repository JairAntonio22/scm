#ifndef SCM_H
#define SCM_H

#include <string>

namespace scm {
	std::string_view read(std::string_view input);

	std::string_view eval(std::string_view input);
}

#endif
