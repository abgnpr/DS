// Singly Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *createNewNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  return newNode;
}

typedef struct SinglyLinkedList {
  Node *start;
} SinglyLinkedList;

SinglyLinkedList *newSinglyLinkedList() {
  SinglyLinkedList *newSLL =
      (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
  newSLL->start = NULL;
  return newSLL;
}

void deleteList(SinglyLinkedList *SLL) {
  Node *nodeToFree, *node = SLL->start;
  while (node != NULL) {
    nodeToFree = node;
    node = node->next;
    free(nodeToFree);
  }
  SLL->start = NULL;
}

// Inserts a node at the beginning
void insertBeg(SinglyLinkedList *SLL, int data) {
  // create new
  Node *newNode = createNewNode(data);

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

// Insert a node at the end
void insertEnd(SinglyLinkedList *SLL, int data) {
  // create new
  Node *newNode = createNewNode(data);

  // if the list is empty
  if (SLL->start == NULL) {
    // set new as first and last
    SLL->start = newNode;
    SLL->start->next = NULL;
    return;
  }

  // else
  // traverse to last
  Node *node = SLL->start;
  while (node->next != NULL)
    node = node->next;

  // set its next to new
  node->next = newNode;

  // set the new as last
  newNode->next = NULL;
}

// Insert after node with data=val
void insertAfter(int val, SinglyLinkedList *SLL, int data) {
  // find node where node.data == val
  for (Node *current = SLL->start; current != NULL; current = current->next) {
    if (val == current->data) {
      // create new
      Node *newNode = createNewNode(data);
      // set next of new to next of current
      newNode->next = current->next;
      // set next of current to new
      current->next = newNode;
      // done
      return;
    }
  }
}

// Traverses and prints data of each node
void traverse(SinglyLinkedList *SLL) {
  Node *node;
  if ((node = SLL->start) != NULL) {
    printf("[%d]", node->data);
    while ((node = node->next) != NULL)
      printf(" -> [%d]", node->data);
    printf("\n");
  } else
    printf("(nil)\n");
}

// driver
int main(void) {
  SinglyLinkedList *SLL = newSinglyLinkedList();

  // insert at beginning
  printf("\nINSERT@BEGINNING\nOriginal : ");
  traverse(SLL);
  for (int i = 1; i <= 5; ++i) {
    printf("insert(%d): ", i);
    insertBeg(SLL, i);
    traverse(SLL);
  }
  deleteList(SLL);

  // insert at end
  printf("\nINSERT@END\nOriginal : ");
  traverse(SLL);
  for (int i = 1; i <= 5; ++i) {
    printf("insert(%d): ", i);
    insertEnd(SLL, i);
    traverse(SLL);
  }
  deleteList(SLL);

  // insert after
  for (int i = 0; i < 5; ++i)
    insertEnd(SLL, i);
  printf("\nINSERT:AFTER\nOriginal   : ");
  traverse(SLL);
  for (int i = 0; i < 5; ++i) {
    printf("in(%d)af(%d) : ", i+5, i);
    insertAfter(i, SLL, i+5);
    traverse(SLL);
  }
  deleteList(SLL);
}
