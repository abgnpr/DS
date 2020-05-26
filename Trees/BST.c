#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
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

BST* createBST() { return NULL; }

Node* smallest(BST* T)
{
    Node* node = T;
    while (node->left)
        node = node->left;
    return node;
}

Node* biggest(BST* T)
{
    Node* node = T;
    while (node->right)
        node = node->right;
    return node;
}

BST* insert(BST* T, int data)
{
    // if the tree is empty (root is NULL)
    if (T == NULL)
        // create a new node and
        // add it as the root
        T = createNewNode(data);

    else {
        // begin with the root, and since root
        // has no parents, its parent is NULL
        Node *cur = T, *par = NULL;

        // traverse down comparing current data with
        // new data to find the correct parent to
        // hang the new node
        while (cur != NULL) {
            // current node will be the parent
            // of the next child downstream
            par = cur;

            // if the new data is less than current
            // node’s data then move to the left sub-tree,
            // else move to the right sub-tree.
            cur = (data < cur->data) ? cur->left : cur->right;
        }

        // if the new data is less than
        // that of the parent node
        if (data < par->data)
            // the new node is inserted in the
            // left sub-tree
            par->left = createNewNode(data);
        else
            // else it is inserted in the
            // left sub-tree
            par->right = createNewNode(data);
    }

    return T;
}

BST* del(BST* T, int data)
{
    if (T == NULL)
        printf("Tree Empty\n");

    else {

        Node *cur = T, *par = NULL;
        while (cur != NULL && cur->data != data) {
            par = cur;
            cur = (data < cur->data) ? cur->left : cur->right;
        }

        if (cur) {

            if (cur->left && cur->right) {
                Node* s = smallest(T->right);
                cur->data = s->data;
                T->right = del(T->right, s->data);

            } else if (cur->left) {
                if (par == NULL)
                    T = cur->left;
                else if (cur == par->left)
                    par->left = cur->left;
                else
                    par->right = cur->left;

                free(cur);

            } else if (cur->right) {
                if (par == NULL)
                    T = cur->right;
                else if (cur == par->left)
                    par->left = cur->right;
                else
                    par->right = cur->right;

                free(cur);

            } else {
                if (par == NULL)
                    T = NULL;
                else if (cur == par->left)
                    par->left = NULL;
                else
                    par->right = NULL;

                free(cur);
            }

        } else
            printf("%d not found\n", data);
    }

    return T;
}

void print(int n) { printf("%d ", n); }

void preOrder(BST* T, void (*f)(int))
{
    if (T) {
        (*f)(T->data);
        preOrder(T->left, *f);
        preOrder(T->right, *f);
    }
}

void inOrder(BST* T, void (*f)(int))
{
    if (T) {
        inOrder(T->left, *f);
        (*f)(T->data);
        inOrder(T->right, *f);
    }
}

void postOrder(BST* T, void (*f)(int))
{
    if (T) {
        postOrder(T->left, *f);
        postOrder(T->right, *f);
        (*f)(T->data);
    }
}

void main(void)
{
    BST* T = createBST();

    for (int i = 6; i <= 10; ++i)
        T = insert(T, i);

    for (int i = 1; i <= 5; ++i)
        T = insert(T, i);

    preOrder(T, print);
    printf("\n\n");

    inOrder(T, print);
    printf("\n\n");

    postOrder(T, print);
    printf("\n\n");

    printf("Biggest: %d\n\n", biggest(T)->data);
    printf("Smallest: %d\n\n", smallest(T)->data);

    for (int i = 11; i >= -2; --i) {
        T = del(T, i);
        inOrder(T, print);
        printf("\n");
    }
}
