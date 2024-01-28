#ifndef LOG_H
#define LOG_H

#include <string>

namespace log {

auto msg(std::string msg) -> void;

auto info(std::string msg) -> void;

auto warn(std::string msg) -> void;

auto debug(std::string msg) -> void;

auto error(std::string msg) -> void;

}

#endif
