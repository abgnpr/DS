// QUEUE : array implementation

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Queue {
    int head, tail;
    int max;
    // Flexible Array Member (must be the last member)
    int arr[];
} Queue;

Queue* createQueue(int max)
{
    Queue* Q = malloc(sizeof(Queue) + sizeof(int) * max);
    Q->head = 0;
    Q->tail = -1;
    Q->max = max;
    return Q;
}

int size(Queue* Q) { return Q->tail - Q->head + 1; }

int queueEmpty(Queue* Q) { return (size(Q) == 0) ? TRUE : FALSE; }

int queueFull(Queue* Q) { return (size(Q) == Q->max) ? TRUE : FALSE; }

void rebase(Queue* Q)
{
    if (queueEmpty(Q)) {
        Q->head = 0;
        Q->tail = -1;
    }

    else {
        int i = 0, k = Q->head;
        while (k <= Q->tail)
            Q->arr[i++] = Q->arr[k++];

        Q->head = 0;
        Q->tail = i - 1;
    }
}

void enqueue(Queue* Q, int data)
{
    if (queueFull(Q))
        printf("\033[31mOverflow\033[0m");

    else {
        if (Q->tail == Q->max - 1)
            rebase(Q);

        Q->arr[++Q->tail] = data;
    }
}

void dequeue(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\033[31mUnderflow\033[0m");
    else
        // printed instead of returned
        printf("\nDequeued: %d\n", Q->arr[Q->head++]);
}

void peekFront(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");
    else
        // printed instead of returned
        printf("\nFront(HEAD): %d\n", Q->arr[Q->head]);
}

void peekBack(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");
    else
        // printed instead of returned
        printf("\nBack(TAIL): %d\n", Q->arr[Q->tail]);
}

void print(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue empty\n");

    else {
        printf("\n\033[33mhead{\033[0m");
        for (int i = Q->head; i <= Q->tail; ++i) {
            if (i != Q->head)
                printf("|");
            printf(" %d ", Q->arr[i]);
        }
        printf("\033[33m}tail\033[0m\n");
    }
}

int maxIntDigits()
{
    int nDigits = 0;
    int maxInt = INT32_MAX;
    while ((maxInt /= 10) > 0)
        nDigits++;
    return nDigits;
}

// driver
void main(void)
{
    int size;
    printf("\nQueue size: ");
    scanf("%d", &size);

    // instructions
    printf("\nInput gets enqueued, enter d to dequeue, pf to peek front, pb to peek back q to quit\n");

    Queue* q = createQueue(size);

    int maxInputSize = maxIntDigits();
    char input[maxInputSize + 1 /*for null*/];

    int done = FALSE;
    while (!done) {

        printf("\nQueue> ");
        scanf("%s", input);

        if (strlen(input) <= maxInputSize) {

            // `q` to quit
            if (strcmp(input, "q") == 0)
                done = TRUE; // exit

            // `pf` to peek front (HEAD)
            else if (strcmp(input, "pf") == 0)
                peekFront(q);

            // `pb` to peek back (TAIL)
            else if (strcmp(input, "pb") == 0)
                peekBack(q);

            // `d` to deque
            else if (strcmp(input, "d") == 0) {
                dequeue(q);
                print(q);

            } else { // otherwise, enqueue the integer input

                // covert string input to integer
                int data = strtoimax(input, NULL, 10);

                // strtoimax() returns 0 for junk values
                // so, 0 should be pushed only if input
                // is actually 0
                if (data != 0 || strncmp(input, "0", 1) == 0) {
                    enqueue(q, data);
                    print(q);
                }
            }

        } else
            printf("Max input size exceeded\n");
    }

    printf("\n");
}
