// Singly Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* createNewNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    return newNode;
}

typedef struct DoublyLinkedList {
    Node* start;
} DoublyLinkedList;

DoublyLinkedList* newDoublyLinkedList()
{
    DoublyLinkedList* newDLL = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    newDLL->start = NULL;
    return newDLL;
}

// Inserts a node at the beginning
void insertBeg(DoublyLinkedList* DLL, int data)
{
    // create new
    Node* newNode = createNewNode(data);
    // new at first will have no previous
    newNode->prev = NULL;

    // if the list is empty
    if (DLL->start == NULL) {
        // set new as first and last
        DLL->start = newNode;
        newNode->next = NULL;
        return;
    }

    // else
    // set next of new to start
    newNode->next = DLL->start;
    // set prev of start to new
    DLL->start->prev = newNode;
    // set start to new
    DLL->start = newNode;
}

// Inserts a node at the end
void insertEnd(DoublyLinkedList* DLL, int data)
{
    // create new
    Node* newNode = createNewNode(data);
    // new at last will have no next
    newNode->next = NULL;

    // if the list is empty
    if (DLL->start == NULL) {
        // new at first will have no previous
        newNode->prev = NULL;
        // set new as first
        DLL->start = newNode;
        return;
    }

    // else
    // traverse to last
    Node* node = DLL->start;
    while (node->next != NULL)
        node = node->next;

    // set its next to new
    node->next = newNode;

    // set previous of new to last
    newNode->prev = node;
}

// Inserts after the node whose data is `val`
void insertAfter(int val, DoublyLinkedList* DLL, int data)
{
    // scan all nodes
    for (Node* cur = DLL->start; cur != NULL; cur = cur->next) {
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

// Inserts before the node whose data equals `val`
void insertBefore(int val, DoublyLinkedList* DLL, int data)
{
    // scan all nodes
    for (Node* cur = DLL->start; cur != NULL; cur = cur->next) {
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
                DLL->start = newNode;
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

// Deletes the first node
void deleteFirst(DoublyLinkedList* DLL)
{
    // return if the list is empty
    if (DLL->start == NULL)
        return;

    // else
    // select first
    Node* first = DLL->start;
    // set start to next of first
    DLL->start = first->next;
    // delete first
    free(first);
    // if the list has not become empty
    if (DLL->start != NULL)
        // new start will have no previous
        DLL->start->prev = NULL;
}

// Delete the last node
void deleteLast(DoublyLinkedList* DLL)
{
    // return if the list is empty
    if (DLL->start == NULL)
        return;

    // else
    // go to last
    Node* node = DLL->start;
    while (node->next != NULL)
        node = node->next;

    // if previous of last exists
    if (node->prev != NULL)
        // set it as last
        node->prev->next = NULL;
    else // last is also the first
        // list is going to be empty
        DLL->start = NULL;

    // delete last
    free(node);
}

// Deletes a node after the node whose data equals `val`
void deleteAfter(int val, DoublyLinkedList* DLL)
{
    // return if the list is empty
    if (DLL->start == NULL)
        return;

    // else
    // scan all nodes upto second last
    Node* cur = DLL->start;
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

// Deletes the node whose data equals `val`
void deleteNode (int val, DoublyLinkedList* DLL)
{
    // return if the list is empty
    if (DLL->start == NULL)
        return;

    // scan all nodes
    Node* cur = DLL->start;
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
                DLL->start = cur->next;
            free(cur);
            return;
        }
        cur = cur->next;
    }
}

// Deletes all nodes
void deleteList(DoublyLinkedList* DLL)
{
    Node *nodeToFree, *node = DLL->start;
    while (node != NULL) {
        nodeToFree = node;
        node = node->next;
        free(nodeToFree);
    }
    DLL->start = NULL;
}

// Traverses and prints data of each node
void traverse(DoublyLinkedList* DLL)
{
    Node* node = DLL->start;
    if (node != NULL) {
        printf("[%d]", node->data);
        while ((node = node->next) != NULL)
            printf(" <=> [%d]", node->data);
        printf("\n");
    } else
        printf("(nil)\n");
}

// driver
int main(void)
{
    DoublyLinkedList* DLL = newDoublyLinkedList();

    // insert at beginning
    // ------------------------------------------
    printf("\nINSERT@BEGINNING\nOriginal : ");
    traverse(DLL);
    for (int i = 1; i <= 5; ++i) {
        printf("insert(%d): ", i);
        insertBeg(DLL, i);
        traverse(DLL);
    }
    deleteList(DLL);
    // ------------------------------------------

    // insert at end
    // ------------------------------------------
    printf("\nINSERT@END\nOriginal : ");
    traverse(DLL);
    for (int i = 1; i <= 5; ++i) {
        printf("insert(%d): ", i);
        insertEnd(DLL, i);
        traverse(DLL);
    }
    deleteList(DLL);
    // ------------------------------------------

    // insert after
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(DLL, i);
    printf("\nINSERT:AFTER\nOriginal   : ");
    traverse(DLL);

    printf("ins(%d)af(%d): ", 7, 1);
    insertAfter(1, DLL, 7);
    traverse(DLL);
    printf("ins(%d)af(%d): ", 9, 5);
    insertAfter(5, DLL, 9);
    traverse(DLL);

    deleteList(DLL);
    // ------------------------------------------

    // insert before
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(DLL, i);
    printf("\nINSERT:BEFORE\nOriginal   : ");
    traverse(DLL);

    printf("ins(%d)bf(%d): ", 6, 1);
    insertBefore(1, DLL, 6);
    traverse(DLL);
    printf("ins(%d)bf(%d): ", 8, 4);
    insertBefore(4, DLL, 8);
    traverse(DLL);

    deleteList(DLL);
    // ------------------------------------------

    // delete first
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(DLL, i);
    printf("\nDELETE^FIRST\nOriginal     : ");
    traverse(DLL);
    for (int i = 1; i <= 5; ++i) {
        printf("deleteFirst(): ");
        deleteFirst(DLL);
        traverse(DLL);
    }
    deleteList(DLL);
    // ------------------------------------------

    // delete last
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(DLL, i);
    printf("\nDELETE^LAST\nOriginal    : ");
    traverse(DLL);
    for (int i = 1; i <= 5; ++i) {
        printf("deleteLast(): ");
        deleteLast(DLL);
        traverse(DLL);
    }
    deleteList(DLL);
    // ------------------------------------------

    // delete after
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(DLL, i);
    printf("\nDELETE:AFTER\nOriginal      : ");
    traverse(DLL);

    printf("deleteAfter(%d): ", 1);
    deleteAfter(1, DLL);
    traverse(DLL);
    printf("deleteAfter(%d): ", 4);
    deleteAfter(4, DLL);
    traverse(DLL);

    deleteList(DLL);
    // ------------------------------------------

    // delete
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(DLL, i);
    printf("\nDELETE^VAL\nOriginal : ");
    traverse(DLL);

    printf("delete(%d): ", 1);
    delete (1, DLL);
    traverse(DLL);
    printf("delete(%d): ", 4);
    delete (4, DLL);
    traverse(DLL);
    printf("delete(%d): ", 5);
    delete (5, DLL);
    traverse(DLL);

    deleteList(DLL);
    // ------------------------------------------

    free(DLL);
    printf("\n");
    return EXIT_SUCCESS;
}
