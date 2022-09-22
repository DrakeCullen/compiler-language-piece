#include "../include/Parser.h"

Parser::Parser(string newFilename)
{
    tokens = Tokenizer();
    tokens.readFile(newFilename);
}

Token Parser::peek()
{
    return tokens.peek();
}

Token Parser::next()
{
    return tokens.next();
}

Tokenizer &Parser::getTokenizer()
{
    return tokens;
}

bool Parser::variable(Tokenizer &t)
{
    if (t.next().type == VARIABLE)
        return true;
    return t.error("Expected a variable");
}

bool Parser::fraction(Tokenizer &t)
{
    if (t.next().type == DOT)
    {
        if (t.next().type == INTPART)
            return true;
        return t.error("Expected integer part after decimal point");
    }
    return t.error("Expected a decimal point");
}

// pointfloat ::= {intpart} fraction | {intpart} DOT
bool Parser::pointFloat(Tokenizer &t)
{
    if (t.next().type == INTPART)
    {
        Tokenizer temp = t;
        if (fraction(temp))
        {
            t = temp;
            return true;
        }
        if (t.next().type == DOT)
            return true;
        return t.error("Expected a decimal point or faction part after integer part");
    }
    return t.error("Expected integer part");
}

bool Parser::exponent(Tokenizer &t)
{
    if (t.next().type == E)
    {
        if (t.next().type != A_OPERATOR)
            return t.error("Expected an arithmetic operator");
        if (t.next().type == INTPART)
            return true;
        return t.error("Expected integer part after exponent operator");
    }
    return t.error("Expected an exponent operator");
}

// exponentfloat ::= (intpart | pointfloat) exponent
bool Parser::exponentFloat(Tokenizer &t)
{
    Tokenizer temp = t;
    if (pointFloat(temp))
    {
        t = temp;
        return exponent(t);
    }
    if (t.next().type == INTPART)
        return exponent(t);
    return t.error("Expected integer part or point float");
}

// factor ::= integer  | variable | "(" expression ")"
bool Parser::factor(Tokenizer &t)
{
    Tokenizer temp = t;
    if (integer(temp))
    {
        t = temp;
        return true;
    }
    temp = t;
    if (variable(temp))
    {
        t = temp;
        return true;
    }
    t = temp;
    // Add check for '(' expression ')'
    return t.error("Expected integer, floatnumber, variable, or (expression)");
}

// floatnumber ::= pointfloat | exponentfloat
bool Parser::floatNumber(Tokenizer &t)
{
    Tokenizer temp = t;
    if (exponentFloat(temp))
    {
        t = temp;
        return true;
    }
    if (pointFloat(t))
        return true;
    return t.error("Expected a pointFloat or exponentFloat");
}
// integer ::= floatnumber | hexinteger | intpart    ---- added intpart
bool Parser::integer(Tokenizer &t)
{
    if (t.peek().type == HEXDIGIT)
    {
        t.next();
        return true;
    }
    Tokenizer temp = t;
    if (floatNumber(temp))
    {
        t = temp;
        return true;
    }
    if (t.next().type == INTPART)
        return true;
    return t.error("Expected floatNumber or Hexdigit part");
}

// m_expr ::=  factor m_operator m_expr
bool Parser::mExpression(Tokenizer &t)
{
    if (factor(t))
    {
        if (t.peek().type == M_OPERATOR)
        {
            t.next();
            if (mExpression(t))
                return true;
            return t.error("Expected a m_expression after m_operator");
        }
        return true;
    }
    return t.error("Expected a factor");
}

// a_expr ::= m_expr | a_expr "+" m_expr| a_expr "-" m_expr
// updated  a_expr ::= m_expr | m_expr "+" a_expr | m_expr  "-"  a_expr
bool Parser::aExpression(Tokenizer &t)
{
    if (mExpression(t))
    {
        if (t.peek().type == A_OPERATOR)
        {
            t.next();
            if (aExpression(t))
                return true;
            else
                return t.error("Expected m_expr after A_OPERATOR");
        }
        return true;
    }
    return t.error("Expected a m_expression");
}

// comparison ::= a_expr { comp_operator a_expr }   --- { is one or more
bool Parser::comparison(Tokenizer &t)
{
    if (aExpression(t))
    {
        if (t.peek().type == COMP_OPERATOR)
        {
            t.next();
            if (aExpression(t))
                return true;
            else
                return t.error("Expected a_expr after comp_operator");
        }
        return true;
    }
    return t.error("Expected a_expr");
}

// not_test ::= comparison | "not" not_test
bool Parser::notTest(Tokenizer &t)
{
    if (t.peek().type == NOT)
    {
        t.next();
        if (notTest(t)) return true;
        return t.error("Expected a notTest after NOT");
    }
    if (comparison(t)) return true;
    return t.error("Expected comparison or not, i'm soft and frictionless");
}

// and_test ::= not_test | and_test "and" not_test
// updated and_test ::= not_test | not_test "and" and_test
bool Parser::andTest(Tokenizer &t)
{
    if (notTest(t))
    {
        if (t.peek().type == AND)
        {   
            t.next();
            if (andTest(t)) return true;
            else return t.error("Expected not_test after and");
        }
        return true;
    }
    return t.error("Expected not_test");
}

// or_test ::= and_test | or_test "or" and_test
// or_test ::= and_test | and_test "or" or_test
bool Parser::orTest(Tokenizer &t)
{
    if (andTest(t))
    {
        if (t.peek().type == OR)
        {
            t.next();
            if (orTest(t)) return true;
            else return t.error("Expected and_test after or");
        }
        return true;
    }
    return t.error("Expected and_test");
}

// var2 if a > b else c + 3 if d > e else f
//conditional_expression ::= or_test ["if" or_test "else" conditional_expression]
//v2 conditional_expression ::= or_test ["if" or_test "else" conditional_expression]
bool Parser::conditionalExpression(Tokenizer &t){
    if(orTest(t)){
        if(t.next().type == IF){
            if(orTest(t)){
                if(t.next().type == ELSE){
                    if(orTest(t))return true;
                    return t.error("Expected expression after else");
                }
                return t.error("Expected else after or_test");
            }
            return t.error("Expected or_test after if");
        }
        return t.error("Expected if after or_test");
    }
    return t.error("Expected or_test");
}

// v2
/* bool Parser::conditionalExpression(Tokenizer &t){
    if(orTest(t)){
        if(t.next().type == IF){
            if(orTest(t)){
                if(t.next().type == ELSE){
                    if(conditionalExpression(t))return true;
                    return t.error("Expected expression after else");
                }
                return t.error("Expected else after or_test");
            }
            return t.error("Expected or_test after if");
        }
        return t.error("Expected if after or_test");
    }
    return t.error("Expected or_test");
} */