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
    long double value;
    Num(long double value): value(value), Evaluable("num") {};
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

class Carrot : public Evaluable {
public:
    std::shared_ptr<Evaluable> num, power;
    Carrot(std::shared_ptr<Evaluable> num, std::shared_ptr<Evaluable> power):
        num(num), power(power), Evaluable("carrot") {}
};

class Factorial : public Evaluable {
public:
    std::shared_ptr<Evaluable> num;
    Factorial(std::shared_ptr<Evaluable> num): num(num), Evaluable("factorial") {}
};