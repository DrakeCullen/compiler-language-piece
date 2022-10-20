#pragma once
#include "Tokenizer.h"
#include<math.h>

class Parser {
	Tokenizer tokens;
	public:
	Token peek();
	Token next();
	Tokenizer& getTokenizer();
	Parser(string newFilename);	
	Result variable(Tokenizer &t);
	Result fraction(Tokenizer &t);
	Result pointFloat(Tokenizer &t);
	Result exponent(Tokenizer &t);
	Result exponentFloat(Tokenizer &t);
	Result factor(Tokenizer &t);
	Result mExpression(Tokenizer &t);
	Result floatNumber(Tokenizer &t);
	Result integer(Tokenizer &t);
	Result aExpression(Tokenizer &t);
	Result comparison(Tokenizer &t);
	Result andTest(Tokenizer &t);
	Result notTest(Tokenizer &t);
	Result orTest(Tokenizer &t);
	Result conditionalExpression(Tokenizer &t);
};