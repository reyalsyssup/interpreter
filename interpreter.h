#pragma once

// Include these here and they work in main without cluttering
// main.cpp's #include section
#include "parser.h"
#include "lexer.h"
#include "types.h"
#include "math.h"
#include <iostream>

float interpret(std::shared_ptr<Evaluable> node) {
    if(node->type == "num") {
        auto numptr = std::dynamic_pointer_cast<Num>(node);
        return numptr->value;
    }
    if(node->type == "binop") {
        auto binopPtr = std::dynamic_pointer_cast<BinOp>(node);
        std::string type = binopPtr->op.type;
        if(type == PLUS)
            return interpret(binopPtr->left) + interpret(binopPtr->right);
        if(type == MINUS)
            return interpret(binopPtr->left) - interpret(binopPtr->right);
        if(type == MUL)
            return interpret(binopPtr->left) * interpret(binopPtr->right);
        if(type == DIV)
            return interpret(binopPtr->left) / interpret(binopPtr->right);
    }
    if(node->type == "unary") {
        auto unaryPtr = std::dynamic_pointer_cast<UnaryOp>(node);
        if(unaryPtr->num->type == "unary") {
            std::shared_ptr<Evaluable> evalPtr = std::dynamic_pointer_cast<UnaryOp>(unaryPtr->num);
            return interpret(evalPtr);
        }
        if(unaryPtr->num->type == "num") {
            // get num from unaryptr
            float value = std::dynamic_pointer_cast<Num>(unaryPtr->num)->value;
            if(unaryPtr->op == MINUS) return -value;
            else if(unaryPtr->op == PLUS) return value;
        }
        if(unaryPtr->num->type == "binop") {
            auto binopPtr = std::dynamic_pointer_cast<BinOp>(unaryPtr->num);
            if(unaryPtr->op == MINUS) return -interpret(binopPtr);
            else if(unaryPtr->op == PLUS) return interpret(binopPtr);
        }
    }
    if(node->type == "sqrt") {
        auto sqrtPtr = std::dynamic_pointer_cast<Sqrt>(node);
        float value = interpret(sqrtPtr->num);
        return sqrt(value);
    }
    if(node->type == "carrot") {
        auto carrotPtr = std::dynamic_pointer_cast<Carrot>(node);
        float value = pow(interpret(carrotPtr->num), interpret(carrotPtr->power));
        return value;
    }
}