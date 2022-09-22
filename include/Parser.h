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
	bool aExpression(Tokenizer &t);
	/* bool andExpression(Tokenizer &t);
	bool xorExpression(Tokenizer &t);
	bool orExpression(Tokenizer &t); */
	bool comparison(Tokenizer &t);
	bool andTest(Tokenizer &t);
	bool notTest(Tokenizer &t);
	bool orTest(Tokenizer &t);
	bool conditionalExpression(Tokenizer &t);
};