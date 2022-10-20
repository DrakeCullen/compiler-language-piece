#pragma once
#include "Token.h"
#include "Result.h"

class Tokenizer {
    int linepos,charpos;
	string text;
	unsigned pos;
public:
    static string filename;
    Tokenizer();
    Result error(string);
	Result message(string ,nodePtr);
    void readFile(string);
    void setText(string newText="");
    Token next();
    Token peek();
    void consumeSpaces();
    bool isComment();
    void consumeComments();
    Token getString();
    Token compOperator();
    bool isKeyword();
    Token intPart();
    Token characterParser();
    
};
