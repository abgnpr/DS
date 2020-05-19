// Singly Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNewNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    return newNode;
}

typedef struct SinglyLinkedList {
    Node* start;
} SinglyLinkedList;

SinglyLinkedList* newSinglyLinkedList()
{
    SinglyLinkedList* newSLL = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    newSLL->start = NULL;
    return newSLL;
}

void deleteList(SinglyLinkedList* SLL)
{
    Node *nodeToFree, *node = SLL->start;
    while (node != NULL) {
        nodeToFree = node;
        node = node->next;
        free(nodeToFree);
    }
    SLL->start = NULL;
}

// Inserts a node at the beginning
void insertBeg(SinglyLinkedList* SLL, int data)
{
    // create new
    Node* newNode = createNewNode(data);

    // if the list is empty
    if (SLL->start == NULL) {
        // set new as first and last
        SLL->start = newNode;
        SLL->start->next = NULL;
        return;
    }

    // else
    // set next of new to start
    newNode->next = SLL->start;
    // set start to new
    SLL->start = newNode;
}

// Inserts a node at the end
void insertEnd(SinglyLinkedList* SLL, int data)
{
    // create new
    Node* newNode = createNewNode(data);

    // if the list is empty
    if (SLL->start == NULL) {
        // set new as first and last
        SLL->start = newNode;
        SLL->start->next = NULL;
        return;
    }

    // else
    // traverse to last
    Node* node = SLL->start;
    while (node->next != NULL)
        node = node->next;

    // set its next to new
    node->next = newNode;

    // set the new as last
    newNode->next = NULL;
}

// Inserts after the node whose data is `val`
void insertAfter(int val, SinglyLinkedList* SLL, int data)
{
    // scan all nodes
    for (Node* cur = SLL->start; cur != NULL; cur = cur->next) {
        // if current node data matches `val`
        if (val == cur->data) {
            // create new
            Node* newNode = createNewNode(data);
            // set next of new to next of current
            newNode->next = cur->next;
            // set next of current to new
            cur->next = newNode;
            // done
            return;
        }
    }
}

// Inserts before the node whose data is `val`
void insertBefore(int val, SinglyLinkedList* SLL, int data)
{
    // scan all nodes
    for (Node *pre = NULL, *cur = SLL->start; cur != NULL; pre = cur, cur = cur->next) {
        // if current node data matches `val`
        if (val == cur->data) {
            // create new
            Node* newNode = createNewNode(data);
            // if previous of current exists
            if (pre != NULL)
                // set next of previous to new
                pre->next = newNode;
            else // when current is first
                // set start to new
                SLL->start = newNode;
            // set next of new to current
            newNode->next = cur;
            // done
            return;
        }
    }
}

// Deletes the first node
void deleteFirst(SinglyLinkedList* SLL)
{
    // return if the list is empty
    if (SLL->start == NULL)
        return;

    // else
    // select first
    Node* first = SLL->start;
    // set start to next of first
    SLL->start = first->next;
    // delete first
    free(first);
}

// Delete the last node
void deleteLast(SinglyLinkedList* SLL)
{
    // return if the list is empty
    if (SLL->start == NULL)
        return;

    // else
    // begin with first
    Node* pre = NULL;
    Node* cur = SLL->start;

    // go to the last node
    while (cur->next != NULL) {
        pre = cur,
        cur = cur->next;
    }

    // if previous of current exists
    if (pre != NULL)
        // set it as last
        pre->next = NULL;
    else // when last is also the first
        // list will be empty after delete
        SLL->start = NULL;

    // delete last
    free(cur);
}

// Deletes a node after the node whose data is `val`
void deleteAfter(int val, SinglyLinkedList* SLL)
{
    // return if the list is empty
    if (SLL->start == NULL)
        return;

    // else
    // begin with first
    Node* cur = SLL->start;
    // traverse until we reach last
    while (cur->next != NULL) {

        // if curent node data matches `val`
        if (val == cur->data) {
            // set next to next of current
            Node* next = cur->next;
            // set next of current to next of next
            cur->next = next->next;
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
void deleteNode (int val, SinglyLinkedList* SLL)
{
    // return if the list is empty
    if (SLL->start == NULL)
        return;

    // else
    // begin with first
    Node *pre, *cur;
    pre = NULL;
    cur = SLL->start;

    // scan all nodes
    while (cur != NULL) {

        // if curent node data matches `val`
        if (val == cur->data) {
            // if previous of current exists
            if (pre != NULL)
                // set its next to next of current
                pre->next = cur->next;
            else // when current is first
                // set new start to next of current
                SLL->start = cur->next;
            // delete current
            free(cur);
            // done
            return;
        }

        // move to next nodes
        pre = cur;
        cur = cur->next;
    }
}

// Traverses and prints data of each node
void traverse(SinglyLinkedList* SLL)
{
    Node* node;
    if ((node = SLL->start) != NULL) {
        printf("[%d]", node->data);
        while ((node = node->next) != NULL)
            printf(" -> [%d]", node->data);
        printf("\n");
    } else
        printf("(nil)\n");
}

// driver
int main(void)
{
    SinglyLinkedList* SLL = newSinglyLinkedList();

    // insert at beginning
    // ------------------------------------------
    printf("\nINSERT@BEGINNING\nOriginal : ");
    traverse(SLL);
    for (int i = 1; i <= 5; ++i) {
        printf("insert(%d): ", i);
        insertBeg(SLL, i);
        traverse(SLL);
    }
    deleteList(SLL);
    // ------------------------------------------

    // insert at end
    // ------------------------------------------
    printf("\nINSERT@END\nOriginal : ");
    traverse(SLL);
    for (int i = 1; i <= 5; ++i) {
        printf("insert(%d): ", i);
        insertEnd(SLL, i);
        traverse(SLL);
    }
    deleteList(SLL);
    // ------------------------------------------

    // insert after
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(SLL, i);
    printf("\nINSERT:AFTER\nOriginal   : ");
    traverse(SLL);

    printf("ins(%d)af(%d): ", 7, 1);
    insertAfter(1, SLL, 7);
    traverse(SLL);
    printf("ins(%d)af(%d): ", 9, 5);
    insertAfter(5, SLL, 9);
    traverse(SLL);

    deleteList(SLL);
    // ------------------------------------------

    // insert before
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(SLL, i);
    printf("\nINSERT:BEFORE\nOriginal   : ");
    traverse(SLL);

    printf("ins(%d)bf(%d): ", 6, 1);
    insertBefore(1, SLL, 6);
    traverse(SLL);
    printf("ins(%d)bf(%d): ", 8, 4);
    insertBefore(4, SLL, 8);
    traverse(SLL);
    printf("ins(%d)bf(%d): ", 7, 5);
    insertBefore(5, SLL, 7);
    traverse(SLL);

    deleteList(SLL);
    // ------------------------------------------

    // delete first
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(SLL, i);
    printf("\nDELETE^FIRST\nOriginal     : ");
    traverse(SLL);
    for (int i = 1; i <= 5; ++i) {
        printf("deleteFirst(): ");
        deleteFirst(SLL);
        traverse(SLL);
    }
    deleteList(SLL);
    // ------------------------------------------

    // delete last
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(SLL, i);
    printf("\nDELETE^LAST\nOriginal    : ");
    traverse(SLL);
    for (int i = 1; i <= 5; ++i) {
        printf("deleteLast(): ");
        deleteLast(SLL);
        traverse(SLL);
    }
    deleteList(SLL);
    // ------------------------------------------

    // delete after
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(SLL, i);
    printf("\nDELETE:AFTER\nOriginal   : ");
    traverse(SLL);

    printf("deleteAfter(%d): ", 1);
    deleteAfter(1, SLL);
    traverse(SLL);
    printf("deleteAfter(%d): ", 3);
    deleteAfter(3, SLL);
    traverse(SLL);
    printf("deleteAfter(%d): ", 5);
    deleteAfter(5, SLL);
    traverse(SLL);

    deleteList(SLL);
    // ------------------------------------------

    // delete
    // ------------------------------------------
    for (int i = 1; i <= 5; ++i)
        insertEnd(SLL, i);
    printf("\nDELETE^VAL\nOriginal : ");
    traverse(SLL);

    printf("delete(%d): ", 1);
    delete (1, SLL);
    traverse(SLL);
    printf("delete(%d): ", 4);
    delete (4, SLL);
    traverse(SLL);
    printf("delete(%d): ", 5);
    delete (5, SLL);
    traverse(SLL);

    deleteList(SLL);
    // ------------------------------------------

    printf("\n");
    return EXIT_SUCCESS;
}
