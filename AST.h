#pragma once

#include "lexer.h"
#include <iostream>

class Num {
public:
    float value;

    Num(Token token): value(std::stof(token.value)) {};
    Num() = default;

    float evaluate();
    std::string repr() { return "Num( " + std::to_string(this->value) + " )"; };
    void print() { std::cout << this->repr() << std::endl; };
};

class Node;

class BinOp {
public:
    Node *left, *right;
    Token op;
    BinOp(Node *left, Token op, Node *right): left(left), op(op), right(right) {};
    BinOp() = default;

    float evaluate();
    std::string repr();
    void print() { std::cout << this->repr() << std::endl; };
};

class Node {
public:
    Num numNode;
    BinOp binopNode;
    std::string type = "";
    Node(Num num): type("Num"), numNode(num) {};
    Node(BinOp binop): type("BinOp"), binopNode(binop) {};

    float evaluate();
    std::string repr();
    void print() { std::cout << this->repr() << std::endl; };
};