#pragma once
#include "ASTNode.h"

typedef shared_ptr<ASTNode> nodePtr; 

class SymbolTableEntry {
	vector<string> formal;
	nodePtr tree;
	public:
	vector<string> getFormal();
	nodePtr getTree();
	SymbolTableEntry(nodePtr newTree=NULL);
	void setTree(nodePtr newTree);
	void addFormal(string p);
	friend ostream & operator <<(ostream &out,const SymbolTableEntry &ste); 
};