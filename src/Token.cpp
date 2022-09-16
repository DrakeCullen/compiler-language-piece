#include "../include/Token.h"
//#include "TokenTypes.cpp"

Token::Token(TokenType newType,string newValue) {
		type=newType;
		value=newValue;
}


void Token::setValue(string newValue) {
    value=newValue;
}

void Token::setType(TokenType newType){
    type=newType;
}

ostream &operator <<(ostream &out,const Token &token) {
    return out <<"Token:" << tokenString(token.type)<<":"<<token.value;
}

