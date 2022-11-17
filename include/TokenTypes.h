#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <vector>

using namespace std;

enum TokenType {KEYWORD, DOT, STRING, AND, OR, NOT, HEXDIGIT, VARIABLE,
	 			INTPART, E, M_OPERATOR, A_OPERATOR, COMP_OPERATOR, IF, ELSE,
                UNRECOGNIZED, END_OF_TEXT, LEFT_PAREN, RIGHT_PAREN,EQUAL,
// Parsed Tokens
                P_EXPONENT_FLOAT, P_POINT_FLOAT, P_EXPONENT, P_CONDITIONAL_EXPRESSION, P_VALDECL, P_ORTEST };

string tokenString(TokenType t);