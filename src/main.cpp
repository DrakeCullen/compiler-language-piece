#include "../include/TokenizerTest.h"
#include "../include/ParserTest.h"

bool runTests();
void addTokenizerTests(vector<TestCase*> &tests);

int main() {
    runTests();
    return 0;
}

void addTokenizerTests(vector<TestCase*> &tests) {
	tests.push_back(new TokenizerTest("'''This is a comment''' 'string' 'string2'  ", false));
    tests.push_back(new TokenizerTest("'s' > 'd' 'e' <= 'd' 'f' != 'g' ", false));
    tests.push_back(new TokenizerTest("or and not or", false));
	tests.push_back(new TokenizerTest("123 53.", false));
	tests.push_back(new TokenizerTest("* / // % */", false));
	tests.push_back(new TokenizerTest("+ - +-", false));
	tests.push_back(new TokenizerTest("E 0x4932 0X9483 or and not var", false));
}

bool runTests() {
    vector<TestCase*> tests;
	//addTokenizerTests(tests);
	tests.push_back(new ParserTest("./tests/variableTests/1.txt", 3, VARIABLE_TEST));
	tests.push_back(new ParserTest("./tests/variableTests/2.txt", 1, VARIABLE_TEST));
	tests.push_back(new ParserTest("./tests/variableTests/3.txt", 4, VARIABLE_TEST));
	tests.push_back(new ParserTest("./tests/fractionTests/1.txt", 1, FRACTION_TEST));
	tests.push_back(new ParserTest("./tests/fractionTests/2.txt", 4, FRACTION_TEST));
	tests.push_back(new ParserTest("./tests/pointFloatTests/1.txt", 3, POINTFLOAT_TEST));
	bool success=true;
	for (auto test:tests)
		if (!test->test()) success=false;
	if (success) {
		cout << "All passed" << endl;
		return true;
	}
	cerr << "Failed some test"<<endl; 
	return false;	
}