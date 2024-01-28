#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <ctime>

#include "log/log.h"

using namespace std;

auto log::msg(std::string msg) -> void {
    cout << "\033[0m" << msg << '\n';
}

auto log::info(std::string msg) -> void {
    cout << "\033[32m" << "info: ";
    log::msg(msg);
}

auto log::warn(std::string msg) -> void {
    cout << "\033[33m" << "warn: ";
    log::msg(msg);
}

auto log::debug(std::string msg) -> void {
    cout << "\033[34m" << "debug: ";
    log::msg(msg);
}

auto log::error(std::string msg) -> void {
    cout << "\033[31m" << "error: ";
    log::msg(msg);
}
