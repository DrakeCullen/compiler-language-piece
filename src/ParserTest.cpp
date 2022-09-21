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
            if (type==VARIABLE_TEST) 
                if (p->variable(p->getTokenizer())) count++;
            if (type==FRACTION_TEST) 
                if (p->fraction(p->getTokenizer())) count++;
            if (type==POINTFLOAT_TEST) 
                if (p->pointFloat(p->getTokenizer())) count++;
            if (type==EXPONENT_TEST)
                if (p->exponent(p->getTokenizer())) count++;
            if (type==EXPONENT_FLOAT_TEST)
                if (p->exponentFloat(p->getTokenizer())) count++;
            i++;
        }
		return count==numInstances;
	}

ParserTest::~ParserTest() {
    delete p;
}