#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "lexer.h"
#include "ast.h"

using namespace std;

class Parser {

private:
    vector<Token> tokens;
    size_t position;

    // Helper functions
    Token currentToken();

    bool match(TokenType type,const string& value = "");

    Token consume(TokenType type,const string& value = "");

public:

    Parser(const vector<Token>& tokenList);

    //Parsing functions
    Program* parseProgram();

    Rule* parseRule();

    Condition* parseCondition();

    Condition* parseAtom();
};

#endif