#include "../include/Tokenizer.h"

string Tokenizer::filename="";

Tokenizer::Tokenizer() {
    text="";
}

bool Tokenizer::error(string message) {
		cerr << filename<<':'<<linepos<<':' << message << endl;	
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
    //cout << "Next character is " << text[pos] << endl;
    while (pos< text.size() && isspace(text[pos])){
        if (text[pos]=='\n') linepos++;
        pos++;
    }
    if (text[pos]=='{') { 
        while (pos< text.size() && text[pos]!='}') {
        if (text[pos]=='\n') linepos++;
        pos++;
        }
        pos++;		
    }
    char c=text[pos];
    if (c=='\'') {
        int offset=1;
        while (pos+offset<text.size() && text[pos+offset]!='\'') {
            if (text[pos+offset]=='\n') linepos++;
            offset++;
        }
        if (text[pos+offset]=='\'') offset++;
        Token retval=Token(STRING,text.substr(pos,offset));
        pos+=offset;
        return retval;
    }
}

void Tokenizer::printTokenSecret() {
//cout << token << endl;
}