#include "lexer.h"
#include "AST.h"
#include <vector>

class Parser {
public:
    std::vector<Node> leftNodes;
    std::vector<Node> rightNodes;

    Lexer lexer;
    Token currentToken;
    Parser(Lexer lexer);

    void eat(std::string type);

    Node term();
    Node plusExpr();
    Node mulExpr();

    void parse();
};