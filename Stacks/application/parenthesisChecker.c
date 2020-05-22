// Parenthesis Checker

#include <stdio.h>
#include <string.h>

#define MAX 1024

char stk[MAX];
int top = -1;

int stackEmpty()
{
    return top == -1 ? 1 : 0;
}

void push(char c)
{
    if (top == MAX - 1)
        printf("Overflow\n");
    else
        stk[++top] = c;
}

char pop()
{
    if (stackEmpty())
        printf("Underflow\n");
    else
        return stk[top--];
}

char peek()
{
    if (stackEmpty())
        printf("nil\n");
    else
        return stk[top];
}

void main(void)
{
    printf("Input expression: ");
    char exp[MAX + 2], ch;
    fgets(exp, MAX + 2, stdin);

    int i, len = strlen(exp) - 1 /* exclude \n */;
    for (i = 0; i < len; ++i) {

        ch = exp[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch);
        }

        if (ch == ')' || ch == '}' || ch == ']') {
            if (stackEmpty())
                break;
            if ((peek() == '(' && ch == ')')
            ||  (peek() == '{' && ch == '}')
            ||  (peek() == '[' && ch == ']'))
                pop();
        }
    }

    if (stackEmpty() && i == len)
        printf("Valid\n");
    else
        printf("Invalid\n");
}
