#include "lexer.h"
#include "AST.h"
#include <vector>

class Parser {
public:
    Lexer lexer;
    Token currentToken;
    Parser(Lexer lexer);

    void eat(std::string type);

    Evaluable term();
    Evaluable plusExpr();
    Evaluable mulExpr();

    Evaluable AST();
};