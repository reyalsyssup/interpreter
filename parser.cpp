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

Node Parser::term()  {
    Token tok = this->currentToken;
    if(tok.type == INTEGER) {
        this->eat(INTEGER);
        return Node(Num(tok));
    } else {
        this->eat(LPAREN);
        Node node = this->plusExpr();
        this->eat(RPAREN);
        return Node(node);
    }
}

Node Parser::mulExpr() {
    Node node = this->term();

    while(this->currentToken.type == MUL || this->currentToken.type == DIV) {
        Token tok = this->currentToken;
        if(tok.type == MUL)
            this->eat(MUL);
        else if(tok.type == DIV)
            this->eat(DIV);

        // kinda scuffed but i need pointers until I find a better solution so I am storing nodes in an array
        this->leftNodes.push_back(node);
        this->rightNodes.push_back(this->term());
        node = Node(BinOp(&this->leftNodes[this->leftNodes.size()-1], tok, &this->rightNodes[this->rightNodes.size()-1]));
        std::cout << "[mulExpr()] : " << node.type << std::endl;
    }
    return node;
}

Node Parser::plusExpr() {
    Node node = this->mulExpr();
    
    while(this->currentToken.type == PLUS || this->currentToken.type == MINUS) {
        Token tok = this->currentToken;
        if(tok.type == PLUS)
            this->eat(PLUS);
        else if(tok.type == MINUS)
            this->eat(MINUS);

        // kinda scuffed but i need pointers until I find a better solution so I am storing nodes in an array
        this->leftNodes.push_back(node);
        this->rightNodes.push_back(this->mulExpr());
        node = Node(BinOp(&this->leftNodes[this->leftNodes.size()-1], tok, &this->rightNodes[this->rightNodes.size()-1]));
        std::cout << "[plusExpr()] : " << node.type << std::endl;
    }
    node.print();
    return node;
}

void Parser::parse() {
    float ans = this->plusExpr().evaluate();
    // std::cout << this->lexer.text << " = " << ans << std::endl;
    // this->plusExpr().print();
}