// Circular Singly Linked List

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

typedef struct CircularLinkedList
{
  Node *start;
} CircularLinkedList;

CircularLinkedList *newCircularLinkedList()
{
  CircularLinkedList *newCLL =
      (CircularLinkedList *)malloc(sizeof(CircularLinkedList));
  newCLL->start = NULL;
  return newCLL;
}

void deleteList(CircularLinkedList *CLL)
{
  Node *node, *nodeToFree;
  if ((node = CLL->start) != NULL)
  {
    do
    {
      nodeToFree = node;
      node = node->next;
      free(nodeToFree);
    } while (node != CLL->start);

    CLL->start = NULL;
  }
}

// Inserts a node at the beginning
void insertBeg(CircularLinkedList *CLL, int data)
{
  Node *newNode = createNewNode(data);

  // if the list is empty
  if (CLL->start == NULL)
  {
    // insert the new node and set
    // itself as the first and last
    newNode->next = newNode;
    CLL->start = newNode;
    return;
  }

  // else
  // go to the last node
  Node *node = CLL->start;
  while (node->next != CLL->start)
    node = node->next;

  // set its next to new node
  node->next = newNode;

  // set the next of new node to start
  newNode->next = CLL->start;

  // set the start to new node
  CLL->start = newNode;
}

// Inserts a node at the end
void insertEnd(CircularLinkedList *CLL, int data)
{
  Node *newNode = createNewNode(data);

  // if the list is empty
  if (CLL->start == NULL)
  {
    // insert the new node and set
    // itself as the first and last
    newNode->next = newNode;
    CLL->start = newNode;
    return;
  }

  // else
  // go to the last node
  Node *node = CLL->start;
  while (node->next != CLL->start)
    node = node->next;

  // set its next node to new node
  node->next = newNode;

  // set the next of new node to start
  newNode->next = CLL->start;
}

// Deletes the first node
void deleteFirst(CircularLinkedList *CLL)
{
  // return if list is empty
  if (CLL->start == NULL)
    return;

  // when there's only one node
  if (CLL->start == CLL->start->next)
  {
    // free the node and nullify the list
    free(CLL->start);
    CLL->start = NULL;
    return;
  }

  // else
  // go to the last node
  Node *node;
  while (node->next != CLL->start)
    node = node->next;

  // set its next to next of first
  node->next = CLL->start->next;

  // free first
  free(CLL->start);

  // set new start to next of last
  CLL->start = node->next;
}

// Deletes the last node
void deleteLast(CircularLinkedList *CLL)
{
  // return if list is empty
  if (CLL->start == NULL)
    return;

  // when there's only one node
  if (CLL->start == CLL->start->next)
  {
    // free the node and nullify the list
    free(CLL->start);
    CLL->start = NULL;
    return;
  }

  // else
  // go to second last node
  Node *node = CLL->start;
  while (node->next->next != CLL->start)
    node = node->next;

  // free the last node
  free(node->next);

  // set next of second last to start
  node->next = CLL->start;
}

// Traverses and prints data of each node
void traverse(CircularLinkedList *CLL)
{
  Node *node;
  if ((node = CLL->start) != NULL)
  {
    printf("[ %d ]", node->data);
    while ((node = node->next) != CLL->start)
      printf("->[ %d ]", node->data);
    printf("\n");
  }
  else
    printf("(nil)\n");
}

// driver
int main(void)
{
  CircularLinkedList *CLL = newCircularLinkedList();

  // insert at beginning
  printf("\n@BEGINNING\nOriginal : ");
  traverse(CLL);
  for (int i = 1; i <= 5; ++i)
  {
    printf("insert(%d): ", i);
    insertBeg(CLL, i);
    traverse(CLL);
  }
  deleteList(CLL);

  // insert at end
  printf("\n@END\nOriginal : ");
  traverse(CLL);
  for (int i = 1; i <= 5; i++)
  {
    printf("insert(%d): ", i);
    insertEnd(CLL, i);
    traverse(CLL);
  }
  deleteList(CLL);

  // delete first
  for (int i = 1; i <= 5; ++i)
    insertEnd(CLL, i);
  printf("\n^FIRST\nOriginal : ");
  traverse(CLL);
  for (int i = 1; i <= 5; ++i)
  {
    printf("delete(%d): ", i);
    deleteFirst(CLL);
    traverse(CLL);
  }

  // delete last
  for (int i = 1; i <= 5; ++i)
    insertEnd(CLL, i);
  printf("\n^LAST\nOriginal : ");
  traverse(CLL);
  for (int i = 5; i >= 1; --i)
  {
    printf("delete(%d): ", i);
    deleteLast(CLL);
    traverse(CLL);
  }

  deleteList(CLL);
  free(CLL);

  printf("\n");
  return EXIT_SUCCESS;
}
