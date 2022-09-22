#include "../include/ParserTest.h"

ParserTest::ParserTest(string newFilename, int numInstances, testType type, bool newShouldFail):TestCase("ParserTest " + newFilename) {
    p=new Parser(newFilename);
    shouldFail=newShouldFail;
    this->numInstances=numInstances;
    this->type=type;
}

bool ParserTest::doTest() {
		int count=0,i=0;
		while (p->peek().type!=END_OF_TEXT && i < 20) {
            if (type==VARIABLE_TEST && p->variable(p->getTokenizer())) count++;
            if (type==FRACTION_TEST && p->fraction(p->getTokenizer())) count++;
            if (type==POINTFLOAT_TEST && p->pointFloat(p->getTokenizer())) count++;
            if (type==EXPONENT_TEST && p->exponent(p->getTokenizer())) count++;
            if (type==EXPONENT_FLOAT_TEST && p->exponentFloat(p->getTokenizer())) count++;
            if (type==FLOATNUMBER_TEST && p->floatNumber(p->getTokenizer())) count++;
            i++;
        }
		return count==numInstances;
	}

ParserTest::~ParserTest() {
    delete p;
}