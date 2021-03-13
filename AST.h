#pragma once

#include "lexer.h"
#include "types.h"
#include <memory>

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
    std::shared_ptr<Evaluable> num;
    UnaryOp(std::string op, std::shared_ptr<Evaluable> num): num(num), op(op), Evaluable("unary") {}
    UnaryOp() = default;
};

class BinOp : public Evaluable {
public:
    Token op;
    std::shared_ptr<Evaluable> left, right;
    BinOp(std::shared_ptr<Evaluable> left, Token op, std::shared_ptr<Evaluable> right):
        op(op), left(left), right(right), Evaluable("binop") {};
    BinOp() = default;
};

class Sqrt : public Evaluable {
public:
    std::shared_ptr<Evaluable> num;
    Sqrt(std::shared_ptr<Evaluable> num): num(num), Evaluable("sqrt") {}
};