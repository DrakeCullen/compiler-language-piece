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
};