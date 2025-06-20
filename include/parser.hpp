#pragma once

#include "tokenization.hpp"
#include <cstddef>
#include <optional>
#include <variant>
#include <vector>
#include <variant>
using namespace std;

struct NodeExprIntLit {
    Token int_lit;
};

struct NodeExprIdent {
    Token ident;
};

struct NodeExpr {
    std::variant<NodeExprIntLit, NodeExprIdent> var;
};

struct NodeStmtExit {
    NodeExpr expr;
};

struct NodeStmtLet {
    Token ident;
    NodeExpr expr;
};

struct NodeStmt {
    std::variant<NodeStmtExit, NodeStmtLet> var;
};

struct NodeProg {
    vector<NodeStmt> stmts;
};


class Parser {
public:
    inline explicit Parser(vector<Token> tokens)
    : m_tokens(std::move(tokens))
    {
    }

    optional<NodeExpr> parse_expr();
    optional<NodeStmt> parse_stmt();
    optional<NodeExit> parse();

private:
    [[nodiscard]] inline optional<Token> peek(int offset = 0) const {
        if(m_index+offset >= m_tokens.size()) {
            return {};
        }
        else {
            return m_tokens.at(m_index + offset);
        }
    }

    inline Token consume() {
        return m_tokens.at(m_index++);
    }



    const vector<Token> m_tokens;
    size_t m_index = 0;
};