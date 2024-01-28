#ifndef IO_H
#define IO_H

#include <optional>
#include <string>
#include <map>

namespace io {

auto readln() -> std::optional<std::string>;

auto read_file(std::string_view path) -> std::optional<std::string>;

}

#endif
