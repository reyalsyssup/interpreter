#include "lexer.h"
#include "AST.h"
#include <vector>

class Parser {
public:
    Lexer lexer;
    Token currentToken;
    Parser(Lexer lexer);

    void eat(std::string type);

    std::shared_ptr<Evaluable> term();
    std::shared_ptr<Evaluable> power();
    std::shared_ptr<Evaluable> plusExpr();
    std::shared_ptr<Evaluable> mulExpr();

    std::shared_ptr<Evaluable> AST();
};