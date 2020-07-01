// PRIORITY QUEUE : array implementation

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct PriorityQueue {
    int max;
    int *head, *tail, **arr;
} PriorityQueue;

PriorityQueue* createQueue(int max)
{
    PriorityQueue* Q = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    Q->max = max;

    // dynamically allocated

    Q->head = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; ++i)
        Q->head[i] = 0;

    Q->tail = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; ++i)
        Q->tail[i] = -1;

    Q->arr = (int**)malloc(sizeof(int*) * 5);
    for (int i = 0; i < 5; ++i)
        Q->arr[i] = (int*)malloc(sizeof(int) * max);

    return Q;
}

int size(PriorityQueue* Q, int p)
{
    if (Q->tail[p] == -1 && Q->head[p] == 0)
        return 0;

    int diff = Q->tail[p] - Q->head[p] + 1;
    return (Q->tail[p] >= Q->head[p]) ? diff : Q->max + diff;
}

int queueEmpty(PriorityQueue* Q, int p) { return (size(Q, p) == 0) ? TRUE : FALSE; }

int queueFull(PriorityQueue* Q, int p) { return (size(Q, p) == Q->max) ? TRUE : FALSE; }

void enqueue(PriorityQueue* Q, int data, int p)
{
    if (queueFull(Q, p))
        printf("\n\033[31mOverflow\033[0m\n");

    else {
        if (Q->tail[p] == Q->max - 1)
            Q->tail[p] = 0;
        else
            Q->tail[p] += 1;

        Q->arr[p][Q->tail[p]] = data;
    }
}

void dequeue(PriorityQueue* Q)
{
    for (int p = 0; p < 5; ++p) {
        if (!queueEmpty(Q, p)) {
            // print instead of return
            printf("\nDequeued: %d\n", Q->arr[p][Q->head[p]]);

            if (Q->head[p] == Q->tail[p]) {
                Q->head[p] = 0;
                Q->tail[p] = -1;

            } else if (Q->head[p] == Q->max - 1)
                Q->head[p] = 0;

            else
                Q->head[p] += 1;

            return;
        }
    }

    printf("\n\033[31mUnderflow\033[0m\n");
}

void front(PriorityQueue* Q)
{
    for (int p = 0; p < 5; ++p) {
        if (!queueEmpty(Q, p)) {
            // print instead of return
            printf("\nFront(HEAD): %d\n", Q->arr[p][Q->head[p]]);
            return;
        }
    }

    printf("\nQueue Empty\n");
}

// incomplete
void back(PriorityQueue* Q) { }

void print(PriorityQueue* Q)
{
    int empty = TRUE;

    printf("\n");
    for (int p = 0; p < 5; ++p) {
        if (!queueEmpty(Q, p)) {
            printf(" [%d]: ", p);
            empty = FALSE;
            for (int n = 1, i = Q->head[p]; n <= size(Q, p); ++n, i = (i == Q->max - 1) ? 0 : ++i)
                printf("| %d ", Q->arr[p][i]);
            printf("|\n");
        }
    }

    if (empty)
        printf("Queue Empty\n");
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
    printf("\nMax Queue size per priority?: ");
    scanf("%d", &size);

    // instructions
    printf("\nInput gets enqueued\nd  - dequeue\npf - peek front\npb - peek back,\nq  - quit\n");

    PriorityQueue* q = createQueue(size);

    int maxInputSize = maxIntDigits();
    char input[maxInputSize + 1 /*for null*/];

    int done = FALSE;
    while (!done) {

        printf("\n\nQueue> ");
        scanf("%s", input);

        if (strlen(input) <= maxInputSize) {

            // `q` to quit
            if (strcmp(input, "q") == 0)
                done = TRUE; // exit

            // `pf` to view front (HEAD)
            else if (strcmp(input, "pf") == 0)
                front(q);

            // `pb` to view back (TAIL)
            else if (strcmp(input, "pb") == 0)
                back(q);

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

                    int p;
                    printf("       ^__priority(0-4): ");
                    scanf("%d", &p);

                    if (p >= 0 && p <= 4) {
                        enqueue(q, data, p);
                        print(q);

                    } else
                        printf("       Invalid priority! (MAXIMUM: 0, MINIMUM: 4)\n");
                }
            }

        } else
            printf("Max input size exceeded\n");
    }

    printf("\n");
}
