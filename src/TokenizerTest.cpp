#include "../include/TokenizerTest.h"

TokenizerTest::TokenizerTest(string newText,bool newShouldFail)  :TestCase("TokenizerTest") 
{
    text=newText;
    shouldFail=newShouldFail;
}

bool TokenizerTest::doTest() {
    Tokenizer t;
    t.setText(text);
    int count=0;
    int status=0;
    Token token;
    do {
        token=t.next();
        cout << token << endl;
        if (token.type==UNRECOGNIZED) { 
            t.error(" Unrecognized Token ");
            status=1;
        }
        count++;
    } while (token.type!=END_OF_TEXT && count<100);
    return status==0;
}