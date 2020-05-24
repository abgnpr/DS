// INFIX to POSTFIX
// sample test case :  a - ( b / c + (d % e * f) / g) * h

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// character stack
#define MAX 101
char stk[MAX];
int top = -1;
void push(char c) { stk[++top] = c; }
char pop() { return stk[top--]; }
char peek() { return stk[top]; }
int stkEmpty() { return top == -1 ? 1 : 0; }

// appends char c to string S and
// returns the new length of S
int append(char* S, char c)
{
    int len = strlen(S);
    S[len] = S[len - 1];
    S[len - 1] = c;
    S[++len] = '\0';
    return len;
}

// returns true if c is an operator (*, /, %, +, or -)
int isOperator(char c) {
    switch (c) {
        case '*': case '/' : case '%': case '+': case '-': return 1;
        default: return 0;
    }
}

// returns precedence of operator O
int precedence (char O) {
    switch (O) {
        case '*': case '/' : case '%': return 2; // higher
        case '+': case '-': return 1; // lower
    }
}

// converts an infix expression into a postfix expression
// note: contains no expression validity checks
void infixToPostfix (char infix[MAX], char postfix[MAX])
{
    push('(');
    int len = append(infix, ')');

    int p = 0; // counter for `postfix`
    char c;

    for (int i = 0; i < len; ++i) {
        
        c = infix[i];

        if (c == '(') push('(');

        else if (isalnum(c)) postfix[p++] = c;

        else if (c == ')') {
            while (peek() != '(') postfix[p++] = pop();
            pop(); // '('
        }

        else if (isOperator(c)) {
            while (peek() != '(' && precedence(peek()) > precedence(c))
                postfix[p++] = pop();
            push(c);
        }
    }

    while (!stkEmpty())
        postfix[p++] = pop();

    postfix[p++] = '\n';
    postfix[p] = '\0';
}

// driver
void main()
{
    char I[MAX], P[MAX];
    
    printf("Input infix: ");
    fgets(I, MAX, stdin);

    infixToPostfix(I, P);
    printf("Postfix: %s", P);
}
