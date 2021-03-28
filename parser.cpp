#include "parser.h"
#include "types.h"
#include "AST.h"
#include <string>
#include <iostream>
#include <memory>

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

std::shared_ptr<Evaluable> Parser::term()  {
    Token tok = this->currentToken;
    if(tok.type == INTEGER) {
        this->eat(INTEGER);
        // convert num to evaluable pointer
        std::shared_ptr<Num> num = std::make_shared<Num>(Num(std::stof(tok.value)));
        // Evaluable *numEvalPtr = num;
        // factorial
        if(this->currentToken.type == FACTORIAL)
            return std::make_shared<Factorial>(Factorial(num));
        return num;
    } else if(tok.type == LPAREN) {
        this->eat(LPAREN);
        auto node = this->plusExpr();
        this->eat(RPAREN);
        return node;
    } else if(tok.type == MINUS || tok.type == PLUS) {
        this->eat(tok.type);
        std::shared_ptr<UnaryOp> unary(new UnaryOp(tok.type, this->term()));
        std::shared_ptr<Evaluable> unaryEvalPtr = unary;
        return unaryEvalPtr;
    } else if(tok.type == WORD && tok.value == "sqrt") {
        this->eat(WORD);
        this->eat(LPAREN);
        std::shared_ptr<Sqrt> sqrt(new Sqrt(this->plusExpr()));
        this->eat(RPAREN);
        std::shared_ptr<Evaluable> sqrtPtr = sqrt;
        return sqrtPtr;
    } else {
        std::cout << "Unexpected token of type '" << this->currentToken.type << "'" << std::endl;
        exit(-1);
    }
}

std::shared_ptr<Evaluable> Parser::power() {
    auto node = this->term();
    if(this->currentToken.type == CARROT) {
        this->eat(CARROT);
        node = std::make_shared<Carrot>(Carrot(node, this->term()));
    }
    return node;
}

std::shared_ptr<Evaluable> Parser::mulExpr() {
    auto node = this->power();

    while(this->currentToken.type == MUL || this->currentToken.type == DIV) {
        Token tok = this->currentToken;
        if(tok.type == MUL)
            this->eat(MUL);
        else if(tok.type == DIV)
            this->eat(DIV);
            
        std::shared_ptr<Evaluable> binopEvalPtr = std::make_shared<BinOp>(BinOp(node, tok, this->term()));
        node = binopEvalPtr;
    }
    return node;
}

std::shared_ptr<Evaluable> Parser::plusExpr() {
    std::shared_ptr<Evaluable> node = this->mulExpr();
    
    while(this->currentToken.type == PLUS || this->currentToken.type == MINUS) {
        Token tok = this->currentToken;
        if(tok.type == PLUS)
            this->eat(PLUS);
        else if(tok.type == MINUS)
            this->eat(MINUS);
        std::shared_ptr<Evaluable> binopEvalPtr = std::make_shared<BinOp>(BinOp(node, tok, this->mulExpr()));
        node = binopEvalPtr;
    }
    return node;
}

std::shared_ptr<Evaluable> Parser::AST() {
    return this->plusExpr();
}