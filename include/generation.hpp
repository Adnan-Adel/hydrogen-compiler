#pragma once

#include <sstream>

#include "parser.hpp"
#include <string>
#include <unordered_map>
using namespace std;

class Generator {
public:
    inline explicit Generator(NodeProg prog)
    : m_prog(std::move(prog))
    {

    }

    void gen_stmt(const NodeStmt& stmt);
    void gen_expr(const NodeExpr& expr);

    [[nodiscard]] std::string gen_prog();

private:
    void push(const string& reg) {
        m_output << "    push " << reg << "\n";
        m_stack_size++;
    }
    void pop(const string& reg) {
        m_output << "    pop " << reg << "\n";
        m_stack_size--;
    }
    struct Var {
        size_t stack_loc;
    };

    const NodeProg m_prog;
    std::stringstream m_output;
    size_t m_stack_size;
    unordered_map<string, Var> m_vars {};
};
