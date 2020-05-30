// QUEUE : array implementation

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Queue {
    int head, tail;
    int size;
    // Flexible Array Member (must be the last member)
    int arr[];
} Queue;

Queue* createQueue(int size)
{
    Queue* Q = malloc(sizeof(Queue) + sizeof(int) * size);
    Q->head = Q->tail = 0;
    Q->size = size;
    return Q;
}

int queueEmpty(Queue* Q)
{
    if (Q->head == Q->tail)
        return TRUE;
    return FALSE;
}

void moveForward(Queue* Q)
{
    for (int i = Q->head; i < Q->tail; ++i)
        Q->arr[i] = Q->arr[i + 1];
    Q->tail--;
}

void enqueue(Queue* Q, int data)
{
    if (Q->tail < Q->size)
        Q->arr[Q->tail++] = data;
    else
        printf("\033[31mOverflow\033[0m");
}

void dequeue(Queue* Q)
{
    if (Q->head < Q->tail) {
        int dequeued = Q->arr[Q->head];
        moveForward(Q);
        printf("Dequeued: %d", dequeued);
    } else
        printf("\033[31mUnderflow\033[0m");
}

void print(Queue* Q)
{
    printf("\n\033[33mhead{\033[0m");
    for (int i = Q->head; i < Q->tail; ++i) {
        if (i != Q->head)
            printf("|");
        printf(" %d ", Q->arr[i]);
    }
    printf("\033[33m}tail\033[0m\n");
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
int main(void)
{
    int size;
    printf("\nQueue size: ");
    scanf("%d", &size);

    // instructions
    printf("\nInput gets enqueued, enter d to dequeue, q to quit\n");

    Queue* q = createQueue(size);

    int maxInputSize = maxIntDigits();
    char input[maxInputSize + 1 /*for null*/];

    int done = FALSE;
    while (!done) {

        printf("\nQueue> ");
        scanf("%s", input);

        // `q` to quit
        if (strcmp(input, "q") == 0) {
            done = TRUE; // exit

        } else if (strlen(input) <= maxInputSize) {

            // `d` to deque
            if (strcmp(input, "d") == 0)
                dequeue(q);

            else {  // otherwise, enqueue the integer input
                
                // covert string input to integer
                int data = strtoimax(input, NULL, 10);
                
                // strtoimax() returns 0 for junk values
                // so, 0 should be pushed only if input
                // is actually 0
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