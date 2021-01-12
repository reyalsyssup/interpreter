#include "parser.h"
#include "types.h"
#include "AST.h"
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

Evaluable* Parser::term()  {
    Token tok = this->currentToken;
    if(tok.type == INTEGER) {
        this->eat(INTEGER);
        // convert num to evaluable pointer
        Num *num = new Num(std::stof(tok.value));
        Evaluable *numEvalPtr = num;
        return numEvalPtr;
    } else if(tok.type == LPAREN) {
        this->eat(LPAREN);
        Evaluable *node = this->plusExpr();
        this->eat(RPAREN);
        return node;
    } else if(tok.type == MINUS || tok.type == PLUS) {
        this->eat(tok.type);
        UnaryOp *unary = new UnaryOp(tok.type, this->term());
        Evaluable *unaryEvalPtr = unary;
        return unaryEvalPtr;
    } else {
        std::cout << "Error in parser.term()" << std::endl;
        exit(-1);
    }
}

Evaluable* Parser::mulExpr() {
    Evaluable *node = this->term();

    while(this->currentToken.type == MUL || this->currentToken.type == DIV) {
        Token tok = this->currentToken;
        if(tok.type == MUL)
            this->eat(MUL);
        else if(tok.type == DIV)
            this->eat(DIV);

        // BinOp *binop = ;
        // ill figure out where to delete stuff later cbf rn
        Evaluable *binopEvalPtr = new BinOp(node, tok, this->term());
        node = binopEvalPtr;
    }
    return node;
}

Evaluable* Parser::plusExpr() {
    Evaluable *node = this->mulExpr();
    
    while(this->currentToken.type == PLUS || this->currentToken.type == MINUS) {
        Token tok = this->currentToken;
        if(tok.type == PLUS)
            this->eat(PLUS);
        else if(tok.type == MINUS)
            this->eat(MINUS);

        // BinOp *binop = ;
        // ill figure out where to delete stuff later cbf rn
        Evaluable *binopEvalPtr = new BinOp(node, tok, this->mulExpr());
        node = binopEvalPtr;
    }
    return node;
}

Evaluable* Parser::AST() {
    return this->plusExpr();
}