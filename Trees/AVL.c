// AVL Tree

// Note: Doesn't support duplicate nodes

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

// Returns the greater among a and b
int max(int a, int b) { return a > b ? a : b; }

// Returns the height of the root of tree T
int height(AVLTree* T)
{
    return (T) ? T->height : -1;
}

// Updates the height of a node `n`
void updateHeight(Node* n)
{
    if (n)
        n->height = 1 + max(height(n->left), height(n->right));
}

// Returns the balance factor at a node `n`
int balanceFactor(Node* n)
{
    return height(n->left) - height(n->right);
}

// Finds and returns the node containing `data` in tree T
Node* find(AVLTree* T, int data)
{
    Node* cur = T;
    while (cur && cur->data != data)
        cur = (data < cur->data) ? cur->left : cur->right;
    return cur;
}

// rotate right
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

// rotate left
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

// idk
AVLTree* rotateLR(AVLTree* T)
{
    T->left = rotateRR(T->left);
    T = rotateLL(T);
    return T;
}

// idk
AVLTree* rotateRL(AVLTree* T)
{
    T->right = rotateLL(T->right);
    T = rotateRR(T);
    return T;
}

// Performs bottom to top height updates and balancing
// Traces the path from `cur` to root and returns the root
AVLTree* balanceAndUpdate(Node* cur)
{
    AVLTree* T;

    if (cur == NULL) {
        printf("Invalid start point");
        T = NULL;
    }

    while (cur) {

        updateHeight(cur);
        int bf = balanceFactor(cur);

        if (bf > 1) {
            // left left case
            if (balanceFactor(cur->left) >= 0)
                cur = rotateLL(cur);
            // left right case
            else // < 0
                cur = rotateLR(cur);
        }

        else if (bf < -1) {
            // right right case
            if (balanceFactor(cur->right) <= 0)
                cur = rotateRR(cur);
            // right left case
            else // > 0
                cur = rotateRL(cur);
        }

        T = cur;
        cur = cur->parent;
    }

    return T;
}

// Inserts a new node with `data` in tree T
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

        T = balanceAndUpdate(par);
    }

    return T;
}

// Returns the node with biggest `data` in tree T
Node* biggest(AVLTree* T)
{
    if (T == NULL)
        printf("Tree empty\n");

    Node* node = T;
    while (node->right)
        node = node->right;
    return node;
}

// Removes the element containing `data` from tree T
// Returns the root of the main tree
AVLTree* del(AVLTree* T, int data)
{
    if (T == NULL)
        printf("Tree Empty\n");

    else {
        Node* cur = find(T, data);
        if (cur) {

            Node* par = cur->parent;

            if (cur->right && cur->left) {
                Node* b = biggest(cur->left);
                cur->data = b->data;
                T = del(cur->left, b->data);

            } else if (cur->left) {
                cur->left->parent = par;
                if (par == NULL)
                    T = cur->left;

                else {
                    if (cur == par->left)
                        par->left = cur->left;
                    else
                        par->right = cur->left;

                    T = balanceAndUpdate(par);
                }

                free(cur);

            } else if (cur->right) {
                cur->right->parent = par;
                if (par == NULL)
                    T = cur->right;

                else {
                    if (cur == par->left)
                        par->left = cur->right;
                    else
                        par->right = cur->right;

                    T = balanceAndUpdate(par);
                }

                free(cur);

            } else {
                if (par == NULL)
                    T = NULL;

                else {
                    if (cur == par->left)
                        par->left = NULL;
                    else
                        par->right = NULL;

                    T = balanceAndUpdate(par);
                }

                free(cur);
            }

        } else
            printf("%d not found\n", data);
    }

    return T;
}

// Traverses the tree T in order and prints each node
// in ascending order
void inOrder(AVLTree* T)
{
    if (T) {
        inOrder(T->left);
        printf("%d ", T->data);
        inOrder(T->right);
    }
}

// driver
void main(void)
{
    AVLTree* T = NULL;

    printf("\n");

    printf("Insertion started\n");
    for (int i = 1; i <= 10000000; i += 1) {
        T = insert(T, i);
    }
    printf("Insertion complete\n");

    printf("\n");
    printf("\n");

    printf("Deletion started\n");
    for (int i = 10000000; i >= 1; i -= 1) {
        T = del(T, i);
    }
    printf("Deletion complete\n");

    printf("\n");
}
