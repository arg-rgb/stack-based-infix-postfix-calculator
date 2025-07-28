// Calculator using STACK DATA_STRUCTURE with infix to postfix then postfix evaluation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack node for characters (operators)
struct CNode {
    char data;
    struct CNode *link;
};

// Stack node for integers (evaluation)
struct IntNode {
    int data;
    struct IntNode *link;
};

struct CNode *opStack = NULL;
struct IntNode *valStack = NULL;

// ---------- Stack Functions ----------
void pushChar(char c) {
    struct CNode *newnode = (struct CNode*)malloc(sizeof(struct CNode));
    if(newnode == NULL){
        return;
    }
    newnode->data = c;
    newnode->link = opStack;
    opStack = newnode;
}

char popChar() {
    if (opStack == NULL) 
        return '\0';
    struct CNode *temp = opStack;
    char val = temp->data;
    opStack = opStack->link;
    free(temp);
    return val;
}

char peekChar() {
    return (opStack != NULL) ? opStack->data : '\0';
}

void pushInt(int val) {
    struct IntNode *newnode = (struct IntNode*)malloc(sizeof(struct IntNode));
    newnode->data = val;
    newnode->link = valStack;
    valStack = newnode;
}

int popInt() {
    if (valStack == NULL) return 0;
    struct IntNode *temp = valStack;
    int val = temp->data;
    valStack = valStack->link;
    free(temp);
    return val;
}

// ---------- Helper Functions ----------
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op, int *err) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) { *err = 1; return 0; }
            return a / b;
        default: return 0;
    }
}

void clearCharStack() {
    while (opStack != NULL) popChar();
}

void clearIntStack() {
    while (valStack != NULL) popInt();
}

// Convert infix to postfix with spaces separating tokens, ignore spaces in input
void infixToPostfix(char *infix, char *postfix) {
    int i = 0, j = 0;
    char token;

    while ((token = infix[i]) != '\0') {
        if (isspace(token)) {
            // Skip any whitespace in input
            i++;
            continue;
        }
        if (isdigit(token)) {
            // Append entire number to postfix with a trailing space
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
        } else if (token == '(') {
            pushChar(token);
            i++;
        } else if (token == ')') {
            while (peekChar() != '(' && peekChar() != '\0') {
                postfix[j++] = popChar();
                postfix[j++] = ' ';
            }
            popChar(); // Remove '('
            i++;
        } else if (strchr("+-*/", token)) {
            while (opStack != NULL && peekChar() != '(' && precedence(peekChar()) >= precedence(token)) {
                postfix[j++] = popChar();
                postfix[j++] = ' ';
            }
            pushChar(token);
            i++;
        } else {
            // Invalid characters ignored or can be handled as error
            i++;
        }
    }
    // Pop remaining operators
    while (peekChar() != '\0') {
        postfix[j++] = popChar();
        postfix[j++] = ' ';
    }
    if (j > 0 && postfix[j-1] == ' ') j--; // Remove trailing space
    postfix[j] = '\0';
}

// Evaluate postfix expression separated by spaces
int evaluatePostfix(char *postfix, int *err) {
    char *token = strtok(postfix, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            int val = atoi(token);
            pushInt(val);
        } else if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            int b = popInt();
            int a = popInt();
            int result = applyOp(a, b, token[0], err);
            if (*err) return 0;
            pushInt(result);
        } else {
            *err = 1;
            return 0;
        }
        token = strtok(NULL, " ");
    }
    return popInt();
}

// ---------- Main File I/O Logic ----------
int main() {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    if (!fin || !fout) {
        printf("File error.\n");
        return 1;
    }

    char line[MAX];
    while (fgets(line, sizeof(line), fin)) {
        clearCharStack();
        clearIntStack();

        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

        char postfix[3*MAX] = "";
        int error = 0;

        infixToPostfix(line, postfix);

        char postfixCopy[3*MAX];
        strcpy(postfixCopy, postfix);

        int result = evaluatePostfix(postfixCopy, &error);

        if (error) {
            fprintf(fout, "Error: Invalid expression or division by zero\n");
        } else {
            fprintf(fout, "%d\n", result);
        }
    }

    fclose(fin);
    fclose(fout);
    printf("Calculation complete. Check output.txt\n");
    return 0;
}
