#include "../include/SymbolTable.h"


SymbolTableEntry SymbolTable::get(string name) const {
    //if (table.find(name) == table.end()) throw SemanticException("Undefined reference to "+name);
    return table.find(name)->second;
}

void SymbolTable::add(string val, SymbolTableEntry ste) {
    table[val]=ste;
}

void SymbolTable::populate(nodePtr tree) {
    if (tree->getToken().type==P_VALDECL) {
        //cout << "YOYOPGKGPK:GKDFLGLFDJGFDJ " << tree->getTokValue() << endl;
        //tree->print(cout);
        table[tree->getToken().value]=SymbolTableEntry(tree->childAt(0));
    }
    else {
        for (unsigned i=0;i<tree->size();i++) {
            Token t=tree->childAt(i)->getToken();
            populate(tree->childAt(i));
        }
    } 
}
ostream & operator <<(ostream &out,const SymbolTable &st) {
    out << "Symbol Table Dump" << endl;
    for(auto item:st.table) {
        out << item.first << "|" << item.second << endl;
    }
    return out;
}