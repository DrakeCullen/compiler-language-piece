#include "../include/TestCase.h"

TestCase::TestCase(string newName) {
		name=newName;
}

bool TestCase::test() {
    cout << "Test " << name << endl;
    bool retval=doTest();
    cout << "End Test " << name;
    if (retval) cout << "->Passed" << endl;
    else cout << "->Failed" << endl;
    return retval;
}
