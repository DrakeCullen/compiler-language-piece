#include "../include/ASTNode.h"

ASTNode::ASTNode(Token newToken, nodePtr left, nodePtr right )
{
    token = newToken;
    if (left != NULL)
        children.push_back(left);
    if (right != NULL)
        children.push_back(right);
}
void ASTNode::addChild(nodePtr child)
{
    children.push_back(child);
}

Token ASTNode::getToken()
{
    return token;
}

string ASTNode::getTokValue()
{
    return token.value;
}

shared_ptr<ASTNode> ASTNode::childAt(unsigned i)
{
    if (i < children.size())
        return children[i];
    else
        return NULL;
}

unsigned ASTNode::size()
{
    return children.size();
}

void ASTNode::print(ostream &out, int depth)
{
    out << setw(depth) << setfill(' ') << ' ';
    out << token << endl;
    for (auto child : children)
        child->print(out, depth + 1);
}
