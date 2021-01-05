#include "parser.h"
#include "types.h"
#include <string>
#include <iostream>

Parser::Parser(Lexer lexer) {
    this->lexer = lexer;
    this->currentToken = this->lexer.getNextToken();
}

void Parser::eat(std::string type) {
    if(this->currentToken.type == type)
        this->currentToken = this->lexer.getNextToken();
    else {
        std::cout << "Error in eat function" << std::endl;
        exit(-1);
    }
}

float Parser::term()  {
    Token tok = this->currentToken;
    this->eat(INTEGER);
    return std::stof(tok.value);
}

float Parser::plusExpr() {
    float result = this->term();
    
    while(this->currentToken.type == PLUS || this->currentToken.type == MINUS) {
        Token tok = this->currentToken;
        if(tok.type == PLUS) {
            this->eat(PLUS);
            result += this->term();
        }
        else if(tok.type == MINUS) {
            this->eat(MINUS);
            result -= this->term();
        }
    }
    return result;
}

void Parser::parse() {
    float ans = this->plusExpr();
    std::cout << this->lexer.text << " = " << ans << std::endl;
}