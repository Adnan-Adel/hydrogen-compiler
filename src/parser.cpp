#include "../include/parser.hpp"
#include <cstdlib>
#include <iostream>


optional<NodeExpr>Parser::parse_expr() {
    if(peek().has_value() && peek().value().type == TokenType::int_lit) {
        return NodeExpr{.int_lit = consume()};
    }
    else {
        return {};
    }
}

optional<NodeExit>Parser::parse() {
    optional<NodeExit> exit_node;
    while(peek().has_value()) {
        if(peek().value().type == TokenType::exit) {
            consume();
            if(auto node_expr = parse_expr()) {
                exit_node = NodeExit{.expr = node_expr.value()};
            }
            else {
                cerr << "Invalid Expression!" << endl;
                exit(EXIT_FAILURE);
            }
            if(peek().has_value() && peek().value().type == TokenType::semi) {
                consume();
            }
            else {
                cerr << "Invalid Expression!" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    m_index = 0;
    return exit_node;
}
