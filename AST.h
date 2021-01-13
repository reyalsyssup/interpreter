#pragma once

#include "lexer.h"
#include "types.h"

class Evaluable {
public:
    std::string type = "eval";
    Evaluable(std::string type): type(type) {};
    Evaluable() = default;
    virtual ~Evaluable() = default;
};

class Num : public Evaluable {
public:
    float value;
    Num(float value): value(value), Evaluable("num") {};
    Num() = default;
};

class UnaryOp : public Evaluable {
public:
    std::string op;
    Evaluable *num;
    UnaryOp(std::string op, Evaluable *num): num(num), op(op), Evaluable("unary") {}
    UnaryOp() = default;
};

class BinOp : public Evaluable {
public:
    Token op;
    Evaluable *left, *right;
    BinOp(Evaluable *left, Token op, Evaluable *right):
        op(op), left(left), right(right), Evaluable("binop") {};
    BinOp() = default;
};

class Sqrt : public Evaluable {
public:
    Evaluable *num;
    Sqrt(Evaluable *num): num(num), Evaluable("sqrt") {}
};