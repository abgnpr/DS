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

BST* deleteBST(BST* T)
{
    if (T) {
        deleteBST(T->left);
        deleteBST(T->right);
        free(T);
    }
    return NULL;
}

BST* mirror(BST* T)
{
    if (T) {
        mirror(T->left);
        mirror(T->right);
        BST* temp = T->left;
        T->left = T->right;
        T->right = temp;
    }
}

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

static inline int max(int a, int b) { return a > b ? a : b; }
int height(BST* T)
{
    if (T == NULL)
        return 0;

    return 1 + max(height(T->left), height(T->right));
}

int totalNodes(BST* T)
{
    if (T == NULL)
        return 0;

    return 1 + totalNodes(T->left) + totalNodes(T->right);
}

int totalInternalNodes(BST* T)
{
    if (T == NULL || (T->left == NULL && T->right == NULL))
        return 0;

    return 1 + totalInternalNodes(T->left) + totalInternalNodes(T->right);
}

int totalExternalNodes(BST* T)
{
    if (T == NULL)
        return 0;

    if (T->left == NULL && T->right == NULL)
        return 1;

    return totalExternalNodes(T->left) + totalExternalNodes(T->right);
}

void preOrder(BST* T)
{
    if (T) {
        printf("%d ", T->data);
        preOrder(T->left);
        preOrder(T->right);
    }
}

void inOrder(BST* T)
{
    if (T) {
        inOrder(T->left);
        printf("%d ", T->data);
        inOrder(T->right);
    }
}

void postOrder(BST* T)
{
    if (T) {
        postOrder(T->left);
        postOrder(T->right);
        printf("%d ", T->data);
    }
}

void main(void)
{
    BST* T = createBST();

    // insert some elements
    for (int i = 6; i <= 10; ++i)
        T = insert(T, i);
    for (int i = 1; i <= 5; ++i)
        T = insert(T, i);

    printf("\nPreorder Traversal: \n");
    preOrder(T);
    printf("\n\n");

    printf("Inorder Traversal: \n");
    inOrder(T);
    printf("\n\n");

    printf("Postorder Traversal: \n");
    postOrder(T);
    printf("\n\n");

    printf("Biggest: %d\n\n", biggest(T)->data);
    printf("Smallest: %d\n\n", smallest(T)->data);

    // delete some elements
    for (int i = 1; i <= 10; i += 2) {
        del(T, i);
        printf("delete(%d): ", i);
        inOrder(T);
        printf("\n\n");
    }

    printf("Height: %d\n\n", height(T));

    printf("Total Nodes: %d\n\n", totalNodes(T));

    printf("Total internal Nodes: %d\n\n", totalInternalNodes(T));

    printf("Total external Nodes: %d\n\n", totalExternalNodes(T));

    printf("Mirror: ");
    T = mirror(T);
    inOrder(T);
    printf("\n\n");

    // deleteing all elements
    T = deleteBST(T);
    inOrder(T);
    printf("\n\n");
}
