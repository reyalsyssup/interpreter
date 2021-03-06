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
    if(this->currentChar == '.') {
        strNum += '.';
        this->advance();
        while(!this->curCharNone && isdigit(this->currentChar)) {
            strNum += currentChar;
            this->advance();
        }
    }
    return Token(INTEGER, strNum);
}

Token Lexer::word() {
    std::string word = "";
    while(isalpha(this->currentChar) && !this->curCharNone) {
        word += this->currentChar;
        this->advance();
    }
    return Token(WORD, word);
}

Token Lexer::getNextToken() {
    while(!this->curCharNone) {
        char currentChar = this->currentChar;

        // ignore whitespace
        if(isspace(currentChar)) {
            this->advance(1);
            continue;
        }

        if(isalpha(currentChar))
            return this->word();

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
        if(currentChar == '*') {
            this->advance(1);
            return Token(MUL, "*");
        }
        if(currentChar == '/') {
            this->advance(1);
            return Token(DIV, "/");
        }

        if(currentChar == '(') {
            this->advance(1);
            return Token(LPAREN, "(");
        }
        if(currentChar == ')') {
            this->advance(1);
            return Token(RPAREN, ")");
        }
        if(currentChar == '^') {
            this->advance(1);
            return Token(CARROT, "^");
        }
        if(currentChar == '!') {
            this->advance(1);
            return Token(FACTORIAL, "!");
        }

        // if we got here an error occured
        std::cout << "Unexpected character '" << currentChar << "' at position: " << this->pos << std::endl;
        exit(-1);
    }

    return Token(_EOF, _EOF);
}