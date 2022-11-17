#include "../include/SymbolTableEntry.h"

vector<string> SymbolTableEntry::getFormal() {
    return formal;
}

nodePtr SymbolTableEntry::getTree() {
    return tree;
}
SymbolTableEntry::SymbolTableEntry(nodePtr newTree) {
    setTree(newTree);
}
void SymbolTableEntry::setTree(nodePtr newTree) {
    tree=newTree;
}
void SymbolTableEntry::addFormal(string p) {
    formal.push_back(p);
}
ostream & operator <<(ostream &out,const SymbolTableEntry &ste) {
    bool first=true;
    for(auto item:ste.formal) {
        if (first) first=false;
        else out << ",";
        out << item;
    }
    out << endl;
    ste.tree->print(out,4);
    return out;
}