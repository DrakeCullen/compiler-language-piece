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
            if (type==INTEGER_TEST && p->integer(p->getTokenizer())) count++;
            if (type==FACTOR_TEST && p->factor(p->getTokenizer())) count++;
            if (type==M_EXPRESSION_TEST && p->mExpression(p->getTokenizer())) count++;
            if (type==A_EXPRESSION_TEST && p->aExpression(p->getTokenizer())) count++;
            if (type==COMP_EXPRESSION_TEST && p->comparison(p->getTokenizer())) count++;
            if (type==NOT_TEST && p->notTest(p->getTokenizer())) count++;
            if (type==AND_TEST && p->andTest(p->getTokenizer())) count++;
            if (type==OR_TEST && p->orTest(p->getTokenizer())) count++;
            if (type==CONDITIONAL_EXPRESSION_TEST && p->conditionalExpression(p->getTokenizer())) count++;
            i++;
        }
		return count==numInstances;
	}

ParserTest::~ParserTest() {
    delete p;
}