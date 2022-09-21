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
    if (t.next().type == VARIABLE) return true;
    return t.error("Expected a variable");
}

bool Parser::fraction(Tokenizer &t) {
    if (t.next().type == DOT) {
        if (t.next().type == INTPART) return true;
        return t.error("Expected integer part after decimal point");
    }
    return t.error("Expected a decimal point");
}

// pointfloat ::= {intpart} fraction | {intpart} DOT
bool Parser::pointFloat(Tokenizer &t) {
    if (t.next().type == INTPART) {
        Tokenizer temp = t;
        if (fraction(temp)) {t=temp; return true; }
        if (t.next().type == DOT) return true;
        return t.error("Expected a decimal point or faction part after integer part");
    }
    return t.error("Expected integer part");
}

bool Parser::exponent(Tokenizer &t) {
    if (t.next().type == E) {
        if (t.next().type != A_OPERATOR) return t.error("Expected an arithmetic operator");
        if (t.next().type == INTPART) return true;
        return t.error("Expected integer part after exponent operator");
    }
    return t.error("Expected an exponent operator");
}

//exponentfloat ::= (intpart | pointfloat) exponent
bool Parser::exponentFloat(Tokenizer &t) {
    Tokenizer temp = t;
    if (pointFloat(temp)) {
        t = temp;
        return exponent(t);
    }
    if (t.next().type == INTPART) return exponent(t);
    return t.error("Expected integer part or point float");
}