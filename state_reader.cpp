#include "state_reader.h"

//Function to load the initial facts
void loadInitialState(const string& input,Interpreter& interpreter) {

    stringstream ss(input);

    string line;

    while (getline(ss, line)) {

        //Ignore empty lines
        if (line.empty()) {
            continue;
        }

        //Variable assignment
        if (line.find('=') != string::npos) {

            stringstream lineStream(line);

            string name;
            string equalSign;

            int value;

            lineStream
                >> name
                >> equalSign
                >> value;

            interpreter.addVariable(name,value);
        }

        //Active fact
        else {

            interpreter.addFact(line);
        }
    }
}