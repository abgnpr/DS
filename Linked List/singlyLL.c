// Singly Linked List

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node *next;
} Node;

Node *createNewNode(int data)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  return newNode;
}

typedef struct SinglyLinkedList
{
  Node *start;
} SinglyLinkedList;

SinglyLinkedList *newSinglyLinkedList()
{
  SinglyLinkedList *newSLL =
      (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
  newSLL->start = NULL;
  return newSLL;
}

void deleteList(SinglyLinkedList *SLL)
{
  Node *nodeToFree, *node = SLL->start;
  while (node != NULL)
  {
    nodeToFree = node;
    node = node->next;
    free(nodeToFree);
  }
}

// Inserts a node at the beginning
