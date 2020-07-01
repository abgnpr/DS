#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Element {
    int data;
    struct Element* next;
} Element;

typedef struct Queue {
    Element *head, *tail;
} Queue;

Queue* createQueue() { return (Queue*)malloc(sizeof(Queue)); }

int queueEmpty(Queue* Q) { return (Q->head == NULL) ? TRUE : FALSE; }

void enqueue(Queue* Q, int data)
{
    Element* newElement = (Element*)malloc(sizeof(Element));
    newElement->data = data;
    newElement->next = NULL;

    if (queueEmpty(Q))
        Q->head = newElement;
    else
        Q->tail->next = newElement;

    Q->tail = newElement;
}

void dequeue(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\033[31mUnderflow\033[0m");

    else {
        Element* dequeued = Q->head;
        Q->head = Q->head->next;

        // printed instead of returned
        printf("\nDequeued: %d\n", dequeued->data);
        
        free(dequeued);
    }
}

void peekFront(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");

    else
        // printed instead of returned
        printf("\nFront(HEAD): %d\n", Q->head->data);
}

void peekBack(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");

    else
        // printed instead of returned
        printf("\nBack(TAIL): %d\n", Q->tail->data);
}

void print(Queue* Q)
{
    if (queueEmpty(Q))
        printf("\nQueue Empty\n");

    else {
        printf("\n\033[33m  head{\033[0m");

        Element* e = Q->head;
        while (e != NULL) {
            if (e != Q->head)
                printf("|");
            printf(" %d ", e->data);
            e = e->next;
        }

        printf("\033[33m}tail\033[0m\n");
    }
}

int maxIntDigits()
{
    int digits = 0;
    int maxInt = INT32_MAX;
    while ((maxInt /= 10) > 0)
        digits++;
    return digits;
}

// driver
void main(void)
{
    // instructions
    printf("\nInput gets enqueued, enter d to dequeue, pf to peek front, pb to peek back q to quit\n");

    Queue* q = createQueue();

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
