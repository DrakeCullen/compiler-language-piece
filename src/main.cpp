#include "../include/TokenizerTest.h"

bool runTests();

int main() {
    runTests();
    return 0;
}

bool runTests() {
    vector<TestCase*> tests;
	tests.push_back(new TokenizerTest("'''This is a comment''' 'string' 'string2'  ", false));
    tests.push_back(new TokenizerTest("'s' > 'd' 'e' <= 'd' 'f' != 'g' ", false));
    tests.push_back(new TokenizerTest("or and not or", false));
	tests.push_back(new TokenizerTest("123 53.", false));
	tests.push_back(new TokenizerTest("* / // % */", false));
	tests.push_back(new TokenizerTest("+ - +-", false));
	tests.push_back(new TokenizerTest("E 0x4932 0X9483 or and not var", false));
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