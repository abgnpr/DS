// B-Tree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 5          // maximum degree
const int t = M / 2; // minimum degree
// condition: t >= 2

typedef struct Node {
  int n, keys[M - 1];
  struct Node *children[M];
  bool isLeaf;
} Node;

Node *newNode() {
  Node *node = (Node *)malloc(sizeof(Node));
  node->n = 0;
  return node;
}

typedef struct {
  Node *root;
} BTree;

BTree *createBTree() {
  BTree *T = (BTree *)malloc(sizeof(BTree));
  T->root = newNode();
  T->root->isLeaf = true;
  // diskWrite(T);

  return T;
}

typedef struct {
  bool found;
  Node *node;
  int index;
} Result;

Result search(Node *node, int key) {
  Result res;

  int i = 0;
  while (i < node->n && key > node->keys[i])
    i += 1;

  if (i < node->n && key == node->keys[i]) {
    res.found = true;
    res.node = node;
    res.index = i;
  }

  else if (node->isLeaf) {
    res.found = false;
    res.node = NULL;
    res.index = -1;
  }

  else
    // diskRead(node->children[i])
    res = search(node->children[i], key);

  return res;
}

void splitChild(Node *node, int index) {
  Node *right = newNode();
  Node *left = node->children[index];

  right->isLeaf = left->isLeaf;
  right->n = t;

  for (int i = 0; i < t - 1; ++i)
    right->keys[i] = left->keys[i + t];

  if (!left->isLeaf)
    for (int i = 0; t < t; ++i)
      right->children[i] = left->children[i + t];

  left->n = t;

  for (int i = node->n; i >= index + 1; --i)
    node->children[i + 1] = node->children[i];

  node->children[index + 1] = right;

  for (int i = node->n - 1; i >= index; --i)
    node->keys[i + 1] = node->keys[i];

  node->keys[index] = left->keys[t];
  node->n -= 1;

  // diskWrite(node);
  // diskWrite(left);
  // diskWrite(right);
}

void insertNonFull(Node *node, int key) {
  int i = node->n - 1;

  if (node->isLeaf) {
    for (; i >= 1 && key < node->keys[i]; --i)
      node->keys[i + 1] = node->keys[i];

    node->keys[i + 1] = key;
    node->n = node->n + 1;
    // diskWrite(node);

  } else {
    for (; i >= 0 && key < node->keys[i]; --i)
      ;
    i++;
    // diskRead(node->children[i])
    if (node->children[i]->n == M - 1) {
      splitChild(node, i);
      if (key > node->keys[i])
        i++;
    }
    insertNonFull(node->children[i], key);
  }
}

void insert(BTree *T, int key) {
  Node *root = T->root;

  if (root->n == M - 1) {
    Node *node = newNode();
    T->root = node;
    node->isLeaf = false;
    node->children[0] = root;

    splitChild(node, 0);
    insertNonFull(node, key);

  } else
    insertNonFull(root, key);
}

int main() {
  BTree *T = createBTree();

  for (int i = 0; i < 100; ++i)
    insert(T, i);
}