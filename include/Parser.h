#pragma once
#include "Tokenizer.h"

class Parser {
	Tokenizer tokens;
	public:
	Token peek();
	Tokenizer& getTokenizer();
	Parser(string newFilename);	
};