#include "../include/Parser.h"

Parser::Parser(string newFilename)
{
    tokens = Tokenizer();
    tokens.readFile(newFilename);
}

Parser::Parser(string newFilename, bool debug)
{
    tokens = Tokenizer(debug);
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

Result Parser::variable(Tokenizer &t)
{
    Token id = t.next();
    Result result;
    if (id.type == VARIABLE)
    {
        Token tok = t.peek();
        if (tok.type == EQUAL)
        {
            t.next();
            Tokenizer temp = t;
            if ((result = aExpression(t)).success)
            {
                return t.message("Variable assignment", make_shared<ASTNode>(Token(P_VALDECL, id.value), result.subtree));
            } 
            else
                return t.error("Expected expression after '='");
        }
        /* else
            return t.error("Expected '='"); */

        return t.message("!!!Found Variable", make_shared<ASTNode>(id));
    }
    return t.error("Expected a variable");
}

// Result Parser

// P fraction ::= DOT intpart
Result Parser::fraction(Tokenizer &t)
{
    if (t.next().type == DOT)
    {
        Token tok = t.next();
        if (tok.type == INTPART)
            return t.message("!!!Found Fraction", make_shared<ASTNode>(tok));
        return t.error("Expected integer part after decimal point");
    }
    return t.error("Expected a decimal point");
}

// pointfloat ::= {intpart} fraction | {intpart} DOT
Result Parser::pointFloat(Tokenizer &t)
{
    Token beforeDot = t.next();
    Result result;
    if (beforeDot.type == INTPART)
    {
        Tokenizer temp = t;
        if ((result = fraction(temp)).success)
        {
            t = temp;
            return t.message("!!!Found Point Float with fraction part",
                             make_shared<ASTNode>(Token(P_POINT_FLOAT, beforeDot.value + result.subtree->getTokValue())));
        }
        if (t.next().type == DOT)
            return t.message("!!!Found Point Float without fraction part",
                             make_shared<ASTNode>(Token(P_POINT_FLOAT, beforeDot.value + ".")));
        return t.error("Expected a decimal point or faction part after integer part");
    }
    return t.error("Expected integer part");
}

Result Parser::exponent(Tokenizer &t)
{
    if (t.next().type == E)
    {
        Token op = t.next();
        if (op.type != A_OPERATOR)
            return t.error("Expected an arithmetic operator");
        Token intPart = t.next();
        if (intPart.type == INTPART)
            return t.message("!!!Found exponent", make_shared<ASTNode>(Token(P_EXPONENT, op.value + intPart.value)));
        return t.error("Expected integer part after exponent operator");
    }
    return t.error("Expected an exponent operator");
}

// exponentfloat ::= (intpart | pointfloat) exponent
Result Parser::exponentFloat(Tokenizer &t)
{
    Tokenizer temp = t;
    Result result, result2;
    if ((result = pointFloat(temp)).success)
    {
        t = temp;
        if ((result2 = exponent(t)).success)
        {
            double base = stod(result.subtree->getTokValue());
            double exp = stod(result2.subtree->getTokValue());
            double value = base * pow(10, exp);
            return t.message("!!!Found point float followed by exponent",
                             make_shared<ASTNode>(Token(P_EXPONENT_FLOAT, to_string(value))));
        }
        return t.error("No exponent following pointfloat");
    }
    Token intPart = t.next();
    if (intPart.type == INTPART)
    {
        if ((result = exponent(t)).success)
        {
            double base = stod(intPart.value);
            double exp = stod(result.subtree->getTokValue());
            double value = base * pow(10, exp);
            return t.message("!!!Found integer part followed by exponent",
                             make_shared<ASTNode>(Token(P_EXPONENT_FLOAT, to_string(value))));
        }
        else
            return t.error("Expected exponent after integer part");
    }
    return t.error("Expected integer part or point float");
}

// floatnumber ::= pointfloat | exponentfloat
Result Parser::floatNumber(Tokenizer &t)
{
    Tokenizer temp = t;
    Result result;
    if ((result = exponentFloat(temp)).success)
    {
        t = temp;
        return t.message("!!!Found exponent float", result.subtree);
    }
    if ((result = pointFloat(t)).success)
        return t.message("!!!Found exponent float", result.subtree);
    return t.error("Expected a pointFloat or exponentFloat");
}
// integer ::= floatnumber | hexinteger | intpart    ---- added intpart
Result Parser::integer(Tokenizer &t)
{
    if (t.peek().type == HEXDIGIT)
    {
        Token tok = t.next();
        return t.message("!!!Found Hex Integer", make_shared<ASTNode>(tok));
    }
    Tokenizer temp = t;
    Result result;
    if ((result = floatNumber(temp)).success)
    {
        t = temp;
        return t.message("!!!Found floatnumber", result.subtree);
    }
    Token intPart = t.next();
    if (intPart.type == INTPART)
        return t.message("!!!Found integer", make_shared<ASTNode>(intPart));
    return t.error("Expected floatNumber or Hexdigit part");
}

// factor ::= integer  | variable | "(" conditionalExpression ")"  ----> added string
Result Parser::factor(Tokenizer &t)
{
    Tokenizer temp = t;
    Result result;
    if ((result = integer(temp)).success)
    {
        t = temp;
        return t.message("!!!Found integer", result.subtree);
    }
    temp = t;
    if ((result = variable(temp)).success)
    {
        t = temp;
        return t.message("!!!Found variable", result.subtree);
    }
    temp = t;
    if (temp.peek().type == STRING)
    {
        Token tok = temp.next();
        t = temp;
        return t.message("!!!Found string", make_shared<ASTNode>(tok));
    }
    if (t.next().type == LEFT_PAREN)
    {
        if ((result = conditionalExpression(t)).success)
        {
            if (t.next().type == RIGHT_PAREN)
                return t.message("!!!Found conditional expression", result.subtree);
            return t.error("Expected a right parenthesis");
        }
        return t.error("Expected an expression");
    }
    return t.error("Expected integer, floatnumber, variable, or (expression)");
}

// m_expr ::=  factor m_operator m_expr
Result Parser::mExpression(Tokenizer &t)
{
    Result result, result2;
    if ((result = factor(t)).success)
    {
        Token op = t.peek();
        if (op.type == M_OPERATOR)
        {
            t.next();
            if ((result2 = mExpression(t)).success)
                return t.message("!!!Found compound mExpression",
                                 make_shared<ASTNode>(op, result.subtree, result2.subtree));
        }
        return t.message("!!!Found simple mExpression", result.subtree);
    }
    return t.error("Expected a factor");
}

// a_expr ::= m_expr | a_expr "+" m_expr| a_expr "-" m_expr
// updated  a_expr ::= m_expr | m_expr "+" a_expr | m_expr  "-"  a_expr
Result Parser::aExpression(Tokenizer &t)
{
    Result result, result2;
    if ((result = mExpression(t)).success)
    {
        Token op = t.peek();
        if (op.type == A_OPERATOR)
        {
            t.next();
            if ((result2 = aExpression(t)).success)
                return t.message("!!!Found compound aExpression",
                                 make_shared<ASTNode>(op, result.subtree, result2.subtree));
            else
                return t.error("Expected m_expr after A_OPERATOR");
        }
        return t.message("!!!Found simple aExpression", result.subtree);
    }
    return t.error("Expected a m_expression");
}

// comparison ::= a_expr { comp_operator a_expr }   --- { is one or more
Result Parser::comparison(Tokenizer &t)
{
    Result result, result2;
    if ((result = aExpression(t)).success)
    {
        Token op = t.peek();
        if (op.type == COMP_OPERATOR)
        {
            t.next();
            if ((result2 = aExpression(t)).success)
                return t.message("Found compound comparison", make_shared<ASTNode>(op, result.subtree, result2.subtree));
            else
                return t.error("Expected a_expr after comp_operator");
        }
        return t.message("!!!Found simple comparison", result.subtree);
    }
    return t.error("Expected a_expr");
}

// not_test ::= comparison | "not" not_test
Result Parser::notTest(Tokenizer &t)
{
    Token notToken = t.peek();
    Result result;
    if (notToken.type == NOT)
    {
        t.next();
        if ((result = notTest(t)).success)
            return t.message("Found \"not\" followed by not_test", make_shared<ASTNode>(notToken, result.subtree));
        return t.error("Expected a notTest after NOT");
    }
    if ((result = comparison(t)).success)
        return t.message("Found comparison", result.subtree);
    return t.error("Expected comparison or not");
}

// and_test ::= not_test | and_test "and" not_test
// updated and_test ::= not_test | not_test "and" and_test
Result Parser::andTest(Tokenizer &t)
{
    Result result, result2;
    if ((result = notTest(t)).success)
    {
        Token andToken = t.peek();
        if (andToken.type == AND)
        {
            t.next();
            if ((result2 = andTest(t)).success)
                return t.message("Found compound and_test", make_shared<ASTNode>(andToken, result.subtree, result2.subtree));
            else
                return t.error("Expected not_test after and");
        }
        return t.message("Found notTest in andTest ", result.subtree);
    }
    return t.error("Expected not_test");
}

// or_test ::= and_test | or_test "or" and_test
// or_test ::= and_test | and_test "or" or_test
Result Parser::orTest(Tokenizer &t)
{
    Result result, result2;
    nodePtr orTree = make_shared<ASTNode>(Token(P_ORTEST));
    Token tok;
    while (tok.type != END_OF_TEXT)
    {
        tok = t.peek();
        if (tok.type == END_OF_TEXT)
            break;
        if ((result = andTest(t)).success)
        {
            Token orToken = t.peek();
            if (orToken.type == OR)
            {
                t.next();
                if ((result2 = orTest(t)).success)
                    orTree->addChild(make_shared<ASTNode>(orToken, result.subtree, result2.subtree));
                // return t.message("Found compound or_test", make_shared<ASTNode>(orToken, result.subtree, result2.subtree));
                else
                    return t.error("Expected and_test after or");
            }
            else
                orTree->addChild(result.subtree);
            // return t.message("Found andTest in orTest ", result.subtree);
        }
        //else
         //   orTree->addChild(result.subtree);
        // return t.error("Expected and_test");
    }
    return t.message("Found orTest", orTree);
}

// var2 if a > b else c + 3 if d > e else f
// conditional_expression ::= or_test ["if" or_test "else" conditional_expression]
// v2 conditional_expression ::= or_test ["if" or_test "else" conditional_expression]
Result Parser::conditionalExpression(Tokenizer &t)
{
    Result result, result2, result3;
    if ((result = orTest(t)).success)
    {
        Token ifToken = t.peek();
        nodePtr ifNode = make_shared<ASTNode>(ifToken, result.subtree);
        if (ifToken.type == IF)
        {
            t.next();
            if ((result2 = orTest(t)).success)
            {
                Token elseToken = t.next();
                ifNode->addChild(result2.subtree);
                if (elseToken.type == ELSE)
                {
                    if ((result3 = conditionalExpression(t)).success)
                    {
                        ifNode->addChild(result3.subtree);
                        return t.message("Found conditional expression", ifNode);
                    }
                    return t.error("Expected expression after else");
                }
                return t.error("Expected else after or_test");
            }
            return t.error("Expected or_test after if");
        }
        return t.message("Found orTest in conditionalExpression ", result.subtree);
        // Conditional expression no longer has to be "if else", this may have ramifications later
        // return t.error("Expected if after or_test");
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