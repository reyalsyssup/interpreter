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
        long double value = interpret(parser.AST());
        std::cout << lexer.text << " = " << value << std::endl;
    }
}