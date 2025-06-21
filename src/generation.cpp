#include "../include/generation.hpp"
#include <sstream>
#include <iostream>
#include <unordered_map>

void Generator::gen_expr(const NodeExpr& expr) {
    struct ExprVisitor {
        Generator* gen;
        void operator()(const NodeExprIntLit& expr_int_lit) const {
            gen->m_output << "    mov rax, " << expr_int_lit.int_lit.value.value() << "\n";
            gen->push("rax");
        }
        void operator()(const NodeExprIdent& expr_ident) const {
            if (!gen->m_vars.contains(expr_ident.ident.value.value())) {
                cerr << "ERROR! Undeclared Identifier: " << expr_ident.ident.value.value() << endl;
                exit(EXIT_FAILURE);
            }
            const auto& var = gen->m_vars.at(expr_ident.ident.value.value());
            // offset the stack pointer, take a copy, push it back at the top
            stringstream offset;
            offset << "    QWORD [rsp + " << (gen->m_stack_size - var.stack_loc - 1) * 8 << "]\n";
            gen->push(offset.str());
        }
    };
    ExprVisitor visitor {.gen = this};
    std::visit(visitor, expr.var);
}

void Generator::gen_stmt(const NodeStmt& stmt){
    struct StmtVisitor {
        Generator* gen;
        void operator()(const NodeStmtExit& stmt_exit) const {
            gen->gen_expr(stmt_exit.expr);
            gen->m_output << "    mov rax, 60\n";
            gen->pop("rdi");
            gen->m_output << "    syscall\n";
        }
        void operator()(const NodeStmtLet& stmt_let) const {
            // check there is no other variable with the same name declared
            if (gen->m_vars.contains(stmt_let.ident.value.value())) {
                cerr << "ERROR! Identifier Already Used: " << stmt_let.ident.value.value() << endl;
                exit(EXIT_FAILURE);
            }

            // insert the variable in unordered map
            gen->m_vars.insert({stmt_let.ident.value.value(), Var {.stack_loc = gen->m_stack_size}});

            // evaluate the expression
            gen->gen_expr(stmt_let.expr);
        }
    };
    StmtVisitor visitor {.gen = this};
    std::visit(visitor, stmt.var);
}


[[nodiscard]]string Generator::gen_prog() {
    m_output << "global _start\n_start:\n";

    for (const NodeStmt& stmt : m_prog.stmts) {
        gen_stmt(stmt);
    }

    m_output << "    mov rax, 60\n";
    m_output << "    mov rdi, 0\n";
    m_output << "    syscall\n";

    return m_output.str();
}