// B-Tree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 5          // maximum order
const int t = M / 2; // minimum order

typedef struct Node {
  int n, keys[M - 1];
  struct Node *ptrs[M];
  bool isLeaf;
} Node;

Node *newNode() {
  Node *node = (Node *)malloc(sizeof(Node));
  node->n = 0;
  // node->isLeaf = true;
}

typedef struct {
  Node *root;
} BTree;

BTree *createBTree() {
  BTree *T = (BTree *)malloc(sizeof(BTree));
  T->root = newNode();
  T->root->isLeaf = false;
  // diskWrite(*T);

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
    res = search(node->ptrs[i], key);

  return res;
}

void splitChild(Node *node, int index) {
  Node *right = newNode();
  Node *left = node->ptrs[index];

  right->isLeaf = left->isLeaf;
  right->n = t - 1;

  for (int i = 0; i < t - 1; ++i)
    right->keys[i] = left->keys[i + t];

  if (!left->isLeaf)
    for (int i = 0; t < t; ++i)
      right->ptrs[i] = left->ptrs[i + t];

  left->n = t - 1;

  for (int i = node->n + 1; i >= i + 1; --i)
    node->ptrs[i + 1] = node->ptrs[i];

  node->ptrs[index + 1] = right;

  for (int i = node->n; i >= index; --i)
    node->keys[i + 1] = node->keys[i];

  node->keys[index] = left->keys[t];
  node->n -= 1;

  // diskWrite(*node);
  // diskWrite(*left);
  // diskWrite(*right);
}

int main() {}