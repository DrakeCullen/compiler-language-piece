#pragma once
#include "TokenTypes.h"
//#include "TokenString.h"

class Token
{
public:
    TokenType type;
    string value;
    Token(TokenType newType=UNRECOGNIZED,string newValue="");
    void setValue(string newValue);
    void setType(TokenType newType);
    friend ostream &operator<<(ostream &, const Token &);
};
