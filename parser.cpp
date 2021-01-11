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

Evaluable Parser::term()  {
    Token tok = this->currentToken;
    if(tok.type == INTEGER) {
        this->eat(INTEGER);
        Num *num = new Num(tok);
        return Evaluable(num);
    } else {
        this->eat(LPAREN);
        Evaluable node = this->plusExpr();
        this->eat(RPAREN);
        return node;
    }
}

Evaluable Parser::mulExpr() {
    Evaluable node = this->term();

    while(this->currentToken.type == MUL || this->currentToken.type == DIV) {
        Token tok = this->currentToken;
        if(tok.type == MUL)
            this->eat(MUL);
        else if(tok.type == DIV)
            this->eat(DIV);

        BinOp *binop = new BinOp(node, tok, this->term());
        node = Evaluable(binop);
    }
    return node;
}

Evaluable Parser::plusExpr() {
    Evaluable node = this->mulExpr();
    
    while(this->currentToken.type == PLUS || this->currentToken.type == MINUS) {
        Token tok = this->currentToken;
        if(tok.type == PLUS)
            this->eat(PLUS);
        else if(tok.type == MINUS)
            this->eat(MINUS);

        BinOp *binop = new BinOp(node, tok, this->mulExpr());
        node = Evaluable(binop);
        // ill figure out where to delete stuff later cbf rn
    }
    return node;
}

Evaluable Parser::AST() {
    return this->plusExpr();
}