#pragma once
#include "Tokenizer.h"

class Parser {
	Tokenizer tokens;
	public:
	Token peek();
	Token next();
	Tokenizer& getTokenizer();
	Parser(string newFilename);	
	bool variable(Tokenizer &t);
	bool fraction(Tokenizer &t);
	bool pointFloat(Tokenizer &t);
	bool exponent(Tokenizer &t);
	bool exponentFloat(Tokenizer &t);
	bool factor(Tokenizer &t);
	bool mExpression(Tokenizer &t);
	bool floatNumber(Tokenizer &t);
	bool integer(Tokenizer &t);
	bool u_expr(Tokenizer &t);
};