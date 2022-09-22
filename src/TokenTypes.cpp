#include <string>
#include <iostream>

using namespace std;

enum TokenType {KEYWORD, DOT, STRING, AND, OR, NOT, HEXDIGIT, VARIABLE,
	 			INTPART, E, M_OPERATOR, A_OPERATOR, COMP_OPERATOR, IF, ELSE,
                UNRECOGNIZED, END_OF_TEXT };

string tokenString(TokenType t) {
    switch(t) {
        case KEYWORD: return "KEYWORD";
        case HEXDIGIT: return "HEXDIGIT";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        case DOT: return "DOT";
        case STRING: return "STRING";
        case INTPART: return "INTPART";
        case VARIABLE: return "VARIABLE";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case E: return "E";
        case M_OPERATOR: return "Multipy_OPERATOR";
        case A_OPERATOR: return "Add_OPERATOR";
        case COMP_OPERATOR: return "COMP_OPERATOR";
        case UNRECOGNIZED: return "UNRECOGNIZED";
        case END_OF_TEXT: return "END_OF_TEXT";
        default: return "UNKNOWN";
    }
}
