/* We'll use this grammar transformed to LL(1)
Program     -> RuleList

RuleList    -> Rule RuleList | ε

Rule        -> rule id : if Cond then id

Cond   -> Atom | Atom AND Cond

Atom        -> id | id RelOp value
*/


#include "parser.h"

#include <stdexcept>

//Constructor that saves the given Token List and initializes the position on 0
Parser::Parser(const vector<Token>& tokenList) {

    tokens = tokenList;

    position = 0;
}

//Function that returns the current token
Token Parser::currentToken() {

    return tokens[position];
}

//Function that checks if a current token matches a type and optionally a value
bool Parser::match(TokenType type,const string& value) {

    if (position >= tokens.size()) {
        return false;
    }

    Token token = currentToken();

    // Type mismatch
    if (token.type != type) {
        return false;
    }

    // Optional value check
    if (value != "" && token.value != value) {
        return false;
    }

    return true;
}

//Function that consumes a token and checks if it matches with the expected token
Token Parser::consume(TokenType type,const string& value) {

    if (!match(type, value)) {

        throw runtime_error(
            "Unexpected token: " +
            currentToken().value
        );
    }

    return tokens[position++];
}


//We define a function for each rule of the grammar

//Program -> RuleList
Program* Parser::parseProgram() {

    Program* program = new Program();

    while (!match(TokenType::END_OF_FILE)) {
        Rule* rule = parseRule();
        program->rules.push_back(rule);
    }

    return program;
}


//Rule -> rule id : if Cond then Action
Rule* Parser::parseRule() {

    consume(TokenType::KEYWORD, "rule");

    string ruleName = consume(TokenType::IDENTIFIER).value;

    consume(TokenType::COLON, ":");

    consume(TokenType::KEYWORD, "if");

    Condition* condition = parseCondition();

    consume(TokenType::KEYWORD, "then");

    string action = consume(TokenType::IDENTIFIER).value;

    return new Rule(ruleName,condition,action);
}


// Cond -> Atom CondTail
// CondTail -> AND Atom CondTail | ε
Condition* Parser::parseCondition() {

    Condition* left =parseAtom();

    while (match(TokenType::KEYWORD, "AND")) {

        consume(TokenType::KEYWORD, "AND");

        Condition* right = parseAtom();

        left = new AndCondition(left,right);
    }

    return left;
}

//Atom -> id RelOp value | id
Condition* Parser::parseAtom() {

    string identifier = consume(TokenType::IDENTIFIER).value;

    //Comparison condition
    if (match(TokenType::REL_OPERATOR)) {

        string op = consume(TokenType::REL_OPERATOR).value;
        int value = stoi(consume(TokenType::VALUE).value);

        return new ComparisonCondition(identifier,op,value);
    }

    // Fact condition
    return new FactCondition(identifier);
}