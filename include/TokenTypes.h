#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <vector>

using namespace std;

enum TokenType{KEYWORD, INTEGER, DECIMAL_INTEGER, STRING, HEX_INTEGER, HEX_DIGIT,
	 			FLOAT_NUMBER, EXPONENT_FLOAT, INTPART, FRACTION, EXPONENT, EXPRESSION,
				EXPRESSION_LIST, EXPRESSION_STMT, CONDITIONAL_EXPRESSION, OR_TEST, AND_TEST,
				NOT_TEST, COMPARISON, COMP_OPERATOR, AND_EXPR, XOR_EXPR, OR_EXPR, U_EXPR, M_EXPR, A_EXPR,
                UNRECOGNIZED, END_OF_TEXT
};

string tokenString(TokenType t);