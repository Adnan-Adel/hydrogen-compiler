#pragma once
#include <cstddef>
#include <optional>
#include <string>
#include <vector>
using namespace std;

enum class TokenType {
    exit,
    int_lit,
    semi
  };

struct Token {
    TokenType type;
    optional<string> value {};
};


class Tokenizer {
public:
    inline explicit Tokenizer(const string& src)
    : m_src(std::move(src))
    {
    }

    vector<Token> tokenize();


private:
    [[nodiscard]] inline optional<char> peek(int ahead = 1) const {
        if(m_index+ahead > m_src.length()) {
            return {};
        }
        else {
            return m_src.at(m_index);
        }
    }

    inline char consume() {
        return m_src.at(m_index++);
    }

    const string m_src;
    size_t m_index = 0;
};