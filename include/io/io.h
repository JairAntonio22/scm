#ifndef IO_H
#define IO_H

#include <optional>
#include <string>
#include <map>

namespace io {

std::optional<std::string> readln();

std::optional<std::string> read_file(std::string_view path);

}

#endif
