#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <vector>

using namespace std;

enum TokenType {KEYWORD, DOT, STRING, AND, OR, NOT, HEXDIGIT, VARIABLE,
	 			INTPART, E, M_OPERATOR, A_OPERATOR, COMP_OPERATOR, IF, ELSE,
                UNRECOGNIZED, END_OF_TEXT };

string tokenString(TokenType t);