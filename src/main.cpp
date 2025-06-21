#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "../include/generation.hpp"
#include "../include/parser.hpp"
#include "../include/tokenization.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Incorrect Usage!" << endl;
        cerr << "Correct Usage: " << argv[0] << " <file.hy>" << endl;
        return EXIT_FAILURE;
    }

    // read the file
    string contents; {
        fstream input(argv[1], ios::in);
        stringstream contents_stream;
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    Tokenizer tokenizer(std::move(contents));

    vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    optional<NodeProg> prog = parser.parse_prog();

    if (!prog.has_value()) {
        cerr << "Invalid Program!" << endl;
        exit(EXIT_FAILURE);
    }

    Generator generator(prog.value());


    // putting assembly to a file
    {
        fstream file("./out.asm", ios::out);
        file << generator.gen_prog();
    }

    // generate object file
    system("nasm -felf64 out.asm");
    // generate executable
    system("ld -o out out.o");


    return EXIT_SUCCESS;
}
