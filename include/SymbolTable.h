#pragma once
#include "SymbolTableEntry.h"
#include <map>


class SymbolTable {
	map<string,SymbolTableEntry> table;
	public:
	SymbolTableEntry get(string name) const;
	void add(string val, SymbolTableEntry ste);
	void populate(nodePtr tree);
	friend ostream & operator <<(ostream &out,const SymbolTable &st);
};