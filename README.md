# Rule-Based Inference Engine in C++

**Students:**
- Jhon David Santamaria Cossio
- Luis Fernando Bernal Ramirez


** Video Explanation:**  https://drive.google.com/file/d/1ZcACtXODlmHN6UYr3t12pfD3rjWBJeP3/view?usp=sharing



## Overview

This project implements a small rule-based inference engine in C++.  
The system includes:

- A lexical analyzer (lexer)
- A recursive descent parser
- An Abstract Syntax Tree (AST)
- A forward-chaining interpreter
- A basic static analysis module

The engine reads rules and an initial state, evaluates conditions, activates facts, and infers new conclusions until no more rules can be triggered.

---

# Development Environment

This project was developed and tested using:

- **Operating System:** macOS 26.5
- **IDE / Editor:** Visual Studio Code
- **Compiler:** g++

---

# Features

## Lexical Analysis

The lexer tokenizes the input source code into:

- Keywords
- Identifiers
- Numeric values
- Relational operators
- Assignment symbols

Supported keywords:

```txt
rule
if
then
AND
```

---

## Parsing

The parser is implemented using recursive descent parsing.

Supported grammar:

```txt
Program     -> RuleList

Rule        -> rule IDENTIFIER : if Condition then IDENTIFIER

Condition   -> Atom
             | Atom AND Condition

Atom        -> IDENTIFIER
             | IDENTIFIER REL_OPERATOR VALUE
```

---

## AST (Abstract Syntax Tree)

The parser builds an AST composed of:

- Program
- Rule
- FactCondition
- ComparisonCondition
- AndCondition

The AST can also be printed for debugging and visualization.

---

## Interpreter

The interpreter executes the rule system using forward chaining.

Supported features:

- Variable comparisons
- Logical AND conditions
- Fact propagation
- Iterative inference until fixed point

Example:

```txt
rule r1:
if temp > 30 then alert

rule r2:
if alert then fan_on
```

If:

```txt
temp = 35
```

The engine infers:

```txt
alert
fan_on
```

---

## Static Analysis Module

The analyzer performs three basic checks:

### Conflict Detection

Detects multiple rules generating the same action.

Example:

```txt
rule r1:
if temp > 30 then fan_on

rule r2:
if humidity < 50 then fan_on
```

---

### Redundant Rules

Detects rules with identical conditions and actions.

Example:

```txt
rule r1:
if temp > 30 then alert

rule r2:
if temp > 30 then alert
```

---

### Potentially Inactive Rules

Detects rules that may never activate.

Example:

```txt
rule r1:
if unknown_fact then alert
```

---

# Project Structure

```txt
.
├── lexer.h
├── lexer.cpp
├── parser.h
├── parser.cpp
├── ast.h
├── interpreter.h
├── interpreter.cpp
├── analyzer.h
├── analyzer.cpp
├── state_reader.h
├── state_reader.cpp
├── main.cpp
└── README.md
```

---

# Compilation

Compile using g++:

```bash
g++ lexer.cpp parser.cpp interpreter.cpp state_reader.cpp analyzer.cpp main.cpp -o main
```

---

# Execution

Run the executable:

```bash
./main
```

---

# Input Format

The program reads multiline input using `getline()`.

Type:

```txt
END
```

to finish entering rules or state data.

---

## Example Input

### Rules

```txt
rule r1:
if temp > 30 AND humidity < 50 then alert

rule r2:
if alert then fan_on

END
```

### Initial State

```txt
temp = 35
humidity = 40

END
```

---

# Example Output

```txt
===== OUTPUT =====

alert
fan_on
```

---

# Internal Architecture

## Pipeline

```txt
Source Code
    ↓
Lexer
    ↓
Tokens
    ↓
Parser
    ↓
AST
    ↓
Interpreter
    ↓
Inferred Facts
```

Static analysis operates directly on the AST:

```txt
AST
 ↓
Analyzer
```

---

# Object-Oriented Concepts Used

The project heavily uses:

- Inheritance
- Polymorphism
- Abstract classes
- Dynamic dispatch
- Recursive data structures

Example:

```cpp
class Condition {
public:
    virtual void print(int indent = 0) = 0;
};
```

Derived classes:

- FactCondition
- ComparisonCondition
- AndCondition

---

# Example AST

Input:

```txt
if temp > 30 AND humidity < 50
```

AST:

```txt
AndCondition
  LEFT:
    ComparisonCondition
      Identifier: temp
      Operator: >
      Value: 30

  RIGHT:
    ComparisonCondition
      Identifier: humidity
      Operator: <
      Value: 50
```

---

# Future Improvements

Possible extensions include:

- OR conditions
- NOT operator
- Parenthesized expressions
- Better static analysis
- Rule priorities
- Conflict resolution strategies
- Memory management using smart pointers
- File-based input
- Full type checking

---

