#include "AST.h"
#include "types.h"
#include <iostream>

float Num::evaluate() { return this->value; }
float BinOp::evaluate() {
    std::string op = this->op.type;
    if(op == PLUS)
        return this->left->evaluate() + this->right->evaluate();
    if(op == MINUS)
        return this->left->evaluate() - this->right->evaluate();
    if(op == MUL)
        return this->left->evaluate() * this->right->evaluate();
    if(op == DIV)
        return this->left->evaluate() / this->right->evaluate();
}
std::string BinOp::repr() {
    return "BinOp( " + this->left->repr() + ", " + this->op.value + ", " + this->right->repr() + " )";
}

float Node::evaluate() {
    std::cout << "[Node::evaluate()] : " << this->type << std::endl;
    if(this->type == "Num") return this->numNode.evaluate();
    else if(this->type == "BinOp") return this->binopNode.evaluate();
}

std::string Node::repr() {
    if(this->type == "Num")
        return this->numNode.repr();
    if(this->type == "BinOp")
        return this->binopNode.repr();
}