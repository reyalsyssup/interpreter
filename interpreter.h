#pragma once

// Include these here and they work in main without cluttering
// main.cpp's #include section
#include "parser.h"
#include "lexer.h"
#include "types.h"
#include <iostream>

float interpret(Evaluable *node) {
    if(node->type == "num") {
        Num *numptr = dynamic_cast<Num*>(node);
        return numptr->value;
    }
    if(node->type == "binop") {
        BinOp *binopPtr = dynamic_cast<BinOp*>(node);
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
        UnaryOp *unaryPtr = dynamic_cast<UnaryOp*>(node);
        if(unaryPtr->num->type == "unary")
            return interpret(dynamic_cast<UnaryOp*>(unaryPtr->num));
        if(unaryPtr->num->type == "num") {
            // get num from unaryptr
            float value = dynamic_cast<Num*>(unaryPtr->num)->value;
            if(unaryPtr->op == MINUS) return -value;
            else if(unaryPtr->op == PLUS) return value;
        }
        if(unaryPtr->num->type == "binop") {
            BinOp *binopPtr = dynamic_cast<BinOp*>(unaryPtr->num);
            if(unaryPtr->op == MINUS) return -interpret(binopPtr);
            else if(unaryPtr->op == PLUS) return interpret(binopPtr);
        }
    }
}