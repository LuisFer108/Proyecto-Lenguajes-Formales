#include "lexer.h"

//constructor for initializing values
Token::Token(TokenType token_type, const string& token_value,int ln)
    : type(token_type), value(token_value), line(ln) {}


//Constructor for LexicalAnalyzer
LexicalAnalyzer::LexicalAnalyzer(const string& source){
    input = source;
    position = 0;

    initKeywords();
}


//Function to initialize the keywords map
void LexicalAnalyzer::initKeywords(){
    keywords["if"] = TokenType::KEYWORD;
    keywords["then"] = TokenType::KEYWORD;
    keywords["rule"] = TokenType::KEYWORD;
    keywords["AND"] = TokenType::KEYWORD;
}


//Function to check if a character is whitespace
bool LexicalAnalyzer::isWhitespace(char c){
    return (c==' '|| c=='\t'|| c=='\n' || c=='\r');
}


//Function to check if a character is alphabetic
bool LexicalAnalyzer::isAlpha(char c){
    return ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='_') );
}


//Function to check if a character is a digit
bool LexicalAnalyzer::isDigit(char c){
    return (c>='0'&& c<='9');
}


bool LexicalAnalyzer::isAlphaNumeric(char c){
    return (isAlpha(c) || isDigit(c));
}


//Function to get the next word (identifier or keyword from the input)
string LexicalAnalyzer::getNextWord(){
    size_t start = position;

    while (position < input.length() &&
           isAlphaNumeric(input[position])){
        position++;
    }

    return input.substr(start, position-start);
}


//Function to get the next number(value)
string LexicalAnalyzer::getNextNumber(){
    size_t start=position;

    while (position<input.length() &&
           isDigit(input[position]))
    {
        position++;
    }

    return input.substr(start, position-start);
}


vector<Token> LexicalAnalyzer::tokenize(){
    vector<Token> tokens;

    while (position < input.length()){

        char currentChar = input[position];

        //if for skipping whitespaces
        if (isWhitespace(currentChar)){
            position++;
            continue;
        }

        //checks if the current character is alphabetic
        if(isAlpha(currentChar)){

            //saves the word
            string word = getNextWord();

            if(keywords.find(word) != keywords.end()){

                //inserts the keyword in the container
                tokens.emplace_back(TokenType::KEYWORD,word);

            } else {

                //inserts the identifier in the container
                tokens.emplace_back(TokenType::IDENTIFIER,word);
            }
        }

        //checks if the current character is an integer
        else if(isDigit(currentChar)){

            //saves the value
            string value = getNextNumber();

            //inserts the value in the container
            tokens.emplace_back(TokenType::VALUE, value);
        }

        else if(currentChar == ':'){

            tokens.emplace_back(TokenType::COLON,
                                string(1,currentChar));

            position++;
        }

        else if(currentChar == '>' ||
                currentChar== '<' ||
                currentChar == '='){

            tokens.emplace_back(TokenType::REL_OPERATOR,
                                string(1,currentChar));

            position++;
        }

        else{

            tokens.emplace_back(TokenType::UNKNOWN,
                                string(1, currentChar));

            position++;
        }
    }
    tokens.emplace_back(TokenType::END_OF_FILE, "EOF");

    return tokens;
}


//Function to convert TokenType to string for printing
string getTokenTypeName(TokenType type){

    switch (type)
    {
        case TokenType::KEYWORD:
            return "KEYWORD";

        case TokenType::IDENTIFIER:
            return "IDENTIFIER";

        case TokenType::VALUE:
            return "VALUE";

        case TokenType::REL_OPERATOR:
            return "REL_OPERATOR";

        case TokenType::COLON:
            return "COLON";

        case TokenType::UNKNOWN:
            return "UNKNOWN";

        case TokenType::END_OF_FILE:
            return "END OF FILE";

        default:
            return "UNDEFINED";
    }
}


void printTokens(const vector<Token>& tokens){

    for (const auto& token: tokens){

        cout << "Type: "
             << getTokenTypeName(token.type)
             << ", Value: "
             << token.value
             << endl;
    }
}