#ifndef SCM_H
#define SCM_H

#include <optional>
#include <memory>
#include <string>

namespace scm {

std::string read(std::string input);

std::string eval(std::string input);

}

#endif
