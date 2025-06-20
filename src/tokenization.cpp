#include "../include/tokenization.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <bits/regex_error.h>

vector<Token>Tokenizer::tokenize() {
    vector<Token> tokens {};
    string buf{};

    while(peek().has_value()) {
        if(isalpha(peek().value())) {
            buf.push_back(consume());
            // check for keywords
            while(peek().has_value() && isalnum(peek().value())) {
                buf.push_back(consume());
            }
            if(buf == "exit") {
                tokens.push_back({.type = TokenType::exit});
                buf.clear();
                continue;
            }
            else if (buf == "let") {
                tokens.push_back({.type = TokenType::let});
                buf.clear();
                continue;
            }
            // if it's not a keyword. create an identifier
            else {
                tokens.push_back({.type = TokenType::ident, .value = buf});
                buf.clear();
                continue;
            }
        }
        else if(isdigit(peek().value())) {
            buf.push_back(consume());
            while(peek().has_value() && isdigit(peek().value())) {
                buf.push_back(consume());
            }
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();
            continue;
        }
        else if (peek().value() == '(') {
            consume();
            tokens.push_back({.type = TokenType::open_paren});
            continue;
        }
        else if (peek().value() == ')') {
            consume();
            tokens.push_back({.type = TokenType::close_paren});
            continue;
        }
        else if(peek().value() == ';') {
            consume();
            tokens.push_back({.type = TokenType::semi});
            continue;
        }
        else if (peek().value() == '=') {
            consume();
            tokens.push_back({.type = TokenType::eq});
            continue;
        }
        else if(isspace(peek().value())) {
            consume();
            continue;
        }
        else {
            cerr << "ERROR!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    m_index = 0;
    return tokens;
}
