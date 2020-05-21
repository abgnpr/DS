#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int maxIntDigits()
{
    int nDigits = 0;
    int maxInt = INT32_MAX;
    while ((maxInt /= 10) > 0)
        nDigits++;
    return nDigits;
}

struct Queue {
    int head, tail;
    int size;
    // Flexible Array Member (must be the last member)
    int arr[];
};

struct Queue*
createQueue(int size)
{
    struct Queue* Q;
    Q = malloc(sizeof(*Q) + sizeof(int) * size);
    Q->head = Q->tail = 0;
    Q->size = size;
    return Q;
}

int queueEmpty(const struct Queue* Q)
{
    if (Q->head == Q->tail)
        return TRUE;
    return FALSE;
}

void moveForward(struct Queue* Q)
{
    for (int i = Q->head; i < Q->tail; ++i)
        Q->arr[i] = Q->arr[i + 1];
    Q->tail--;
}

void enqueue(struct Queue* Q, int data)
{
    if (Q->tail < Q->size)
        Q->arr[Q->tail++] = data;
    else
        printf("\033[31mOverflow\033[0m");
}

void dequeue(struct Queue* Q)
{
    if (Q->head < Q->tail) {
        int dequeued = Q->arr[Q->head];
        moveForward(Q);
        printf("Dequeued: %d", dequeued);
    } else
        printf("\033[31mUnderflow\033[0m");
}

void print(const struct Queue* Q)
{
    printf("\n\033[33mhead{\033[0m");
    for (int i = Q->head; i < Q->tail; ++i) {
        if (i != Q->head)
            printf("|");
        printf(" %d ", Q->arr[i]);
    }
    printf("\033[33m}tail\033[0m\n");
}

int main(void)
{
    system("clear");

    int size;
    printf("\nQueue size: ");
    scanf("%d", &size);

    // instructions
    printf("\nInput gets enqueued, enter d to dequeue, q to quit\n");

    struct Queue* q = createQueue(size);

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