// PRIORITY QUEUE

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct PriorityQueue {
    int max, // maximum queue size per priority
        *head, // array of heads
        *tail, // array of tails
        **arr; // 2D array for holding queue elements
} PriorityQueue;

// creates a new priority queue which has
// 5 queues of 5 different priorities
// 0:max, 1:high, 2:normal, 3:low, 4:min
// Each queue can store `max` elements.
// The priority queue can store a total
// of (max X 5) elements
PriorityQueue* createQueue(int max)
{
    PriorityQueue* Q = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    Q->max = max;

    // dynamically allocate and initialize the arrays

    Q->head = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; ++i)
        Q->head[i] = 0; // all heads init. to 0

    Q->tail = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; ++i)
        Q->tail[i] = -1; // all tails init. to -1

    Q->arr = (int**)malloc(sizeof(int*) * 5);
    for (int i = 0; i < 5; ++i)
        Q->arr[i] = (int*)malloc(sizeof(int) * max);

    return Q;
}

// returns the size of the queue
int size(PriorityQueue* Q, int p)
{
    if (Q->tail[p] == -1 && Q->head[p] == 0)
        return 0;

    int diff = Q->tail[p] - Q->head[p] + 1;
    return (Q->tail[p] >= Q->head[p]) ? diff : Q->max + diff;
}

// returns true if the queue is empty
int queueEmpty(PriorityQueue* Q, int p) { return (size(Q, p) == 0) ? TRUE : FALSE; }

// returns true if the queue is full
int queueFull(PriorityQueue* Q, int p) { return (size(Q, p) == Q->max) ? TRUE : FALSE; }

// adds a data element to the queue end
void enqueue(PriorityQueue* Q, int data, int p)
{
    if (queueFull(Q, p))
        printf("\n\033[31mOverflow\033[0m\n");

    else {
        // circular increment of the tail of the queue with priority p
        Q->tail[p] = (Q->tail[p] + 1) % Q->max;

        // put the new data at the tail of the queue with priority p
        Q->arr[p][Q->tail[p]] = data;
    }
}

// removes a data element from the queue front
void dequeue(PriorityQueue* Q)
{
    for (int p = 0; p < 5; ++p) {
        if (!queueEmpty(Q, p)) {

            // print de-queued
            printf("\nDequeued: %d\n", Q->arr[p][Q->head[p]]);

            // coincidence of head and tail implies
            // that the queue has become empty, so
            // we reset both of them
            if (Q->head[p] == Q->tail[p]) {
                Q->head[p] = 0;
                Q->tail[p] = -1;

            } else
                // circular increment of the head of the queue with priority p
                Q->head[p] = (Q->head[p] + 1) % Q->max;

            return;
        }
    }

    printf("\n\033[31mUnderflow\033[0m\n");
}

// shows the element at the queue front
void peekFront(PriorityQueue* Q)
{
    for (int p = 0; p < 5; ++p) {
        if (!queueEmpty(Q, p)) {
            printf("\nFront(HEAD): %d\n", Q->arr[p][Q->head[p]]);
            return;
        }
    }

    printf("\nQueue Empty\n");
}

// shows the element at the queue end
void peekBack(PriorityQueue* Q)
{
    for (int p = 4; p >= 0; --p) {
        if (!queueEmpty(Q, p)) {
            printf("\nBack(TAIL): %d\n", Q->arr[p][Q->tail[p]]);
            return;
        }
    }

    printf("\nQueue Empty\n");
}

// prints the queue
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
                peekFront(q);

            // `pb` to view back (TAIL)
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
