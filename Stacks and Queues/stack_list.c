#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct Element {
    int data;
    struct Element* nextElement;
};

struct Stack {
    int top;
    struct Element* HEAD;
};

struct Stack*
createStack()
{
    struct Stack* S;
    S = (struct Stack*)malloc(sizeof(struct Stack));
    S->top = 0;
    return S;
}

int maxIntDigits()
{
    int digits = 0;
    int maxInt = INT32_MAX;
    while ((maxInt /= 10) > 0)
        digits++;
    return digits;
}

int stackEmpty(const struct Stack* S)
{
    if (S->top == 0)
        return TRUE;
    return FALSE;
}

void push(struct Stack* S, int data)
{
    struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
    if (S->top == 0)
        newElement->nextElement = NULL;
    else
        newElement->nextElement = S->HEAD;
    newElement->data = data;
    S->HEAD = newElement;
    S->top += 1;
}

void pop(struct Stack* S)
{
    if (S->top == 0) {
        printf("\033[31mUnderflow\033[0m");
        return;
    }
    struct Element* poppedElement = S->HEAD;
    S->HEAD = S->HEAD->nextElement;
    printf("\nPopped: %d\n", poppedElement->data);
    free(poppedElement);
    S->top -= 1;
}

void print(const struct Stack* S)
{
    printf("\033[33mtop={\033[0m");
    struct Element* ele = S->HEAD;
    while (ele != NULL) {
        printf(" %d |", ele->data);
        ele = ele->nextElement;
    }
    printf("\n");
}

int main(void)
{
    // instructions
    system("clear");
    printf("\nInput gets pushed, enter p to pop, q to quit\n");

    struct Stack* stk = createStack();

    int maxInputSize = maxIntDigits();
    char input[maxInputSize + 1 /*for null*/];

    int done = FALSE;
    while (!done) {

        printf("\nstack> ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0) {
            done = TRUE; // exit

        } else if (strlen(input) <= maxInputSize) {

            if (strcmp(input, "p") == 0) {
                pop(stk);

            } else {
                int data = strtoimax(input, NULL, 10);
                // strtoimax() returns 0 for junk values
                // so, 0 is pushed only if input is 0
                if (data != 0 || strcmp(input, "0") == 0)
                    push(stk, data);
            }

            printf("\n ");
            if (stackEmpty(stk))
                printf("(empty)\n");
            else
                print(stk);
        } else
            printf("Max input size exceeded\n");
    }
    printf("\n");
    return 0;
}