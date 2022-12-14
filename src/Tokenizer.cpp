#include "../include/Tokenizer.h"
#include <algorithm>

string Tokenizer::filename="";

Tokenizer::Tokenizer() {
    text="";
    debug=false;
}

Tokenizer::Tokenizer(bool newDebug) {
    text="";
    debug=newDebug;
}

Result Tokenizer::error(string message) {
    if (debug) 
        cerr << filename<<':'<<linepos<<':' << message << endl;		
	return Result(false);
}

Result Tokenizer::message(string message, nodePtr subtree=NULL) {
	if (debug)	
        cout << filename<<':'<<linepos<<':' << message << ":"<< text.substr(pos,10) << endl;	
	return Result(true,subtree);
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
    if (c=='<' || c=='>') return compOperator();
    if (c=='=' || c=='!') {
        if (pos+1 < text.size() && text[pos+1]=='=') 
            return Token(COMP_OPERATOR,text.substr(pos,2));
        else if (c != '!')
            return Token(EQUAL, text.substr(pos,1));
    }
    if (c=='.') return Token(DOT,text.substr(pos,1));
    if (c=='(') return Token(LEFT_PAREN,text.substr(pos,1));
    if (c==')') return Token(RIGHT_PAREN,text.substr(pos,1));
    if (c=='*' || c=='/' || c=='%' ) 
        if (pos+1 < text.size() && text[pos] == '/' && text[pos+1]=='/') return Token(M_OPERATOR,text.substr(pos,2));
        else return Token(M_OPERATOR,text.substr(pos,1));
    if (c=='+' || c=='-') return Token(A_OPERATOR,text.substr(pos,1));
    if (isalpha(c) || (isdigit(c) && pos + 1 < text.size() && (text[pos+1] == 'x' || text[pos+1] == 'X'))) return characterParser();
    if (isdigit(c)) {
        unsigned newpos=pos;
        while(newpos<text.size() && isdigit(text[newpos])) newpos++;
        return Token(INTPART,text.substr(pos,newpos-pos));
    } 
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
    return ((pos+1<text.size() && (text.substr(pos,2)=="or" || text.substr(pos,2)=="if")) ||
           (pos+2<text.size() && (text.substr(pos,3)=="and" || text.substr(pos,3)=="not")) ||
           (pos+3<text.size() && text.substr(pos,4)=="else")); 
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
        if (text.substr(pos,2)=="if") return Token(IF,"if");
        if (text.substr(pos,4)=="else") return Token(ELSE,"else");
    } 
    unsigned newpos=pos;
    while (newpos<text.size() && isalnum(text[newpos])) newpos++;
    string value=text.substr(pos,newpos-pos);
    //if (all_of(value.begin(), value.end(), ::isdigit)) return Token(INTPART,value);
    if (value=="E" || value=="e") return Token(E,value);
    if (value[0]=='0' && (value[1]=='x' || value[1]=='X')) {
        bool validHex = true;
        for (unsigned i=2;i<value.size();i++)  
            if (!isxdigit(value[i])) {
                validHex=false;
                break;
            }
        if (validHex) return Token(HEXDIGIT,value); // Hexinteger
    } 
    return Token(VARIABLE,value);
}

