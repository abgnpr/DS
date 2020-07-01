// DEQUE (DOUBLE ENDED QUEUE)

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Queue {
    int left, right;
    int max;
    // Flexible Array Member (must be the last member)
    int arr[];
} Queue;

Queue* createQueue(int max)
{
    Queue* Q = malloc(sizeof(Queue) + sizeof(int) * max);
    Q->left = 0;
    Q->right = -1;
    Q->max = max;
    return Q;
}

int size(Queue* Q)
{
    if (Q->right == -1 && Q->left == 0)
        return 0;

    int diff = Q->right - Q->left + 1;
    return (Q->right >= Q->left) ? diff : Q->max + diff;
}

int queueEmpty(Queue* Q) { return (size(Q) == 0) ? TRUE : FALSE; }

int queueFull(Queue* Q) { return (size(Q) == Q->max) ? TRUE : FALSE; }

void enqueueRight(Queue* Q, int data)
{
    if (queueFull(Q))
        printf("\033[31mOverflow\033[0m");

    else {
        if (Q->right == Q->max - 1)
            Q->right = 0;
        else
            Q->right += 1;

        Q->arr[Q->right] = data;
    }
}

void dequeueLeft(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\033[31mUnderflow\033[0m");

    else {
        // print instead of return
        printf("\nDequeued: %d\n", Q->arr[Q->left]);
        Q->arr[Q->left] = 0;

        if (Q->left == Q->right) {
            Q->left = 0;
            Q->right = -1;

        } else if (Q->left == Q->max - 1)
            Q->left = 0;

        else
            Q->left += 1;
    }
}

void enqueueLeft(Queue* Q, int data)
{
    if (queueFull(Q))
        printf("\033[31mOverflow\033[0m");

    else {
        if (Q->left == 0)
            Q->left = Q->max - 1;
        else
            Q->left -= 1;

        Q->arr[Q->left] = data;
    }
}

void dequeueRight(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\033[31mUnderflow\033[0m");

    else {
        // print instead of return
        printf("\nDequeued: %d\n", Q->arr[Q->right]);
        Q->arr[Q->right] = 0;

        if (Q->left == Q->right) {
            Q->left = 0;
            Q->right = -1;

        } else if (Q->right == 0)
            Q->right = Q->max - 1;

        else
            Q->right -= 1;
    }
}

void peekLeft(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");
    else
        // print instead of return
        printf("\nFront(HEAD): %d\n", Q->arr[Q->left]);
}

void peekRight(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");
    else
        // print instead of return
        printf("\nBack(TAIL): %d\n", Q->arr[Q->right]);
}

void print(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue empty\n");

    else {
        printf("\n\033[33m  head{\033[0m");

        for (int n = 1, i = Q->left; n <= size(Q); ++n) {
            if (i != Q->left)
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
    printf("\nInput gets enqueued (default: right)\n\n");
    printf("[e] : switch enqueue direction\n");
    printf("[dl]: dequeue left\n");
    printf("[dr]: dequeue right\n");
    printf("[pf]: peek left\n");
    printf("[pr]: peek right\n");
    printf("[q] : to quit\n");

    Queue* q = createQueue(size);

    int maxInputSize = maxIntDigits();
    char input[maxInputSize + 1 /*for null*/];

    int done = FALSE;
    char enqueueHead = 'R';

    while (!done) {

        printf("\nQueue> ");
        scanf("%s", input);

        if (strlen(input) <= maxInputSize) {

            // `q` to quit
            if (strcmp(input, "q") == 0)
                done = TRUE; // exit

            // `pl` to peek front (HEAD)
            else if (strcmp(input, "pl") == 0)
                peekLeft(q);

            // `pr` to peek back (TAIL)
            else if (strcmp(input, "pr") == 0)
                peekRight(q);

            // `dl` to deque from left
            else if (strcmp(input, "dl") == 0) {
                dequeueLeft(q);
                print(q);

                // `dr` to deque from right
            } else if (strcmp(input, "dr") == 0) {
                dequeueRight(q);
                print(q);

            } else if (strcmp(input, "e") == 0) {
                // switch enqueuing direction
                enqueueHead = (enqueueHead == 'R') ? 'L' : 'R';
                printf("\n  Enqueue direction flipped\n");

            } else { // otherwise, enqueue the integer input

                // covert string input to integer
                int data = strtoimax(input, NULL, 10);

                // strtoimax() returns 0 for junk values
                // so, 0 should be pushed only if input
                // is actually 0
                if (data != 0 || strncmp(input, "0", 1) == 0) {
                    (enqueueHead == 'R') ? enqueueRight(q, data) : enqueueLeft(q, data);
                    print(q);
                }
            }

        } else
            printf("Max input size exceeded\n");
    }

    printf("\n");
}
