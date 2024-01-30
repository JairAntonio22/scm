#ifndef SCM_H
#define SCM_H

#include <memory>
#include <optional>
#include <string>

namespace scm {

class expr {
    std::string m_atom;
    std::unique_ptr<expr> m_car = nullptr;
    std::unique_ptr<expr> m_cdr = nullptr;

public:
    expr(std::string atom);

    expr(std::unique_ptr<expr> car, std::unique_ptr<expr> cdr);

    auto atom() -> std::string;

    auto car() -> expr*;

    auto cdr() -> expr*;
};

auto operator << (std::ostream& stream, scm::expr* expr) -> std::ostream&;

auto read(std::string input) -> std::unique_ptr<expr>;

auto eval(std::unique_ptr<expr> input) -> std::unique_ptr<expr>;

}

#endif
