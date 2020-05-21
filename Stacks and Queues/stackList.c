#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Element {
    int data;
    struct Element* next;
} Element;

// creates a new element with `data` & returns a pointer to it
Element* newElement(int data)
{
    Element* e = (Element*)malloc(sizeof(Element));
    e->data = data;
    return e;
}

typedef struct Stack {
    Element* HEAD;
} Stack;

// returns a pointer to a new stack
Stack* createStack()
{
    Stack* S = (Stack*)malloc(sizeof(Stack));
    S->HEAD = NULL;
    return S;
}

// returns TRUE(1) if the stack is empty, otherwise FALSE(0)
int stackEmpty(Stack* S)
{
    return (S->HEAD == NULL) ? TRUE : FALSE;
}

// Adds an element to the top of stack S
void push(Stack* S, Element* e)
{
    e->next = S->HEAD;
    S->HEAD = e;
}

// Removes an element from the top of stack S 
// and returns a pointer to it
Element* pop(Stack* S)
{
    if (stackEmpty(S)) {
        printf("\n\033[31mUnderflow\033[0m\n");
        return NULL;

    } else {
        Element* popped = S->HEAD;
        S->HEAD = S->HEAD->next;
        return popped;
    }
}

// Returns a pointer to the topmost element
Element* peek(Stack* S)
{
    return S->HEAD;
}

// Prints the stack S
void print(Stack* S)
{
    printf("\n\t");
    if (!stackEmpty(S)) {
        Element* ele = S->HEAD;
        printf("\033[33mtop={\033[0m");
        while (ele != NULL) {
            printf(" %d |", ele->data);
            ele = ele->next;
        }
    } else {
        printf("Stack Empty");
    }
    printf("\n");
}

// returs the maximum of digits that `int` can hold
int maxIntDigits()
{
    int digits = 0;
    int maxInt = INT32_MAX;
    while ((maxInt /= 10) > 0)
        digits++;
    return digits;
}

// driver
int main(void)
{
    // instructions
    printf("\nInput gets pushed, enter p to pop, pk to peek & q to quit\n");

    struct Stack* stk = createStack();

    int maxInputSize = maxIntDigits();
    char input[maxInputSize + 1 /*for null*/];

    int done = FALSE;
    while (!done) {

        printf("\nstack> ");
        scanf("%s", input);

        // `q` to quit
        if (strcmp(input, "q") == 0) {
            done = TRUE; // exit

        } else if (strlen(input) <= maxInputSize) {

            // `p` to pop
            if (strcmp(input, "p") == 0) {
                Element* e = pop(stk);
                if (e) {
                    printf("\nPopped = %d\n", e->data);
                    free(e);
                }
                print(stk);

                // `pk` to peek
            } else if (strcmp(input, "pk") == 0) {
                Element* e = peek(stk);
                if (e)
                    printf("\nTop = %d\n", e->data);
                else
                    printf("\n\tStack empty\n");

            } else {
                // otherwise, integer input get pushed
                // covert string input to integer
                int data = strtoimax(input, NULL, 10);
                // strtoimax() returns 0 for junk values
                // so, 0 should be pushed only if input
                // is actually 0
                if (data != 0 || strcmp(input, "0") == 0) {
                    push(stk, newElement(data));
                    print(stk);
                }
            }

        } else
            printf("Max input size exceeded\n");
    }

    printf("\n");
    return EXIT_SUCCESS;
}
