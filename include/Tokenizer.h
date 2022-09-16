#pragma once
#include "Token.h"

class Tokenizer {
    int linepos,charpos;
	string text;
	unsigned pos;
public:
    static string filename;
    Tokenizer();
    bool error(string);
	bool message(string );
    void readFile(string);
    void setText(string newText="");
    Token next();
    Token peek();
    void printTokenSecret();
};
