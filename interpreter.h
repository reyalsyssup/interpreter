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
    } else {
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
}