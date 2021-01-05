#include "lexer.h"

class Parser {
public:
    Lexer lexer;
    Token currentToken;
    Parser(Lexer lexer);

    void eat(std::string type);

    float term();
    float plusExpr();

    void parse();
};