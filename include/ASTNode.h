#pragma once
#include "Token.h"
#include <memory>
#include <vector>
#include <iomanip>


class ASTNode {
    typedef shared_ptr<ASTNode> nodePtr; 
	Token token;
	vector<nodePtr> children;
	public:
	ASTNode(Token newToken,nodePtr left=NULL,nodePtr right=NULL);
	void addChild(nodePtr child);
	Token getToken();
	nodePtr childAt(unsigned i);
	unsigned size();
	void print(ostream &out,int depth=0);
    string getTokValue();
};