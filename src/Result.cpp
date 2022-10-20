#include "../include/Result.h"

Result::Result(bool newSuccess,nodePtr newSubtree) {
    success=newSuccess;
    subtree=newSubtree;
}
void Result::print(ostream &out) {
    out << "Result " << (success?"true":"false")<< endl;
    subtree->print(out);
}