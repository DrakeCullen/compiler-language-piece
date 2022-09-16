#include <string>
#include <iostream>

using namespace std;

enum TokenType{KEYWORD, INTEGER, DECIMAL_INTEGER, STRING, HEX_INTEGER, HEX_DIGIT,
	 			FLOAT_NUMBER, EXPONENT_FLOAT, INTPART, FRACTION, EXPONENT, EXPRESSION,
				EXPRESSION_LIST, EXPRESSION_STMT, CONDITIONAL_EXPRESSION, OR_TEST, AND_TEST,
				NOT_TEST, COMPARISON, COMP_OPERATOR, AND_EXPR, XOR_EXPR, OR_EXPR, U_EXPR, M_EXPR, A_EXPR,
                UNRECOGNIZED, END_OF_TEXT
};

string tokenString(TokenType t) {
    switch(t) {
        case KEYWORD: return "KEYWORD";
        case INTEGER: return "INTEGER";
        case DECIMAL_INTEGER: return "DECIMAL_INTEGER";
        case STRING: return "STRING";
        case HEX_INTEGER: return "HEX_INTEGER";
        case HEX_DIGIT: return "HEX_DIGIT";
        case FLOAT_NUMBER: return "FLOAT_NUMBER";
        case EXPONENT_FLOAT: return "EXPONENT_FLOAT";
        case INTPART: return "INTPART";
        case FRACTION: return "FRACTION";
        case EXPONENT: return "EXPONENT";
        case EXPRESSION: return "EXPRESSION";
        case EXPRESSION_LIST: return "EXPRESSION_LIST";
        case EXPRESSION_STMT: return "EXPRESSION_STMT";
        case CONDITIONAL_EXPRESSION: return "CONDITIONAL_EXPRESSION";
        case OR_TEST: return "OR_TEST";
        case AND_TEST: return "AND_TEST";
        case NOT_TEST: return "NOT_TEST";
        case COMPARISON: return "COMPARISON";
        case COMP_OPERATOR: return "COMP_OPERATOR";
        case AND_EXPR: return "AND_EXPR";
        case XOR_EXPR: return "XOR_EXPR";
        case OR_EXPR: return "OR_EXPR";
        case U_EXPR: return "U_EXPR";
        case M_EXPR: return "M_EXPR";
        case A_EXPR: return "A_EXPR";
        case UNRECOGNIZED: return "UNRECOGNIZED";
        default: return "UNKNOWN";
    }
}
