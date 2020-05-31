// CIRCULAR QUEUE

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

int size(Queue* Q)
{
    if (Q->tail == -1 && Q->head == 0)
        return 0;

    int diff = Q->tail - Q->head + 1;
    return (Q->tail >= Q->head) ? diff : Q->max + diff;
}

int queueEmpty(Queue* Q) { return (size(Q) == 0) ? TRUE : FALSE; }

int queueFull(Queue* Q) { return (size(Q) == Q->max) ? TRUE : FALSE; }

void enqueue(Queue* Q, int data)
{
    if (queueFull(Q))
        printf("\033[31mOverflow\033[0m");

    else {
        if (Q->tail == Q->max - 1)
            Q->tail = 0;
        else
            Q->tail += 1;

        Q->arr[++Q->tail] = data;
    }
}

void dequeue(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\033[31mUnderflow\033[0m");

    else {
        // print instead of return
        printf("\nDequeued: %d\n", Q->arr[Q->head]);

        if (Q->head == Q->tail) {
            Q->head = 0;
            Q->tail = -1;

        } else if (Q->head == Q->max - 1)
            Q->head = 0;

        else
            Q->head += 1;
    }
}

void peekFront(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");
    else
        // print instead of return
        printf("\nFront(HEAD): %d\n", Q->arr[Q->head]);
}

void peekBack(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");
    else
        // print instead of return
        printf("\nBack(TAIL): %d\n", Q->arr[Q->tail]);
}

void print(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue empty\n");

    else {
        printf("\n\033[33m  head{\033[0m");

        for (int n = 1, i = Q->head; n <= size(Q); ++n) {
            if (i != Q->head)
                printf("|");
            printf(" %d ", Q->arr[i]);

            i = (i == Q->max - 1) ? 0 : ++i;
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
