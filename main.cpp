#include "lexer.h"
#include "types.h"
#include "parser.h"
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
        parser.parse();
    }
}