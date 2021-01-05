#include "lexer.h"
#include "types.h"
#include <iostream>

Token::Token(std::string _type, std::string _value) {
    this->type = _type;
    this->value = _value;
}

void Lexer::advance(int amount) {
    this->pos += amount;
    // check if eof
    if(this->pos > this->textLength - 1)
        this->curCharNone = true;
    else
        this->currentChar = this->text[this->pos];
}

Token Lexer::integer() {
    std::string strNum = "";
    while(!this->curCharNone && isdigit(this->currentChar)) {
        strNum += currentChar;
        this->advance();
    }
    return Token(INTEGER, strNum);
}

Token Lexer::getNextToken() {
    while(!this->curCharNone) {
        char currentChar = this->currentChar;

        // ignore whitespace
        if(isspace(currentChar)) {
            this->advance(1);
            continue;
        }

        if(isdigit(currentChar))
            return this->integer();

        if(currentChar == '+') {
            this->advance(1);
            return Token(PLUS, "+");
        }
        if(currentChar == '-') {
            this->advance(1);
            return Token(MINUS, "-");
        }

        // if we got here an error occured
        std::cout << "Unexpected character '" << currentChar << "' at position: " << this->pos << std::endl;
        exit(-1);
    }

    return Token(EOF, EOF);
}