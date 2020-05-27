#include <stdio.h>
#include <stdlib.h>

#define BALANCED 0
#define LEFT_HEAVY 1
#define RIGHT_HEAVY -1

typedef struct Node {
    int data;
    struct Node *left, *right, *parent;
    int bf; // balance factor
} Node, AVLTree;

Node* createNewNode(int data)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = n->parent = NULL;
    n->bf = 0;
}

int height(AVLTree* T)
{
    if (T == NULL)
        return 0;

    int hL = height(T->left);
    int hR = height(T->right);

    return 1 + (hL > hR) ? hL : hR;
}

Node* find(AVLTree* T, int data)
{
    Node* cur = T;
    while (cur && cur->data != data)
        cur = (data < cur->data) ? cur->left : cur->right;
    return cur;
}

AVLTree* insert(AVLTree* T, int data)
{
    if (T == NULL)
        T = createNewNode(data);

    else {
        Node* cur = T, *par = NULL;
        while (cur) {
            par = cur;
            cur = (data < cur->data) ? cur->left : cur->right;
        }
        
    }

    return T;
}

AVLTree* del(AVLTree* T) {}

void inOrder(AVLTree* T)
{
    if (T) {
        inOrder(T->left);
        printf("%d ", T->data);
        inOrder(T->right);
    }
}

void main(void) {}