#pragma once
#include "ASTNode.h"

typedef shared_ptr<ASTNode> nodePtr; 


class Result {
	public:
	bool success;
	nodePtr subtree;
	Result(bool newSuccess=false,nodePtr newSubtree=NULL);
	void print(ostream &out);
};