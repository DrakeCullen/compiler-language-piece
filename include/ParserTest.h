#pragma once
#include "TestCase.h"

enum testType {VARIABLE_TEST,FRACTION_TEST, POINTFLOAT_TEST, EXPONENT_TEST, EXPONENT_FLOAT_TEST, FLOATNUMBER_TEST, INTEGER_TEST, FACTOR_TEST, M_EXPRESSION_TEST};

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