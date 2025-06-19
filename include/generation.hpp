#pragma once

#include "parser.hpp"
#include <string>
using namespace std;

class Generator {
public:
    inline explicit Generator(NodeExit root)
    : m_root(std::move(root))
    {

    }

    [[nodiscard]] std::string generate() const;

private:
    const NodeExit m_root;
};
