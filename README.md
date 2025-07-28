**Stack-Based Calculator with Infix to Postfix Conversion**

A comprehensive C implementation of a stack-based calculator that
processes mathematical expressions by converting infix notation to
postfix notation using the Shunting Yard algorithm, then evaluating the
postfix expression using stack-based evaluation.

**Table of Contents**

- [Overview](#overview)

- [Features](#features)

- [Algorithm Theory](#algorithm-theory)

  - [Shunting Yard Algorithm](#shunting-yard-algorithm)

  - [Postfix Expression
    Evaluation](#postfix-expression-evaluation)

- [Code Structure](#code-structure)

- [Data Structures](#data-structures)

- [Core Functions](#core-functions)

- [Installation and Usage](#installation-and-usage)

- [Input/Output Format](#inputoutput-format)

- [Examples](#examples)

- [Error Handling](#error-handling)

- [Implementation Details](#implementation-details)

- [Performance Analysis](#performance-analysis)

- [Known Limitations](#known-limitations)

- [Future Enhancements](#future-enhancements)

- [Contributing](#contributing)

- [License](#license)

## Overview

This program implements a **stack-based calculator** that processes
mathematical expressions written in **infix notation** (the standard
mathematical notation humans use) and converts them to **postfix
notation** (Reverse Polish Notation) for efficient evaluation.

The calculator handles:

- Multi-digit integers

- Basic arithmetic operations (+, -, \*, /)

- Parentheses for grouping

- Whitespace in expressions

- File-based input/output processing

- Comprehensive error handling

**Key Components**

1.  **Infix to Postfix Conversion**: Uses the Shunting Yard algorithm

2.  **Postfix Evaluation**: Stack-based expression evaluation

3.  **File I/O**: Processes multiple expressions from input file

4.  **Memory Management**: Dynamic linked list-based stacks

## Features

**✅ Supported Operations**

- **Addition** (`+`): Performs mathematical addition

- **Subtraction** (`-`): Performs mathematical subtraction

- **Multiplication** (`*`): Performs mathematical multiplication

- **Division** (`/`): Performs mathematical division with zero-division
  error handling

**✅ Expression Handling**

- **Multi-digit Numbers**: Supports integers of any length

- **Parentheses**: Proper grouping and precedence handling

- **Whitespace Tolerance**: Ignores spaces between operators and
  operands

- **Operator Precedence**: Follows standard mathematical precedence
  rules

**✅ File Processing**

- **Batch Processing**: Processes multiple expressions from `input.txt`

- **Result Output**: Writes results to `output.txt`

- **Error Reporting**: Clear error messages for invalid expressions

## Algorithm Theory

## Shunting Yard Algorithm

The **Shunting Yard Algorithm**, developed by Edsger Dijkstra in 1961,
converts infix expressions to postfix notation. Named after railroad
shunting yards, it uses a stack to temporarily hold operators while
processing the expression.

**Core Principles:**

1.  **Operands** go directly to output

2.  **Operators** are pushed to stack based on precedence

3.  **Left parentheses** are pushed to stack

4.  **Right parentheses** trigger popping until matching left
    parenthesis

5.  **Higher precedence** operators are processed first

**Precedence Rules:**

- `*` and `/` have precedence 2 (higher)

- `+` and `-` have precedence 1 (lower)

- `(` and `)` have special handling

**Example Conversion:**

`Infix:    3 + 4 * 2``
Process:  3 → output``
          + → stack``
          4 → output  ``
          * → stack (higher precedence)``
          2 → output``
          End: pop *, then +``
``Postfix:  3 4 2 * +``
`

## Postfix Expression Evaluation

Postfix evaluation uses a **operand stack** where:

1.  **Numbers** are pushed onto the stack

2.  **Operators** pop two operands, perform operation, push result back

3.  **Final result** is the single remaining stack element

**Example Evaluation:**

`Postfix:  3 4 2 * +``
Process:  3 → push to stack: [3]``
          4 → push to stack: [3, 4]  ``
          2 → push to stack: [3, 4, 2]``
          * → pop 2,4; calculate 4*2=8; push: [3, 8]``
          + → pop 8,3; calculate 3+8=11; push: [11]``
``Result:   11``
`

## Code Structure

**File Organization**

`calculator.c``
├── Headers and Includes``
├── Constant Definitions  ``
├── Data Structure Definitions``
│   ├── CharNode (operator stack)``
│   └── IntNode (value stack)``
├── Global Variables``
├── Stack Operations``
│   ├──`` Character Stack Functions``
│   └── Integer Stack Functions  ``
├── Helper Functions``
├── Algorithm Implementation``
│   ├── infixToPostfix()``
│   └── evaluatePostfix()``
└── Main Function (File I/O)``
`

## Data Structures

**Stack Node Structures**

**Character Stack Node (Operators)**

`struct CharNode {``
    char data;                    // Stores operator (+, -, *, /, ()``
    struct CharNode *link;        // Points to next node``
};``
`

**Integer Stack Node (Operands)**

`struct IntNode {``
    int data;                     // Stores integer op``erands``
    struct IntNode *link;         // Points to next node``
};``
`

**Stack Implementations**

Both stacks use **singly linked lists** with **LIFO** (Last In, First
Out) access:

- `opStack`: Global pointer to operator stack top

- `valStack`: Global pointer to value stack top

## Core Functions

**Stack Operations**

**Character Stack Functions**

`void pushChar(char c)           // Push operator to stack``
char popChar()                  // Pop and return top operator  ``
char peekChar()                 // Return top operator without removing``
void`` clearCharStack()           // Clear entire operator stack``
`

**Integer Stack Functions**

`void pushInt(int val)           // Push operand to stack``
int popInt()                    // Pop and return top operand``
void clearIntStack()            // Clear entire value`` stack  ``
`

**Algorithm Functions**

**Precedence Function**

`int precedence(char op)``
`

Returns operator precedence:

- `+`, `-`: Returns 1

- `*`, `/`: Returns 2

- Other: Returns 0

**Apply Operation Function**

`int applyOp(int a, int b, char op, int *err)``
`

Performs arithmetic operations:

- Handles all four basic operations

- Sets error flag for division by zero

- Returns operation result

**Infix to Postfix Conversion**

`void infixToPostfix(char *infix, char *postfix)``
`

**Algorithm Steps:**

1.  Skip whitespace characters

2.  For digits: collect complete number, add to postfix with space

3.  For `(`: push to operator stack

4.  For `)`: pop operators until `(`, add to postfix

5.  For operators: pop higher/equal precedence operators, then push
    current

6.  End: pop all remaining operators

**Postfix Evaluation**

`int evaluatePostfix(char *postfix, int *err)``
`

**Algorithm Steps:**

1.  Tokenize postfix string by spaces

2.  For numbers: push to value stack

3.  For operators: pop two values, compute, push result

4.  Return final stack value

## Installation and Usage

**Prerequisites**

- GCC compiler or equivalent C compiler

- Text editor for creating input files

**Compilation**

`gcc -o calculator calculator.c``
`

**File Setup**

1.  Create `input.txt` with mathematical expressions (one per line)

2.  Run the program:

`./calculator``
`

3.  Check results in `output.txt`

## Input File Format (**`input.txt`**)

`12 + 34 * (56 - 7)``
100 / (5 + 5)  ``
3 + 400 * 2 - 10 / 5``
(15 + 25) * 2``
`

## Output File Format (**`output.txt`**)

`1678``
10``
801``
``80``
`

## Examples

**Example 1: Basic Operations**

**Input:** `12 + 34 * 5`

- **Infix to Postfix:** `12 34 5 * +`

- **Evaluation:**

  - Push 12: \[12\]

  - Push 34: \[12, 34\]

  - Push 5: \[12, 34, 5\]

  - Process *: pop 5,34 → 34*5=170, push: \[12, 170\]

  - Process +: pop 170,12 → 12+170=182, push: \[182\]

- **Result:** `182`

**Example 2: Parentheses**

**Input:** `(12 + 3) * 4`

- **Infix to Postfix:** `12 3 + 4 *`

- **Evaluation:**

  - Push 12: \[12\]

  - Push 3: \[12, 3\]

  - Process +: pop 3,12 → 12+3=15, push: \[15\]

  - Push 4: \[15, 4\]

  - Process *: pop 4,15 → 15*4=60, push: \[60\]

- **Result:** `60`

**Example 3: Complex Expression**

**Input:** `100 / (5 + 5) * 3`

- **Infix to Postfix:** `100 5 5 + / 3 *`

- **Evaluation:**

  - Push 100: \[100\]

  - Push 5: \[100, 5\]

  - Push 5: \[100, 5, 5\]

  - Process +: pop 5,5 → 5+5=10, push: \[100, 10\]

  - Process /: pop 10,100 → 100/10=10, push: \[10\]

  - Push 3: \[10, 3\]

  - Process *: pop 3,10 → 10*3=30, push: \[30\]

- **Result:** `30`

## Error Handling

The program includes comprehensive error handling:

**Division by Zero**

`if (b == 0) { ``
    *err = 1; ``
    return 0; ``
}``
`

**Output:** `Error: Invalid expression or division by zero`

**Invalid Expressions**

- Malformed parentheses

- Invalid characters

- Insufficient operands  
  **Output:** `Error: Invalid expression or division by zero`

**File I/O Errors**

`if (!fin || !fout) {``
    printf("File error.\n");``
    return 1;``
``}``
`

**Memory Allocation**

`if(newnode == NULL) {``
    return;``
}``
`

Safe handling of malloc failures.

## Implementation Details

**Memory Management**

- **Dynamic Allocation**: Uses `malloc()` for stack nodes

- **Proper Deallocation**: `free()` called in pop operations

- **Memory Safety**: Null pointer checks prevent crashes

**Stack Reset**

Each expression processing clears both stacks:

`clearCharStack();``
clearIntStack(``);``
`

Prevents interference between expressions.

**String Processing**

- **Whitespace Handling**: `isspace()` check skips spaces

- **Multi-digit Numbers**: Loop collects consecutive digits

- **Token Separation**: Spaces separate tokens in postfix

**Operator Precedence Logic**

`while`` (opStack != NULL && peekChar() != '(' && ``
       precedence(peekChar()) >= precedence(token)) {``
    postfix[j++] = popChar();``
    postfix[j++] = ' ';``
``}``
`

## Performance Analysis

**Time Complexity**

- **Infix to Postfix**: O(n) where n is expression length

- **Postfix Evaluation**: O(n) where n is number of tokens

- **Overall**: O(n) linear time complexity

**Space Complexity**

- **Operator Stack**: O(k) where k is maximum operator nesting

- **Value Stack**: O(n) where n is maximum operand count

- **Output String**: O(n) for postfix representation

**Efficiency Benefits**

1.  **Single Pass**: Each character processed once

2.  **Stack Operations**: O(1) push/pop operations

3.  **No Recursion**: Iterative approach saves stack space

## Known Limitations

**Current Restrictions**

1.  **Integer Only**: No floating-point number support

2.  **Basic Operators**: Only +, -, \*, / supported

3.  **No Unary**: No unary minus or plus operators

4.  **Fixed Buffer**: Maximum expression length of 100 characters

**Edge Cases**

1.  **Empty Input**: May cause undefined behavior

2.  **Very Large Numbers**: Integer overflow possible

3.  **Deeply Nested**: Stack overflow with extreme nesting

## Future Enhancements

**Planned Features**

1.  **Floating Point**: Add double precision support

2.  **Extended Operators**: Power (\^), modulo (%), etc.

3.  **Functions**: Sin, cos, log, sqrt support

4.  **Variables**: Support for variable assignment

5.  **Interactive Mode**: Real-time expression evaluation

**Code Improvements**

1.  **Better Error Messages**: Specific error descriptions

2.  **Input Validation**: Comprehensive syntax checking

3.  **Memory Optimization**: Reduce memory footprint

4.  **Unicode Support**: International number formats

## Contributing

**How to Contribute**

1.  **Fork** the repository

2.  **Create** feature branch (`git checkout -b feature/AmazingFeature`)

3.  **Commit** changes (`git commit -m 'Add some AmazingFeature'`)

4.  **Push** to branch (`git push origin feature/AmazingFeature`)

5.  **Open** Pull Request

**Code Style Guidelines**

- Follow existing indentation (4 spaces)

- Add comments for complex logic

- Include error handling for new functions

- Update documentation for new features

**Testing**

- Test with various expression types

- Verify error handling works correctly

- Check memory leaks with valgrind

- Validate against mathematical calculators

## License

This project is licensed under the MIT License - see the
[LICENSE.md]

**Technical References**

**Algorithm Sources**

- **Shunting Yard Algorithm**: Edsger W. Dijkstra (1961)

- **Stack Data Structure**: Classic computer science concept

- **Postfix Evaluation**: Standard expression evaluation technique

**Implementation Notes**

- **C Standard**: Follows C99 standard conventions

- **Memory Model**: Uses heap allocation for dynamic stacks

- **File I/O**: Standard C library functions (fopen, fgets, fprintf)

**Author:** Argha Ghosh  
**GitHub:** [arg-rgb](https://github.com/arg-rgb)  
**Email:** tojog75@gmail.com
  
**Date Developed**: 20th july to 28th july 2025.

For questions or support, please open an issue in the repository or
contact \[tojog75@gmail.com\].
