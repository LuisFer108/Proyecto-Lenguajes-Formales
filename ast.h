#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


//Helper for indentation
inline void printIndent(int indent) {

    for (int i = 0; i < indent; i++) {
        cout << "  ";
    }
}


// ======================
// CONDITION BASE CLASS
// ======================
class Condition {
public:
    virtual ~Condition() = default;

    virtual void print(int indent = 0) =0;
};

//
// ======================
// FACT CONDITION
// ======================
//
class FactCondition :public Condition {
public:

    string identifier;

    FactCondition(const string& id)
        : identifier(id) {}

    void print(int indent = 0) override {

        printIndent(indent);

        cout << "FactCondition: " << identifier << endl;
    }
};


// ======================
// COMPARISON CONDITION
// ======================
class ComparisonCondition :public Condition {

public:

    string identifier;

    string op;

    int value;

    ComparisonCondition(const string& id,const string& oper,int val)
        : identifier(id),
          op(oper),
          value(val) {}

    void print(int indent = 0) override {

        printIndent(indent);

        cout << "ComparisonCondition" << endl;

        printIndent(indent + 1);
        cout << "Identifier: " << identifier << endl;

        printIndent(indent + 1);
        cout << "Operator: " << op << endl;

        printIndent(indent + 1);
        cout << "Value: " << value << endl;
    }
};


// ======================
// AND CONDITION
// ======================
class AndCondition :public Condition {

public:

    Condition* left;

    Condition* right;

    AndCondition(Condition* l,Condition* r)
        : left(l),
          right(r) {}

    void print(int indent = 0) override {

        printIndent(indent);

        cout << "AndCondition" << endl;

        printIndent(indent + 1);
        cout << "LEFT:" << endl;

        left->print(indent + 2);

        printIndent(indent + 1);
        cout << "RIGHT:" << endl;

        right->print(indent + 2);
    }
};

// ======================
// RULE
// ======================
class Rule {

public:

    string name;

    Condition* condition;

    string action;

    Rule(const string& n, Condition* cond, const string& act)
        : name(n),
          condition(cond),
          action(act) {}

    void print(int indent = 0) {

        printIndent(indent);

        cout << "Rule: " << name << endl;

        printIndent(indent + 1);
        cout << "Condition:" << endl;

        condition->print(indent + 2);

        printIndent(indent + 1);
        cout << "Action: " << action << endl;
    }
};

// ======================
// PROGRAM
// ======================
class Program {

public:

    vector<Rule*> rules;

    void print() {

        cout << "Program" << endl;

        for (Rule* rule : rules) {
            rule->print(1);
        }
    }
};

#endif