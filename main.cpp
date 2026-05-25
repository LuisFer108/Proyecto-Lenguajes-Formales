#include <iostream>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "state_reader.h"
#include "analyzer.h"

using namespace std;

//
// Reads multiline input until END
//
string readMultilineInput() {

    string input;

    string line;

    while (getline(cin, line)) {

        //
        // Stop condition
        //
        if (line == "END") {
            break;
        }

        input += line + "\n";
    }

    return input;
}

int main() {

    //
    // READ RULES
    //
    cout << "Enter rules "
         << "(type END to finish):"
         << endl;

    string rulesInput =
        readMultilineInput();

    //
    // READ INITIAL STATE
    //
    cout << endl;

    cout << "Enter initial state "
         << "(type END to finish):"
         << endl;

    string stateInput = readMultilineInput();

    //
    // PRINT INPUT
    //
    cout << endl;
    cout << "===== RULES ====="
         << endl;

    cout << rulesInput
         << endl;

    cout << "===== STATE ====="
         << endl;

    cout << stateInput
         << endl;

    //
    // LEXER
    //
    LexicalAnalyzer lexer(
        rulesInput
    );

    vector<Token> tokens =
        lexer.tokenize();

    //
    // PRINT TOKENS
    //
    cout << endl;
    cout << "===== TOKENS ====="
         << endl;

    printTokens(tokens);

    //
    // PARSER
    //
    Parser parser(tokens);

    Program* program =
        parser.parseProgram();

    //
    // PRINT AST
    //
    cout << endl;
    cout << "===== AST ====="
         << endl;

    program->print();

    //
    // INTERPRETER
    //
    Interpreter interpreter;

    //
    // LOAD INITIAL STATE
    //
    loadInitialState(
        stateInput,
        interpreter
    );

    //
    // EXECUTE
    //
    interpreter.execute(program);

    //
    // OUTPUT
    //
    cout << endl;
    cout << "===== OUTPUT ====="
         << endl;

    interpreter.printFacts();

    //
    // STATIC ANALYSIS
    //
    Analyzer analyzer;

    cout << endl;
    cout << "===== STATIC ANALYSIS ====="
         << endl;

    analyzer.detectConflicts(program);

    analyzer.detectRedundantRules(program);

    analyzer.detectInactiveRules(program);

    return 0;
}