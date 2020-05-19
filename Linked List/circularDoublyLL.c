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

/*
// Inserts after the node whose data is `val`
void insertAfter(int val, CircularLinkedList* CDLL, int data)
{
    // scan all nodes
    for (Node* cur = CDLL->start; cur != NULL; cur = cur->next) {
        // if current node data matches `val`
        if (val == cur->data) {
            // create new
            Node* newNode = createNewNode(data);
            // if next of current exists
            if (cur->next != NULL)
                // set its previous to new
                cur->next->prev = newNode;
            // set next of new to next of current
            newNode->next = cur->next;
            // set previous of new to current
            newNode->prev = cur;
            // set next of current to new
            cur->next = newNode;

            // done
            return;
        }
    }
}

// Inserts before the node whose data is `val`
void insertBefore(int val, CircularLinkedList* CDLL, int data)
{
    // scan all nodes
    for (Node* cur = CDLL->start; cur != NULL; cur = cur->next) {
        // if current node data matches `val`
        if (val == cur->data) {
            // create new
            Node* newNode = createNewNode(data);
            // if previous of current exists
            if (cur->prev != NULL)
                // set its next to new
                cur->prev->next = newNode;
            else
                // else this should be new first
                CDLL->start = newNode;
            // set next of new to current
            newNode->next = cur;
            // set previous of new to previous of current
            newNode->prev = cur->prev;
            // set previous of current to new
            cur->prev = newNode;
            // done
            return;
        }
    }
}
*/

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

/*
// Deletes a node after the node whose data is val
void deleteAfter(int val, CircularLinkedList* CDLL)
{
    // return if the list is empty
    if (CDLL->start == NULL)
        return;

    // else
    // scan all nodes upto second last
    Node* cur = CDLL->start;
    while (cur->next != NULL) {
        // if current node data matches `val`
        if (val == cur->data) {
            // set next to next of current
            Node* next = cur->next;
            // set next of current to next of next
            cur->next = next->next;
            // if next of next exists
            if (next->next != NULL)
                // set its previous to current
                next->next->prev = cur;
            // delete the next
            free(next);
            // done
            return;
        }
        // move to the next
        cur = cur->next;
    }
}

// Deletes the node whose data is `val`
void deleteNode(int val, CircularLinkedList* CDLL)
{
    // return if the list is empty
    if (CDLL->start == NULL)
        return;

    // scan all nodes
    Node* cur = CDLL->start;
    while (cur != NULL) {
        // if current node data matches `val`
        if (val == cur->data) {
            // if next of current exists
            if (cur->next != NULL)
                // set its previous to previous of current
                cur->next->prev = cur->prev;
            // if previous of current exists
            if (cur->prev != NULL)
                // set its next to next of current
                cur->prev->next = cur->next;
            else // current is the first node
                // set start to its next
                CDLL->start = cur->next;
            free(cur);
            return;
        }
        cur = cur->next;
    }
}
*/

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

    /*
    // insert after
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(CDLL, i);
    printf("\nINSERT:AFTER\nOriginal   : ");
    traverse(CDLL);

    printf("ins(%d)af(%d): ", 7, 1);
    insertAfter(1, CDLL, 7);
    traverse(CDLL);
    printf("ins(%d)af(%d): ", 9, 5);
    insertAfter(5, CDLL, 9);
    traverse(CDLL);

    deleteList(CDLL);
    // ------------------------------------------

    // insert before
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(CDLL, i);
    printf("\nINSERT:BEFORE\nOriginal   : ");
    traverse(CDLL);

    printf("ins(%d)bf(%d): ", 6, 1);
    insertBefore(1, CDLL, 6);
    traverse(CDLL);
    printf("ins(%d)bf(%d): ", 8, 4);
    insertBefore(4, CDLL, 8);
    traverse(CDLL);

    deleteList(CDLL);
    // ------------------------------------------
*/
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
/*
    // delete after
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(CDLL, i);
    printf("\nDELETE:AFTER\nOriginal      : ");
    traverse(CDLL);

    printf("deleteAfter(%d): ", 1);
    deleteAfter(1, CDLL);
    traverse(CDLL);
    printf("deleteAfter(%d): ", 4);
    deleteAfter(4, CDLL);
    traverse(CDLL);

    deleteList(CDLL);
    // ------------------------------------------

    // delete
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(CDLL, i);
    printf("\nDELETE^VAL\nOriginal : ");
    traverse(CDLL);

    printf("delete(%d): ", 1);
    delete (1, CDLL);
    traverse(CDLL);
    printf("delete(%d): ", 4);
    delete (4, CDLL);
    traverse(CDLL);
    printf("delete(%d): ", 5);
    delete (5, CDLL);
    traverse(CDLL);

    deleteList(CDLL);
    // ------------------------------------------
*/
    free(CDLL);
    printf("\n");
    return EXIT_SUCCESS;
}
