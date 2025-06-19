#include "../include/tokenization.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>

vector<Token>Tokenizer::tokenize() {
    vector<Token> tokens {};
    string buf{};

    while(peek().has_value()) {
        if(isalpha(peek().value())) {
            buf.push_back(consume());
            while(peek().has_value() && isalnum(peek().value())) {
                buf.push_back(consume());
            }
            if(buf == "exit") {
                tokens.push_back({.type = TokenType::exit});
                buf.clear();
                continue;
            }
            else {
                cerr << "ERROR!" << endl;
                exit(EXIT_FAILURE);
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
        else if(peek().value() == ';') {
            consume();
            tokens.push_back({.type = TokenType::semi});
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