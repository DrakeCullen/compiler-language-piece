#include "../include/Token.h"

Token::Token(){
    // do nothing
}

void Token::printSecret() {
    std::cout << "Secret: " << tokenType.testData << std::endl;
}