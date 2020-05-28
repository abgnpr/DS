#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data, height;
    struct Node *left, *right, *parent;
} Node, AVLTree;

Node* createNewNode(int data)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = n->parent = NULL;
    n->height = 0;
}

int max(int a, int b) { return a > b ? a : b; }

int height(AVLTree* T)
{
    return (T) ? T->height : -1;
}

void updateHeight(Node* n)
{
    if (n)
        n->height = 1 + max(height(n->left), height(n->right));
}

int balanceFactor(AVLTree* T)
{
    return height(T->left) - height(T->right);
}

Node* find(AVLTree* T, int data)
{
    Node* cur = T;
    while (cur && cur->data != data)
        cur = (data < cur->data) ? cur->left : cur->right;
    return cur;
}

AVLTree* rotateLL(AVLTree* T)
{
    Node* TP;
    AVLTree *TL, *TLR;

    TP = T->parent;
    TL = T->left;
    TLR = TL->right;

    if (TP) {
        if (T == TP->left)
            TP->left = TL;
        else
            TP->right = TL;
    }
    TL->parent = TP;

    TL->right = T;
    T->parent = TL;

    T->left = TLR;
    if (TLR)
        TLR->parent = T;

    updateHeight(TLR);
    updateHeight(T);
    updateHeight(TL);
    updateHeight(TP);

    return TL;
}

AVLTree* rotateRR(AVLTree* T)
{
    Node* TP;
    AVLTree *TR, *TRL;

    TP = T->parent;
    TR = T->right;
    TRL = TR->left;

    if (TP) {
        if (T == TP->left)
            TP->left = TR;
        else
            TP->right = TR;
    }
    TR->parent = TP;

    TR->left = T;
    T->parent = TR;

    T->right = TRL;
    if (TRL)
        TRL->parent = T;

    updateHeight(TRL);
    updateHeight(T);
    updateHeight(TR);
    updateHeight(TP);

    return TR;
}

AVLTree* rotateLR(AVLTree* T)
{
    T->left = rotateRR(T->left);
    T = rotateLL(T);
    return T;
}

AVLTree* rotateRL(AVLTree* T)
{
    T->right = rotateLL(T->right);
    T = rotateRR(T);
    return T;
}

AVLTree* insert(AVLTree* T, int data)
{
    if (T == NULL)
        T = createNewNode(data);

    else {

        Node *cur = T, *par = NULL;
        while (cur) {
            par = cur;
            cur = (data < cur->data) ? cur->left : cur->right;
        }

        Node* newNode = createNewNode(data);
        newNode->parent = par;
        if (data < par->data)
            par->left = newNode;
        else
            par->right = newNode;

        updateHeight(par);

        // climb upwards to look for critical nodes
        cur = par->parent;
        Node* child = par;
        Node* childOfChild = newNode;

        while (cur) {

            updateHeight(cur);
            // calculate the balance factor of current
            int bf = balanceFactor(cur);

            // if current is a critical node
            if (bf > 1 || bf < -1) {
                // determine the type of rotation needed
                // to rebalance and then rotate
                if (cur->left && childOfChild == cur->left->left) {
                    cur = rotateLL(cur);

                } else if (cur->right && childOfChild == cur->right->right) {
                    cur = rotateRR(cur);

                } else if (cur->left && childOfChild == cur->left->right) {
                    cur = rotateLR(cur);

                } else if (cur->right && childOfChild == cur->right->left) {
                    cur = rotateRL(cur);
                }
            }

            // move up
            childOfChild = child;
            child = cur;
            cur = cur->parent;
        }

        T = child;
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

void main(void)
{
    printf("\n");
}
