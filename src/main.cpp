#include "../include/TokenizerTest.h"
#include "../include/ParserTest.h"
#include "../include/SymbolTable.h"

bool runTests(bool verbose = false);
void addTokenizerTests(vector<TestCase *> &tests);

int main(int argc, char **argv)
{

	if (argc < 2)
		cout << "Expecting 'test' or input file name as argument." << endl;
	else if (argc == 2 && string(argv[1]) == "test")
		runTests();
	else if (argc == 3 && string(argv[1]) == "test" && string(argv[2]) == "verbose")
		runTests(true);
	else
	{
		Parser p(argv[1], false);
		Result result = p.conditionalExpression(p.getTokenizer());
		if (result.success)
		{
			cout << "Parse Tree " << endl;
			result.subtree->print(cout);
		}
		else
			cout << "Parse failed." << endl;
		//SymbolTable st;
		//st.populate(result.subtree);
		//cout << st << endl;
	}

	return 0;
}

void addTokenizerTests(vector<TestCase *> &tests)
{
	tests.push_back(new TokenizerTest("'''This is a comment''' 'string' 'string2'  ", false));
	tests.push_back(new TokenizerTest("'s' > 'd' 'e' <= 'd' 'f' != 'g' ", false));
	tests.push_back(new TokenizerTest("or and not or if else", false));
	tests.push_back(new TokenizerTest("123 53.", false));
	tests.push_back(new TokenizerTest("* / // % */", false));
	tests.push_back(new TokenizerTest("+ - +- ( )", false));
	tests.push_back(new TokenizerTest("E 0x4932 0X9483 0xfEf or and not var", false));
	tests.push_back(new TokenizerTest("if 0x4932 0X9483 else or and not var", false));
}

bool runTests(bool verbose)
{
	vector<TestCase *> tests;
	addTokenizerTests(tests);

	tests.push_back(new ParserTest("./tests/variableTests/1.txt", 3, VARIABLE_TEST, verbose));
	tests.push_back(new ParserTest("./tests/variableTests/2.txt", 1, VARIABLE_TEST, verbose));
	tests.push_back(new ParserTest("./tests/variableTests/3.txt", 4, VARIABLE_TEST, verbose));
	tests.push_back(new ParserTest("./tests/fractionTests/1.txt", 1, FRACTION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/fractionTests/2.txt", 4, FRACTION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/pointFloatTests/1.txt", 3, POINTFLOAT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/pointFloatTests/2.txt", 1, POINTFLOAT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/exponentTests/1.txt", 1, EXPONENT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/exponentTests/2.txt", 1, EXPONENT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/exponentTests/3.txt", 3, EXPONENT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/exponentFloatTests/1.txt", 1, EXPONENT_FLOAT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/exponentFloatTests/2.txt", 1, EXPONENT_FLOAT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/exponentFloatTests/3.txt", 3, EXPONENT_FLOAT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/floatNumberTests/1.txt", 4, FLOATNUMBER_TEST, verbose));
	tests.push_back(new ParserTest("./tests/floatNumberTests/2.txt", 2, FLOATNUMBER_TEST, verbose));
	tests.push_back(new ParserTest("./tests/floatNumberTests/3.txt", 4, FLOATNUMBER_TEST, verbose));
	tests.push_back(new ParserTest("./tests/integerTests/1.txt", 3, INTEGER_TEST, verbose));
	tests.push_back(new ParserTest("./tests/integerTests/2.txt", 2, INTEGER_TEST, verbose));
	tests.push_back(new ParserTest("./tests/integerTests/3.txt", 3, INTEGER_TEST, verbose));
	tests.push_back(new ParserTest("./tests/factorTests/1.txt", 3, FACTOR_TEST, verbose));
	tests.push_back(new ParserTest("./tests/factorTests/2.txt", 3, FACTOR_TEST, verbose));
	tests.push_back(new ParserTest("./tests/factorTests/3.txt", 4, FACTOR_TEST, verbose));
	tests.push_back(new ParserTest("./tests/mExpressionTests/1.txt", 1, M_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/mExpressionTests/2.txt", 1, M_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/mExpressionTests/3.txt", 3, M_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/aExpressionTests/2.txt", 2, A_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/aExpressionTests/1.txt", 1, A_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/aExpressionTests/2.txt", 2, A_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/aExpressionTests/3.txt", 3, A_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/comparisonTests/1.txt", 1, COMP_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/comparisonTests/2.txt", 2, COMP_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/comparisonTests/3.txt", 2, COMP_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/notTests/1.txt", 2, NOT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/notTests/2.txt", 1, NOT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/notTests/3.txt", 2, NOT_TEST, verbose));
	tests.push_back(new ParserTest("./tests/andTests/1.txt", 1, AND_TEST, verbose));
	tests.push_back(new ParserTest("./tests/andTests/2.txt", 1, AND_TEST, verbose));
	tests.push_back(new ParserTest("./tests/andTests/3.txt", 2, AND_TEST, verbose));
	tests.push_back(new ParserTest("./tests/orTests/1.txt", 1, OR_TEST, verbose));
	tests.push_back(new ParserTest("./tests/orTests/2.txt", 1, OR_TEST, verbose));
	tests.push_back(new ParserTest("./tests/orTests/3.txt", 1, OR_TEST, verbose));
	tests.push_back(new ParserTest("./tests/conditionalExpressionTests/1.txt", 1, CONDITIONAL_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/conditionalExpressionTests/2.txt", 1, CONDITIONAL_EXPRESSION_TEST, verbose));
	tests.push_back(new ParserTest("./tests/conditionalExpressionTests/3.txt", 1, CONDITIONAL_EXPRESSION_TEST, verbose));

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