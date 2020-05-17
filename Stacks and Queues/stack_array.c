#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct Stack {
    int top;
    int size;
    // Flexible Array Member (must be the last member)
    int arr[];
};

struct Stack*
createStack(int size)
{
    struct Stack* S;
    S = malloc(sizeof(*S) + sizeof(int) * size);
    S->top = 0;
    S->size = size;
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
    if (S->top == S->size) {
        printf("\033[31mOverflow\033[0m");
        return;
    }
    S->arr[S->top++] = data;
}

void pop(struct Stack* S)
{
    if (S->top == 0) {
        printf("\033[31mUnderflow\033[0m");
        return;
    }
    S->top -= 1;
    printf("\nPopped: %d", S->arr[S->top]);
}

void print(const struct Stack* S)
{
    for (int i = 0; i < S->top; ++i) {
        printf("| %d ", S->arr[i]);
    }
    printf("\033[33m}=top\033[0m\n");
}

int main(void)
{
    system("clear");

    int size;
    printf("\nStack size: ");
    scanf("%d", &size);

    // instructions
    printf("\nInput gets pushed, enter p to pop, q to quit\n");

    struct Stack* stk = createStack(size);

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

            printf("\n\t");
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