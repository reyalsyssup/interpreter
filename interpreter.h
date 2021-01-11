#pragma once

// Include these here and they work in main without cluttering
// main.cpp's #include section
#include "parser.h"
#include "lexer.h"
#include "types.h"

float interpret(Evaluable node) {
    if(node.type == "Num") return node.numNode->value;
    else {
        std::string type = node.binopNode->op.type;
        if(type == PLUS)
            return interpret(node.binopNode->left) + interpret(node.binopNode->right);
        if(type == MINUS)
            return interpret(node.binopNode->left) - interpret(node.binopNode->right);
        if(type == MUL)
            return interpret(node.binopNode->left) * interpret(node.binopNode->right);
        if(type == DIV)
            return interpret(node.binopNode->left) / interpret(node.binopNode->right);
    }
}