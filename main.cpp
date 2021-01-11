#include "interpreter.h"
#include <string>
#include <iostream>

int main() {
    while(true) {
        std::cout << "calc> ";
        std::string input = "";
        getline(std::cin, input);
        if(input == "") continue;
        Lexer lexer(input);
        Parser parser(lexer);
        std::cout << lexer.text << " = " << interpret(parser.AST()) << std::endl;
    }
}