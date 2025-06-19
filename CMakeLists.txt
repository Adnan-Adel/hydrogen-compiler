cmake_minimum_required(VERSION 3.31)
project(hydrogen)

set(CMAKE_CXX_STANDARD 20)

add_executable(hydrogen src/main.cpp
        src/parser.cpp
        src/tokenization.cpp
        src/generation.cpp
        include/parser.hpp
        include/generation.hpp
        include/tokenization.hpp)
