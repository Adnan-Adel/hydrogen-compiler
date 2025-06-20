#include "../include/parser.hpp"
#include <cstdlib>
#include <iostream>


optional<NodeExpr> Parser::parse_expr() {
    if (peek().has_value() && peek().value().type == TokenType::int_lit) {
        return NodeExpr{.var = NodeExprIntLit{.int_lit = consume()}};
    } else if (peek().has_value() && peek().value().type == TokenType::ident) {
        return NodeExpr{.var = NodeExprIdent{.ident = consume()}};
    } else {
        return {};
    }
}

optional<NodeStmt> Parser::parse_stmt() {
    if (peek().value().type == TokenType::exit && peek(1).has_value()
        && peek(1).value().type == TokenType::open_paren) {
        consume(); // consume the exit
        consume(); // consume open paren

        // parse expression
        NodeStmtExit stmt_exit;
        if (auto node_expr = parse_expr()) {
            stmt_exit = {.expr = node_expr.value()};
        } else {
            cerr << "Invalid Expression!" << endl;
            exit(EXIT_FAILURE);
        }
        if (peek().has_value() && peek().value().type == TokenType::close_paren) {
            consume();
        } else {
            cerr << "Expected `)`!" << endl;
            exit(EXIT_FAILURE);
        }
        if (peek().has_value() && peek().value().type == TokenType::semi) {
            consume();
        } else {
            cerr << "Expected `;`!" << endl;
            exit(EXIT_FAILURE);
        }
        return NodeStmt{.var = stmt_exit};
    } else if (peek().has_value() && peek().value().type == TokenType::let &&
               peek(1).has_value() && peek(1).value().type == TokenType::ident &&
               peek(2).has_value() && peek(2).value().type == TokenType::eq) {
        consume(); // consume the "let", we don't need it
        auto stmt_let = NodeStmtLet{.ident = consume()};
        consume(); // consume the '=', we don't need it
        // parse the expression
        if (auto expr = parse_expr()) {
            stmt_let.expr = expr.value();
        } else {
            // we are unable to parse expression correctly, so it's invalid
            cerr << "Invalid Expression!" << endl;
            exit(EXIT_FAILURE);
        }
        // now check for ';'
        if (peek().has_value() && peek().value().type == TokenType::semi) {
            consume();
        } else {
            cerr << "Expected `;`!" << endl;
            exit(EXIT_FAILURE);
        }
        // if we get here, we successfully parsed "let ident = expr;"
        return NodeStmt{.var = stmt_let};
    } else {
        return {};
    }
}


optional<NodeExit> Parser::parse() {
    optional<NodeExit> exit_node;
    while (peek().has_value()) {
        if (peek().value().type == TokenType::exit && peek(1).has_value()
            && peek(1).value().type == TokenType::open_paren) {
            consume(); // consume the exit
            consume(); // consume open paren

            // parse expression
            if (auto node_expr = parse_expr()) {
                exit_node = NodeExit{.expr = node_expr.value()};
            } else {
                cerr << "Invalid Expression!" << endl;
                exit(EXIT_FAILURE);
            }
            if (peek().has_value() && peek().value().type == TokenType::close_paren) {
                consume();
            } else {
                cerr << "Expected `)`!" << endl;
                exit(EXIT_FAILURE);
            }
            if (peek().has_value() && peek().value().type == TokenType::semi) {
                consume();
            } else {
                cerr << "Expected `;`!" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    m_index = 0;
    return exit_node;
}
