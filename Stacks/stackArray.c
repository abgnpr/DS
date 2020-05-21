// STACK: array implementation

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Stack {
    int size;
    int top;
    // Flexible Array Member (must be the last member)
    int arr[];
} Stack;

// returns a pointer to a new stack of size `size`
Stack* createStack(int size)
{
    Stack* S = malloc(sizeof(Stack) + sizeof(int) * size);
    S->size = size;
    S->top = -1;
    return S;
}

// returns TRUE(1) if the stack is empty, otherwise FALSE(0)
int stackEmpty(const Stack* S)
{
    return (S->top == -1) ? TRUE : FALSE;
}

// Adds an element to the top of stack S
void push(Stack* S, int data)
{
    if (S->top == S->size - 1)
        printf("\033[31mOverflow\033[0m");
    else
        S->arr[++S->top] = data;
}

// Removes an elemet from the top of stack S and prints it
void pop(Stack* S)
{
    if (S->top == -1)
        printf("\033[31mUnderflow\033[0m");
    else
        printf("\nPopped: %d\n", S->arr[S->top--]);
}

// Prints the value of the topmost element
void peek(Stack* S)
{
    printf("\n\t");
    if (!stackEmpty(S))
        printf("Top = %d", S->arr[S->top]);
    else
        printf("Stack Empty");
    printf("\n");
}

// prints the stack S
void print(const Stack* S)
{
    printf("\n\t");
    if (stackEmpty(S))
        printf("Stack empty");
    else {
        for (int i = 0; i <= S->top; ++i)
            printf("| %d ", S->arr[i]);
        printf("\033[33m}=top\033[0m");
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
    int size;
    printf("\nStack size: ");
    scanf("%d", &size);

    // instructions
    printf("\nInput gets pushed, enter p to pop, pk to peek & q to quit\n");

    struct Stack* stk = createStack(size);

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
                pop(stk);
                print(stk);

            // `pk` to peek
            } else if (strcmp(input, "pk") == 0) {
                peek(stk);

            } else { // otherwise, integer input get pushed
                // covert string input to integer
                int data = strtoimax(input, NULL, 10);
                // strtoimax() returns 0 for junk values
                // so, 0 should be pushed only if input
                // is actually 0
                if (data != 0 || strcmp(input, "0") == 0) {
                    push(stk, data);
                    print(stk);
                }
            }

        } else
            printf("Max input size exceeded\n");
    }

    printf("\n");
    return 0;
}
