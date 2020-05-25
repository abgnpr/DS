#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    struct Node *left, *right;
} Node, BST;

Node* createNewNode(int data)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

BST* insert(BST* T, int data)
{

    if (T == NULL)
        T = createNewNode(data);

    else {
        Node *cur = T, *par = NULL;
        while (cur != NULL) {
            par = cur;
            cur = (data < cur->data) ? cur->left : cur->right;
        }

        if (data < par->data)
            par->left = createNewNode(data);
        else
            par->right = createNewNode(data);
    }

    return T;
}

void print(BST* T)
{
    if (T == NULL) return;

    else {
        print(T->left);
        printf("%d ", T->data);
        print(T->right);
    }
}

void main(void)
{
    BST* T;

    for (int i = 5; i <= 10; ++i)
        T = insert(T, i);

    for (int i = 1; i <= 5; ++i)
        T = insert(T, i);

    print(T);
    printf("\n");
}