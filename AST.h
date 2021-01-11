#pragma once

#include "lexer.h"
#include "types.h"

class Num;
class BinOp;

class Evaluable {
public:
    std::string type;
    Num *numNode;
    BinOp *binopNode;
    Evaluable(Num *num): type("Num"), numNode(num) {};
    Evaluable(BinOp *binop): type("BinOp"), binopNode(binop) {};
    Evaluable() = default;
};

class Num {
public:
    float value;
    Num(Token tok): value(std::stof(tok.value)) {};
    Num() = default;

    float evaluate() { return this->value; };
};

class BinOp {
public:
    Token op;
    Evaluable left, right;
    BinOp(Evaluable left, Token op, Evaluable right):
        op(op), left(left), right(right) {};
    BinOp() = default;

    //will find a better spot for this later
    static float evaluateNode(Evaluable eval) {
        if(eval.type == "Num")
            return eval.numNode->evaluate();
        else
            return eval.binopNode->evaluate();
    }
    
    float evaluate() {
        if(this->op.type == PLUS)
            return this->evaluateNode(this->left) + this->evaluateNode(this->right);
        if(this->op.type == MINUS)
            return this->evaluateNode(this->left) - this->evaluateNode(this->right);
        if(this->op.type == MUL)
            return this->evaluateNode(this->left) * this->evaluateNode(this->right);
        if(this->op.type == DIV)
            return this->evaluateNode(this->left) / this->evaluateNode(this->right);
    }
};