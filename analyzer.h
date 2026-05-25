#ifndef ANALYZER_H
#define ANALYZER_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include "ast.h"

using namespace std;

class Analyzer {

private:
    //Helper function
    //Converts conditions into strings
    string serializeCondition(Condition* condition);

public:

    //Conflict analysis
    void detectConflicts(Program* program);

    //Redundant rules
    void detectRedundantRules(Program* program);

    //Potentially inactive rules
    void detectInactiveRules(Program* program);
};

#endif