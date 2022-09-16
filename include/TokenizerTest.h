#pragma once
#include "TestCase.h"

class TokenizerTest:public TestCase {  // Tokenizer Test at most 100 tokens
	protected:
		string text;
		bool shouldFail;
	public:
	    TokenizerTest(string newText=".",bool newShouldFail=false);
	    virtual bool doTest();
};