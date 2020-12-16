// Binary Search Tree

// Note:
// * Implemented with nodes without parent pointer
// * Doesn't support duplicate nodes

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b )

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

// returns a new empty tree
BST* createBST() { return NULL; }

// deletes all nodes of a BST, returns an empty tree
BST* deleteBST(BST* T)
{
    if (T) {
        deleteBST(T->left);
        deleteBST(T->right);
        free(T);
    }
    return NULL;
}

// mirrors the tree T
void mirror(BST* T)
{
    if (T) {
        mirror(T->left);
        mirror(T->right);
        BST* temp = T->left;
        T->left = T->right;
        T->right = temp;
    }
}

// Returns the node with smallest `data` in tree T
Node* smallest(BST* T)
{
    if (T == NULL)
        printf("Tree empty\n");

    Node* node = T;
    while (node->left)
        node = node->left;
    return node;
}

// Returns the node with biggest `data` in tree T
Node* biggest(BST* T)
{
    if (T == NULL)
        printf("Tree empty\n");

    Node* node = T;
    while (node->right)
        node = node->right;
    return node;
}

// Finds and returns the node cntaining `data` in tree T
Node* find(BST* T, int data)
{
    Node* cur = T;
    while (cur != NULL && data != cur->data)
        cur = (data < cur->data) ? cur->left : cur->right;
    return cur;
}

// Inserts a new node with `data` in tree T
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

        // In order to find the appropriate node to
        // hang the new node, traverse down comparing
        // new data with current data.
        while (cur != NULL) {
            // current node will be the parent
            // of the next node downstream
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

    // return the root
    return T;
}

// Removes the element containing `data` from tree T
// Returns the root of the main tree
BST* del(BST* T, int data)
{
    // report if the tree is empty
    if (T == NULL)
        printf("Tree Empty\n");

    else {

        // find the node to be deleted - `node`
        // and its parent - `par`
        Node *node = T, *par = NULL;
        while (node != NULL && node->data != data) {
            par = node;
            node = (data < node->data) ? node->left : node->right;
        }

        // a node matching with given `data` is found
        if (node) {

            // the node has both children
            if (node->left && node->right) {
                // replace its data with the data
                // of the next in-order successor 
                Node* s = smallest(T->right);
                node->data = s->data;
                // recursively delete the in-order
                // successor
                T->right = del(T->right, s->data);

            // the node has only left child
            } else if (node->left) {
                // node has no parent, i.e. it's the root
                if (par == NULL)
                    // left child becomes the new root
                    T = node->left;

                else {
                    // attach the left child to the appropriate
                    // branch of node's parent
                    if (node == par->left)
                        par->left = node->left;
                    else
                        par->right = node->left;
                }

                free(node); // delete the node

            // the node has only right child
            } else if (node->right) {
                // node has no parent, i.e. it's the root
                if (par == NULL)
                    // right child becomes the new root
                    T = node->right;

                else {
                    // attach the right child to the appropriate
                    // branch of node's parent
                    if (node == par->left)
                        par->left = node->right;
                    else
                        par->right = node->right;
                }

                free(node); // delete the node

            // node is a leaf
            } else {
                // node has no parent, i.e. it's the root
                if (par == NULL)
                    // tre becomes empty
                    T = NULL;

                else {
                    // nellify the appropriate parent branch
                    if (node == par->left)
                        par->left = NULL;
                    else
                        par->right = NULL;
                }

                free(node); // delete the node
            }

        // otherwise report that a node matching given data wasn't found
        } else
            printf("%d not found\n", data);
    }

    return T;
}

// Returns the height of tree T
int height(BST* T)
{
    if (T == NULL)
        return 0;

    return 1 + max(height(T->left), height(T->right));
}

// Returns total number of nodes in tree T
int totalNodes(BST* T)
{
    if (T == NULL)
        return 0;

    return 1 + totalNodes(T->left) + totalNodes(T->right);
}

// Returns total number of nodes excluding leaf nodes
int totalInternalNodes(BST* T)
{
    if (T == NULL || (T->left == NULL && T->right == NULL))
        return 0;

    return 1 + totalInternalNodes(T->left) + totalInternalNodes(T->right);
}

// Returns total number of leaf nodes
int totalExternalNodes(BST* T)
{
    if (T == NULL)
        return 0;

    if (T->left == NULL && T->right == NULL)
        return 1;

    return totalExternalNodes(T->left) + totalExternalNodes(T->right);
}

// Traverses the tree T pre order and prints each node
// before its left and right children have been printed
void preOrder(BST* T)
{
    if (T) {
        printf("%d ", T->data);
        preOrder(T->left);
        preOrder(T->right);
    }
}

// Traverses the tree T in order and prints each node
// in ascending order
void inOrder(BST* T)
{
    if (T) {
        inOrder(T->left);
        printf("%d ", T->data);
        inOrder(T->right);
    }
}

// Traverses the tree T post order and prints each node 
// after its left and right children have been printed
void postOrder(BST* T)
{
    if (T) {
        postOrder(T->left);
        postOrder(T->right);
        printf("%d ", T->data);
    }
}

// driver
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

    printf("find(4): ");
    find(T, 4) ? printf("found!\n\n") : printf("not found\n\n");

    printf("find(11): ");
    find(T, 11) ? printf("found!\n\n") : printf("not found\n\n");

    printf("Biggest: %d\n\n", biggest(T)->data);
    printf("Smallest: %d\n\n", smallest(T)->data);

    Node *node3 = find(T, 5), *node9 = find(T, 1);
    // printf("Successor(3): %d\n\n", successor(T, node3)->data);
    // printf("Predecessor(9): %d\n\n", predecessor(T, node9)->data);

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

    printf("Original: ");
    preOrder(T);
    printf("\nMirror: ");
    mirror(T);
    preOrder(T);
    printf("\n\n");

    // delete all elements
    T = deleteBST(T);
    inOrder(T);
    printf("\n\n");
}
