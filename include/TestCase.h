#pragma once
#include "Parser.h"

class TestCase {
	protected:
	string name;
	public:
	TestCase(string newName);
	bool test();
	virtual bool doTest()=0;
};

