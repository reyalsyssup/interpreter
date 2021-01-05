#include "lexer.h"
#include "types.h"
#include "parser.h"
#include <iostream>

int main() {
    Lexer lexer("5-5+8-9");
    Parser parser(lexer);
    parser.parse();
}