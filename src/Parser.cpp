#include "../include/Parser.h"

Parser::Parser(string newFilename) { 
    tokens=Tokenizer();
    tokens.readFile(newFilename); 
}

Token Parser::peek() { 
    return tokens.peek();
}

Tokenizer& Parser::getTokenizer() { 
    return tokens;
}
