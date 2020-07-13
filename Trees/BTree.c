// B-Tree

#include <stdio.h>
#include <stdlib.h>

#define M 4
#define NOT_FOUND -1

typedef struct Node {
    int *keys, nKeys;
    struct Node **ptrs, *parent;
} Node;

Node* newNode()
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = NULL;

    //  both keys[] and ptrs[] have 1 space extra

    node->keys = (int*)malloc(sizeof(int) * ((M - 1) + 1));
    node->nKeys = 0;

    node->ptrs = (Node**)malloc(sizeof(Node*) * (M + 1));
    for (int i = 0; i < M; ++i)
        node->ptrs[i] = NULL;

    return node;
}

void freeNode(Node* node)
{
    free(node->keys);
    free(node->ptrs);
    free(node);
}

typedef struct BTree {
    Node* root;
} BTree;

BTree* createBTree()
{
    return (BTree*)malloc(sizeof(BTree));
}

int search(BTree* BT, int key, Node** node)
{
    if (BT->root == NULL) {
        *node = NULL;
        return NOT_FOUND;
    }

    *node = BT->root;

    for (;;) {
        int L = 0, R = (*node)->nKeys - 1, mid;
        while (L <= R) {
            mid = (L + R) / 2;
            if (key == (*node)->keys[mid])
                return mid;
            else if (key < (*node)->keys[mid])
                R = mid - 1;
            else
                L = mid + 1;
        }

        if ((*node)->ptrs[L] != NULL)
            *node = (*node)->ptrs[L];
        else
            break;
    }

    return NOT_FOUND;
}

void swapKeys(int A[], int m, int n)
{
    int temp = A[m];
    A[m] = A[n];
    A[n] = temp;
}

void swapPtrs(Node** P, int m, int n)
{
    Node* temp = P[m];
    P[m] = P[n];
    P[n] = temp;
}

// issue - pointer management
void ins(BTree* BT, int key)
{
    // if the tree is empty create a new node
    if (BT->root == NULL)
        BT->root = newNode();

    Node *node, *ptr = NULL;
    if (search(BT, key, &node) == NOT_FOUND) {

        // now var 'node' points to the leaf
        // where the new key should be inserted

        for (;;) {
            // k: next empty position in keys[]
            int k = node->nKeys;

            // add new key at the end of keys[]
            node->keys[k] = key;
            // add new pointer to the end of ptrs[]
            node->ptrs[k + 1] = ptr;

            // relocate the new key along with the new
            // pointer to maintain the sorted order of keys[]
            for (; k > 0 && node->keys[k - 1] > node->keys[k]; --k) {
                swapKeys(node->keys, k - 1, k);
                swapPtrs(node->ptrs, k, k + 1);
            }

            // now number of keys is increased by 1
            node->nKeys += 1;

            // if the node is overflown
            if (node->nKeys > M - 1) {
                // split the node

                int mid = node->nKeys / 2; // median key index
                int midKey = node->keys[mid]; //  median key
                Node* newnode = newNode(); // create a new node

                // shift the second half to new node
                int i, j = 0;
                for (i = mid + 1; i < node->nKeys; ++i, ++j) {
                    newnode->keys[j] = node->keys[i];
                    newnode->ptrs[j] = node->ptrs[i];
                }
                // 1 more for ptrs[]
                newnode->ptrs[j] = node->ptrs[i];

                // if node is the root, then after the split
                // we need a new root node, which will be the
                // parent of node and new node
                if (node->parent == NULL) {
                    node->parent = newNode();
                    BT->root = node->parent;
                    BT->root->ptrs[0] = node;
                }

                // new node will have the same parent
                newnode->parent = node->parent;

                // update number of keys in both nodes
                node->nKeys = mid;
                newnode->nKeys = j;

                // push the median key and the
                // second node pointer to parent
                node = node->parent;
                ptr = newnode;
                key = midKey;

            } else
                break;
        }

    } else
        printf("%d already exists!", key);
}

void del(BTree* BT, int data) { }

void main(void)
{
    BTree* BT = createBTree();

    ins(BT, 30);
    ins(BT, 10);
    ins(BT, 50);
    ins(BT, 40);
    ins(BT, 20);
    ins(BT, 60);

    printf("\n");
}
