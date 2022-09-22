#include "../include/TokenizerTest.h"
#include "../include/ParserTest.h"

bool runTests();
void addTokenizerTests(vector<TestCase *> &tests);

int main()
{
	runTests();
	return 0;
}

void addTokenizerTests(vector<TestCase *> &tests)
{
	tests.push_back(new TokenizerTest("'''This is a comment''' 'string' 'string2'  ", false));
	tests.push_back(new TokenizerTest("'s' > 'd' 'e' <= 'd' 'f' != 'g' ", false));
	tests.push_back(new TokenizerTest("or and not or", false));
	tests.push_back(new TokenizerTest("123 53.", false));
	tests.push_back(new TokenizerTest("* / // % */", false));
	tests.push_back(new TokenizerTest("+ - +-", false));
	tests.push_back(new TokenizerTest("E 0x4932 0X9483 0xfEf or and not var", false));
}

bool runTests()
{
	vector<TestCase *> tests;
	addTokenizerTests(tests);
	tests.push_back(new ParserTest("./tests/variableTests/1.txt", 3, VARIABLE_TEST));
	tests.push_back(new ParserTest("./tests/variableTests/2.txt", 1, VARIABLE_TEST));
	tests.push_back(new ParserTest("./tests/variableTests/3.txt", 4, VARIABLE_TEST));
	tests.push_back(new ParserTest("./tests/fractionTests/1.txt", 1, FRACTION_TEST));
	tests.push_back(new ParserTest("./tests/fractionTests/2.txt", 4, FRACTION_TEST));
	tests.push_back(new ParserTest("./tests/pointFloatTests/1.txt", 3, POINTFLOAT_TEST));
	tests.push_back(new ParserTest("./tests/pointFloatTests/2.txt", 1, POINTFLOAT_TEST));
	tests.push_back(new ParserTest("./tests/exponentTests/1.txt", 1, EXPONENT_TEST));
	tests.push_back(new ParserTest("./tests/exponentTests/2.txt", 1, EXPONENT_TEST));
	tests.push_back(new ParserTest("./tests/exponentTests/3.txt", 3, EXPONENT_TEST));
	tests.push_back(new ParserTest("./tests/exponentFloatTests/1.txt", 1, EXPONENT_FLOAT_TEST));
	tests.push_back(new ParserTest("./tests/exponentFloatTests/2.txt", 1, EXPONENT_FLOAT_TEST));
	tests.push_back(new ParserTest("./tests/exponentFloatTests/3.txt", 3, EXPONENT_FLOAT_TEST));
	tests.push_back(new ParserTest("./tests/floatNumberTests/1.txt", 4, FLOATNUMBER_TEST));
	tests.push_back(new ParserTest("./tests/floatNumberTests/2.txt", 2, FLOATNUMBER_TEST));
	tests.push_back(new ParserTest("./tests/floatNumberTests/3.txt", 4, FLOATNUMBER_TEST));
	tests.push_back(new ParserTest("./tests/integerTests/1.txt", 3, INTEGER_TEST));
	tests.push_back(new ParserTest("./tests/integerTests/2.txt", 2, INTEGER_TEST));
	tests.push_back(new ParserTest("./tests/integerTests/3.txt", 3, INTEGER_TEST));
	tests.push_back(new ParserTest("./tests/factorTests/1.txt", 3, FACTOR_TEST));
	tests.push_back(new ParserTest("./tests/factorTests/2.txt", 3, FACTOR_TEST));
	tests.push_back(new ParserTest("./tests/factorTests/3.txt", 4, FACTOR_TEST));
	tests.push_back(new ParserTest("./tests/mExpressionTests/1.txt", 1, M_EXPRESSION_TEST));
	tests.push_back(new ParserTest("./tests/mExpressionTests/2.txt", 1, M_EXPRESSION_TEST));
	tests.push_back(new ParserTest("./tests/mExpressionTests/3.txt", 2, M_EXPRESSION_TEST));

	bool success = true;
	for (auto test : tests)
		if (!test->test())
			success = false;
	if (success)
	{
		cout << "All passed" << endl;
		return true;
	}
	cerr << "Failed some test" << endl;
	return false;
}