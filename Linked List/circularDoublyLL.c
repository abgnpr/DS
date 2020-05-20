// Singly Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next, *prev;
} Node;

Node* createNewNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    return newNode;
}

typedef struct CircularLinkedList {
    Node* start;
} CircularLinkedList;

CircularLinkedList* newCircularLinkedList()
{
    CircularLinkedList* newCDLL = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    newCDLL->start = NULL;
    return newCDLL;
}

// Inserts a node at the beginning
void insertBeg(CircularLinkedList* CDLL, int data)
{
    // create new
    Node* newNode = createNewNode(data);

    // if the list is empty
    if (CDLL->start == NULL) {
        // new will be first and last
        newNode->next = newNode;
        newNode->prev = newNode;
        // set start to new
        CDLL->start = newNode;
        return;
    }

    // else
    // select first and last
    Node* first = CDLL->start;
    Node* last = first->prev;

    // set next of new to first
    newNode->next = first;
    // set previous of new to
    newNode->prev = last;
    // set prev of first to new
    first->prev = newNode;
    // set next of last to new
    last->next = newNode;
    // set start to new
    CDLL->start = newNode;
}

// Inserts a node at the end
void insertEnd(CircularLinkedList* CDLL, int data)
{
    // create new
    Node* newNode = createNewNode(data);

    // if the list is empty
    if (CDLL->start == NULL) {
        // new will be first and last
        newNode->next = newNode;
        newNode->prev = newNode;
        // set start to new
        CDLL->start = newNode;
        return;
    }

    // else
    // select first and last
    Node* first = CDLL->start;
    Node* last = first->prev;

    // set next of new to first
    newNode->next = first;
    // set previous of new to last
    newNode->prev = last;
    // set next of last to new
    last->next = newNode;
    // set previous of first to new
    first->prev = newNode;
}

// Deletes the first node
void deleteFirst(CircularLinkedList* CDLL)
{
    // return if the list is empty
    if (CDLL->start == NULL)
        return;

    // else
    // select first, second and last
    Node* first = CDLL->start;
    Node* second = first->next;
    Node* last = first->prev;

    // when there's only one node
    if (first == last)
        // nullify the list
        CDLL->start = NULL;
   
    else {
        // set previous of second to last
        second->prev = last;
        // set next of last to second
        last->next = second;
        // set start to second
        CDLL->start = second;
    }

    // delete first
    free(first);
}

// Delete the last node
void deleteLast(CircularLinkedList* CDLL)
{
    // return if the list is empty
    if (CDLL->start == NULL)
        return;

    // else
    // select first, last, and second last
    Node* first = CDLL->start;
    Node* last = first->prev;
    Node* secondLast = last->prev;

    // when there's only one node
    if (first == last)
        // nullify the list
        CDLL->start = NULL;
    
    else {
        // set next of second last to first
        secondLast->next = first;
        // set previous of first to second last
        first->prev = secondLast;
    }

    // delete last
    free(last);
}

// Deletes all nodes
void deleteList(CircularLinkedList* CLL)
{
    Node *node, *nodeToFree;
    if ((node = CLL->start) != NULL) {
        do {
            nodeToFree = node;
            node = node->next;
            free(nodeToFree);
        } while (node != CLL->start);

        CLL->start = NULL;
    }
}

// Traverses and prints data of each node
void traverse(CircularLinkedList* CLL)
{
    Node* node;
    if ((node = CLL->start) != NULL) {
        printf("[%d]", node->data);
        while ((node = node->next) != CLL->start)
            printf(" <=> [%d]", node->data);
        printf("\n");
    } else
        printf("(nil)\n");
}

// driver
int main(void)
{
    CircularLinkedList* CDLL = newCircularLinkedList();

    // insert at beginning
    // ------------------------------------------
    printf("\nINSERT@BEGINNING\nOriginal : ");
    traverse(CDLL);
    for (int i = 1; i <= 5; ++i) {
        printf("insert(%d): ", i);
        insertBeg(CDLL, i);
        traverse(CDLL);
    }
    deleteList(CDLL);
    // ------------------------------------------

    // insert at end
    // ------------------------------------------
    printf("\nINSERT@END\nOriginal : ");
    traverse(CDLL);
    for (int i = 1; i <= 5; ++i) {
        printf("insert(%d): ", i);
        insertEnd(CDLL, i);
        traverse(CDLL);
    }
    deleteList(CDLL);
    // ------------------------------------------

    // delete first
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(CDLL, i);
    printf("\nDELETE^FIRST\nOriginal     : ");
    traverse(CDLL);
    for (int i = 1; i <= 5; ++i) {
        printf("deleteFirst(): ");
        deleteFirst(CDLL);
        traverse(CDLL);
    }
    deleteList(CDLL);
    // ------------------------------------------

    // delete last
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(CDLL, i);
    printf("\nDELETE^LAST\nOriginal    : ");
    traverse(CDLL);
    for (int i = 1; i <= 5; ++i) {
        printf("deleteLast(): ");
        deleteLast(CDLL);
        traverse(CDLL);
    }
    deleteList(CDLL);
    // ------------------------------------------

    free(CDLL);
    printf("\n");
    return EXIT_SUCCESS;
}
