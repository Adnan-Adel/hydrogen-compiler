#pragma once

#include "tokenization.hpp"
#include <cstddef>
#include <optional>
#include <vector>
using namespace std;

struct NodeExpr {
    Token int_lit;
};

struct NodeExit {
    NodeExpr expr;
};



class Parser {
public:
    inline explicit Parser(vector<Token> tokens)
    : m_tokens(std::move(tokens))
    {
    }

    optional<NodeExpr> parse_expr();
    optional<NodeExit> parse();

private:
    [[nodiscard]] inline optional<Token> peek(int ahead = 1) const {
        if(m_index+ahead > m_tokens.size()) {
            return {};
        }
        else {
            return m_tokens.at(m_index);
        }
    }

    inline Token consume() {
        return m_tokens.at(m_index++);
    }



    const vector<Token> m_tokens;
    size_t m_index = 0;
};