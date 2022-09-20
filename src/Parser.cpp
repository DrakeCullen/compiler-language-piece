#include "../include/Parser.h"

Parser::Parser(string newFilename) { 
    tokens=Tokenizer();
    tokens.readFile(newFilename); 
}

Token Parser::peek() { 
    return tokens.peek();
}

Token Parser::next() { 
    return tokens.next();
}

Tokenizer& Parser::getTokenizer() { 
    return tokens;
}

bool Parser::variable(Tokenizer &t) {
    Token token = t.peek();
    if (token.type == VARIABLE) {
        t.next();
        return true;
    }
    return t.error("Expected a variable");
}

bool Parser::fraction(Tokenizer &t) {
    Token token = t.peek();
    if (token.type == DOT) {
        t.next();
        token = t.peek();
        if (token.type == INTPART) {
            t.next();
            while (t.peek().type == INTPART) t.next();
            return true;
        }
        return t.error("Expected integer part after decimal point");
    }
    return t.error("Expected a decimal point");
}

// pointfloat ::= intpart fraction | intpart DOT
bool Parser::pointFloat(Tokenizer &t) {
    if (t.peek().type == INTPART) {
        while (t.peek().type == INTPART) t.next();
        Tokenizer temp = t;
        temp.next();
        if (fraction(temp)) return true;
        if (t.peek().type == DOT) return true;
        return t.error("Expected a decimal point or faction part after integer part");
    }
    return t.error("Expected integer part");
}