#include "../include/Tokenizer.h"
#include <algorithm>

string Tokenizer::filename="";

Tokenizer::Tokenizer() {
    text="";
}

bool Tokenizer::error(string message) {
		//cerr << filename<<':'<<linepos<<':' << message << endl;	
		return false;
}

bool Tokenizer::message(string message) {
		cout << filename<<':'<<linepos<<':' << message << ":"<< text.substr(pos,10) << endl;	
		return true;
}

void Tokenizer::readFile(string newFilename) {
		ifstream file(newFilename);
		Tokenizer::filename=newFilename;
		stringstream buffer;
		buffer << file.rdbuf();
		text=buffer.str();
		pos=0;
		linepos=1;
		charpos=1;
}


void Tokenizer::setText(string newText) {
		text=newText;
		pos=0;
		linepos=1;
		charpos=1;
}

Token Tokenizer::next() {
    // Keep track where we are in the text and produce the next token
    Token p=peek();
    pos+=p.value.size();
    return p;
}

Token Tokenizer::peek() {
    // produce what the next token will be but don't consume
    consumeSpaces();
    if (isComment()) consumeComments();
    if (pos >= text.size()) return Token(END_OF_TEXT,"");
    char c=text[pos];
    if (c=='\'') return getString();
    if (c=='<' || c=='>' || c=='=' || c=='!') return compOperator();
    if (c=='.') return Token(DOT,text.substr(pos,1));
    if (c=='*' || c=='/' || c=='%' ) 
        if (pos+1 < text.size() && text[pos] == '/' && text[pos+1]=='/') return Token(M_OPERATOR,text.substr(pos,2));
        else return Token(M_OPERATOR,text.substr(pos,1));
    if (c=='+' || c=='-') return Token(A_OPERATOR,text.substr(pos,1));
    if (isalnum(c)) return characterParser();
    return Token(UNRECOGNIZED, "");
}

void Tokenizer::consumeSpaces() {
    while (pos < text.size() && isspace(text[pos])){
        if (text[pos]=='\n') linepos++;
        pos++;
    }
}

bool Tokenizer::isComment() {
    return text[pos]=='\'' && pos+2<text.size() && text[pos+1]=='\'' && text[pos+2]=='\'';
}

void Tokenizer::consumeComments() {
    pos+=3;
    while (!isComment() && pos<text.size()) {
        if (text[pos]=='\n') linepos++;
        pos++;
    }
    pos+=3;	
    consumeSpaces();	
}

Token Tokenizer::getString() {
    int offset=1;
    while (pos+offset<text.size() && text[pos+offset]!='\'') {
        if (text[pos+offset]=='\n') linepos++;
        offset++;
    }
    if (text[pos+offset]=='\'') offset++;
    return Token(STRING,text.substr(pos,offset));
}

Token Tokenizer::compOperator() {
    if (pos+1<text.size() && text[pos+1]=='=') 
        return Token(COMP_OPERATOR,text.substr(pos,2));
    return Token(COMP_OPERATOR,text.substr(pos,1));
}

bool Tokenizer::isKeyword() {
    return (pos+1<text.size() && text.substr(pos,2)=="or") ||
           (pos+2<text.size() && text.substr(pos,3)=="and" || text.substr(pos,3)=="not");
}

Token Tokenizer::intPart() {
    unsigned newpos=pos;
    while (newpos<text.size() && isdigit(text[newpos]))
        newpos++;
    return Token(INTPART,text.substr(pos,newpos-pos));
}

Token Tokenizer::characterParser() {
    if (isKeyword()) {
        if (text.substr(pos,2)=="or") return Token(OR,"or");
        if (text.substr(pos,3)=="and") return Token(AND,"and");
        if (text.substr(pos,3)=="not") return Token(NOT,"not");
    } 
    unsigned newpos=pos;
    while (newpos<text.size() && isalnum(text[newpos])) newpos++;
    string value=text.substr(pos,newpos-pos);
    if (value=="E") return Token(E,value);
    if (value[0]=='0' && (value[1]=='x' || value[1]=='X')) {
        bool validHex = true;
        for (unsigned i=2;i<value.size();i++)  
            if (!isxdigit(value[i])) {
                validHex=false;
                break;
            }
        if (validHex) return Token(HEXDIGIT,value);
    } 
    if (all_of(value.begin(), value.end(), ::isdigit)) return Token(INTPART,value);
    return Token(VARIABLE,value);
}

