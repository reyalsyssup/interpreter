#pragma once

#include <string>

class Token {
public:
    std::string type, value;
    Token(std::string _type, std::string _value);
    Token() = default;
};

class Lexer {
public:
    std::string text;
    int textLength = 0;
    char currentChar = text[0];
    bool curCharNone = false;
    int pos = 0;
    Lexer(std::string _text): text(_text), textLength(_text.length()) {};
    Lexer() = default;

    void advance(int amount=1);

    Token integer();
    Token getNextToken();
    Token word();
};