#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// Enum class to define different categories of tokens in a structured format
enum class TokenType{
    KEYWORD,
    IDENTIFIER,
    VALUE,
    REL_OPERATOR,
    COLON,
    UNKNOWN,
    END_OF_FILE                                                
};

//Structure to represent a token with its value and type
struct Token{
    TokenType type; //Category of the token
    string value; //the actual text
    int line; //Line number, usefull for error messages

    //constructor for initializing values
    Token(TokenType token_type,
          const string& token_value,
          int ln = 0);
};

class LexicalAnalyzer {
    private:
        string input; //string in which we will store the input
        size_t position; //variable to keep track of the position of the input
        unordered_map<string, TokenType> keywords; //container to store the pairs of keywords

        //Function to initialize the keywords map
        void initKeywords();

        //Function to check if a character is whitespace
        bool isWhitespace(char c);

        //Function to check if a character is alphabetic
        bool isAlpha(char c);

        //Function to check if a character is a digit
        bool isDigit(char c);

        bool isAlphaNumeric(char c);

        //Function to get the next word (identifier or keyword from the input)
        string getNextWord();

        //Function to get the next number(value)
        string getNextNumber();

    public:
        //Constructor for LexicalAnalyzer
        LexicalAnalyzer(const string& source);

        vector<Token> tokenize();
};

//Function to convert TokenType to string for printing
string getTokenTypeName(TokenType type);

void printTokens(const vector<Token>& tokens);

#endif