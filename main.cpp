#include "lexer.h"
#include "types.h"
#include <iostream>

int main() {
    Lexer lexer("1 2 3 4");
    
    Token tok = lexer.getNextToken();
    while(true) {
        std::cout << "Token(" << tok.type << ", " << tok.value << ")" << std::endl;
        if(tok.type == EOF) break;
        tok = lexer.getNextToken();
    }
}