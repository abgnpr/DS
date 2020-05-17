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

struct Queue {
    struct Element *HEAD, *TAIL;
};

struct Queue*
createStack()
{
    struct Queue* Q;
    Q = (struct Queue*)malloc(sizeof(struct Queue));
    return Q;
}

int maxIntDigits()
{
    int digits = 0;
    int maxInt = INT32_MAX;
    while ((maxInt /= 10) > 0)
        digits++;
    return digits;
}

int queueEmpty(const struct Queue* Q)
{
    if (!Q->HEAD)
        return TRUE;
    return FALSE;
}

void enqueue(struct Queue* Q, int data)
{
    struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
    newElement->data = data;
    newElement->nextElement = NULL;
    if (!Q->HEAD) {
        Q->HEAD = newElement;
    } else {
        Q->TAIL->nextElement = newElement;
    }
    Q->TAIL = newElement;
}

void dequeue(struct Queue* Q)
{
    if (!Q->HEAD) {
        printf("\033[31mUnderflow\033[0m");
        return;
    }
    struct Element* dequeuedElement = Q->HEAD;
    Q->HEAD = Q->HEAD->nextElement;
    printf("\nDequeued: %d\n", dequeuedElement->data);
    free(dequeuedElement);
}

void print(const struct Queue* Q)
{
    printf("\n\033[33mhead{\033[0m");
    struct Element* ele = Q->HEAD;
    while (ele != NULL) {
        if (ele != Q->HEAD)
            printf("|");
        printf(" %d ", ele->data);
        ele = ele->nextElement;
    }
    printf("\033[33m}tail\033[0m\n");
}

int main(void)
{
    // instructions
    system("clear");
    printf("\nInput gets enqueued, enter d to dequeue, q to quit\n");

    struct Queue* q = createStack();

    int maxInputSize = maxIntDigits();
    char input[maxInputSize + 1 /*for null*/];

    int done = FALSE;
    while (!done) {

        printf("\nQueue> ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0) {
            done = TRUE; // exit

        } else if (strlen(input) <= maxInputSize) {

            if (strcmp(input, "d") == 0)
                dequeue(q);

            else {
                int data = strtoimax(input, NULL, 10);
                if (data != 0 || strncmp(input, "0", 1) == 0)
                    enqueue(q, data);
            }

            queueEmpty(q) ? printf("\n(empty)\n") : print(q);

        } else
            printf("Max input size exceeded\n");
    }

    printf("\n");
    return 0;
}