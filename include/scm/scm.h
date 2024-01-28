#ifndef SCM_H
#define SCM_H

#include <optional>
#include <memory>
#include <string>

namespace scm {

auto read(std::string input) -> std::string;

auto eval(std::string input) -> std::string;

}

#endif
