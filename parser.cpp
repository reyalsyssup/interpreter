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
        std::cout << "Expected '" << type << "' got '" << this->currentToken.type << "'" << std::endl;
        exit(-1);
    }
}

float Parser::term()  {
    Token tok = this->currentToken;
    if(tok.type == INTEGER) {
        this->eat(INTEGER);
        return std::stof(tok.value);
    } else {
        this->eat(LPAREN);
        float result = this->plusExpr();
        this->eat(RPAREN);
        return result;
    }
}

float Parser::mulExpr() {
    float result = this->term();

    while(this->currentToken.type == MUL || this->currentToken.type == DIV) {
        Token tok = this->currentToken;
        if(tok.type == MUL) {
            this->eat(MUL);
            result *= this->term();
        }
        else if(tok.type == DIV) {
            this->eat(DIV);
            result /= this->term();
        }
    }
    return result;
}

float Parser::plusExpr() {
    float result = this->mulExpr();
    
    while(this->currentToken.type == PLUS || this->currentToken.type == MINUS) {
        Token tok = this->currentToken;
        if(tok.type == PLUS) {
            this->eat(PLUS);
            result += this->mulExpr();
        }
        else if(tok.type == MINUS) {
            this->eat(MINUS);
            result -= this->mulExpr();
        }
    }
    return result;
}

void Parser::parse() {
    float ans = this->plusExpr();
    std::cout << this->lexer.text << " = " << ans << std::endl;
}