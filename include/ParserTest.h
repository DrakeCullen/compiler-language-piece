#pragma once
#include "TestCase.h"

enum testType {VARIABLE_TEST,FRACTION_TEST, POINTFLOAT_TEST};

class ParserTest:public TestCase {
	private:
		Parser *p;
		bool shouldFail;
        int numInstances;
        testType type;
	public:
	ParserTest(string newFilename, int numInstances, testType type, bool newShouldFail=false);
    bool doTest();
	~ParserTest();
};