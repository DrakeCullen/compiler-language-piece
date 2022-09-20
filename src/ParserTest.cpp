#include "../include/ParserTest.h"

ParserTest::ParserTest(string newFilename, int numInstances, testType type, bool newShouldFail):TestCase("ParserTest " + newFilename) {
    p=new Parser(newFilename);
    shouldFail=newShouldFail;
    this->numInstances=numInstances;
    this->type=type;
}

bool ParserTest::doTest() {
		int count=0;
		while (p->peek().type!=END_OF_TEXT) {
            if (type==VARIABLE_TEST) 
                if (p->variable(p->getTokenizer())) count++;
                else p->next();
            if (type==FRACTION_TEST) 
                if (p->fraction(p->getTokenizer())) count++;
                else p->next();
            if (type==POINTFLOAT_TEST) 
                if (p->pointFloat(p->getTokenizer())) count++;
                else p->next();
        }
		return count==numInstances;
	}

ParserTest::~ParserTest() {
    delete p;
}