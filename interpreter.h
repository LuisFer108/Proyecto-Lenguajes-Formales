#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ast.h"

using namespace std;

class Interpreter {

private:

    //Variables
    // Example:
    // temp = 35
    unordered_map<string, int> variables;

    //Active facts
    // Example:
    // alert
    unordered_set<string> activeFacts;

public:

    //Function to add a variable
    void addVariable(const string& name,int value);

    //Function to add an initial fact
    void addFact(const string& fact);

    //Function to evaluate a condition
    bool evaluateCondition(Condition* condition);

    //Function to execute the program
    void execute(Program* program);

    //Function to print the active facts
    void printFacts();
};

#endif