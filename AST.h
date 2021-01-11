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
};

class BinOp {
public:
    Token op;
    Evaluable left, right;
    BinOp(Evaluable left, Token op, Evaluable right):
        op(op), left(left), right(right) {};
    BinOp() = default;
};