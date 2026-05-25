#include "interpreter.h"
#include <algorithm>

//Add variable
void Interpreter::addVariable(const string& name,int value) {

    variables[name] = value;
}

//Add fact
void Interpreter::addFact(const string& fact) {

    activeFacts.insert(fact);
}

//Evaluate conditions recursively
bool Interpreter::evaluateCondition(Condition* condition) {

    //FACT CONDITION
    if (FactCondition* fact = dynamic_cast<FactCondition*>(condition)) {

        return activeFacts.count(fact->identifier);
    }

    //COMPARISON CONDITION
    if (ComparisonCondition* comp = dynamic_cast<ComparisonCondition*>(condition)) {

        //Variable does not exist
        if (variables.find(comp->identifier) == variables.end()) {

            return false;
        }

        int variableValue = variables[comp->identifier];

        if (comp->op == ">") {

            return variableValue > comp->value;
        }

        if (comp->op == "<") {

            return variableValue < comp->value;
        }

        if (comp->op == "=") {

            return variableValue == comp->value;
        }

        return false;
    }

    // AND CONDITION
    if (AndCondition* andCond = dynamic_cast<AndCondition*>(condition)) {

        return evaluateCondition(andCond->left) && evaluateCondition(andCond->right);
    }

    return false;
}

// Execute program
void Interpreter::execute(Program* program) {

    bool changed;

    do {

        changed = false;

        // Evaluate all rules
        for (Rule* rule : program->rules) {

            if (evaluateCondition(rule->condition)) {

                // New fact discovered
                if (activeFacts.count(rule->action) == 0) {

                    activeFacts.insert(rule->action);
                    changed = true;
                }
            }
        }

    } while (changed);
}

// Print facts sorted alphabetically
void Interpreter::printFacts() {

    vector<string> facts(activeFacts.begin(),activeFacts.end());

    sort(facts.begin(),facts.end());

    for (const string& fact : facts) {

        cout << fact << endl;
    }
}