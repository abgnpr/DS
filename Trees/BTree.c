// B-Tree

#include <stdio.h>
#include <stdlib.h>

#define M 4
#define NOT_FOUND -1

typedef struct Node {
    int *keys, nKeys, parentIndex;
    struct Node **ptrs, *parent;
    // deques may be used for more clarity
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

#define TRUE 1
#define FALSE 0
#define ROOT 0
#define INTERNAL 1
#define LEAF 2

typedef struct SearchResult {

    Node *node, // node in which the search key is found
        *parent; // parent of node

    int found, // whether the key is found (true / false)
        index, // index of the search key in node
        pIndex, // index of the pointer to node in the parent node
        nodeType; // ROOT, LEAF or INTERNAL

} SearchResult;

SearchResult searchV2(BTree* BT, int key)
{
    SearchResult r;

    if (BT->root == NULL) {
        r.found = FALSE;
        return r;
    }

    r.node = BT->root;
    r.nodeType = ROOT;
    r.parent = NULL;

    for (;;) {

        int L = 0, R = r.node->nKeys - 1, mid;
        while (L <= R) {
            mid = (L + R) / 2;
            if (key == r.node->keys[mid]) {
                r.found = TRUE;
                r.index = mid;
                return r;
            } else if (key < r.node->keys[mid])
                R = mid - 1;
            else
                L = mid + 1;
        }

        if (r.node->ptrs[L] != NULL) {
            r.parent = r.node;
            r.pIndex = L;
            r.node = r.node->ptrs[L];

        } else {
            r.nodeType = LEAF;
            break;
        }
    }

    r.found = FALSE;
    return r;
}

void delKey(Node* node, int keyIndex)
{
    for (int i = keyIndex + 1; i < node->nKeys; ++i)
        node->keys[i - 1] = node->keys[i];

    node->nKeys -= 1;
}

void rebalance(BTree* BT, Node* node)
{
    Node *rSib = node->parent->ptrs[node->parentIndex - 1], // right sibling
        *lSib = node->parent->ptrs[node->parentIndex + 1]; // left sibling

    if (rSib && rSib->nKeys > (M - 1) / 2) {
        node->keys[node->nKeys++] = node->parent->keys[node->parentIndex];
        node->parent->keys[node->parentIndex] = rSib->keys[0];
        delKey(rSib, 0);

    } else if (lSib && lSib->nKeys > (M - 1) / 2) {
        for (int i = node->nKeys; i > 0; --i)
            node->keys[i] = node->keys[i - 1];
        node->keys[0] = node->parent->keys[node->parentIndex - 1];
        node->nKeys += 1;
        node->parent->keys[node->parentIndex - 1] = lSib->keys[lSib->nKeys - 1];
        delKey(rSib, lSib->nKeys - 1);

    } else {
        Node *left, *right;

        if (lSib) {
            left = lSib;
            right = node;
        } else {
            left = node;
            right = rSib;
        }

        left->keys[left->nKeys++] = left->parent->keys[left->parentIndex];
        for (int j = 0; j < right->nKeys; ++j)
            left->keys[left->nKeys++] = right->keys[j];
        freeNode(right);
        delKey(left->parent, left->parentIndex);

        if (left->parent == BT->root && BT->root->nKeys == 0) {
            freeNode(BT->root);
            BT->root = left;

        } else if (left->parent->nKeys < (M - 1) / 2)
            rebalance(BT, left->parent);
    }
}

void del(BTree* BT, int key)
{
    SearchResult d = searchV2(BT, key);

    if (d.found == FALSE)
        printf("%d doesn't exist!\n", key);

    else if (d.nodeType == LEAF) {
        delKey(d.node, d.index);
        if (d.node->nKeys < (M - 1) / 2)
            rebalance(BT, d.node);
    }

    else if (d.nodeType == INTERNAL) {
        BTree* rightSubtree;
        rightSubtree->root = d.node->ptrs[d.index + 1];
        Node* sNode = nodeWithSmallestKey(rightSubtree);
        d.node->keys[d.index] = sNode->keys[0];
        if (sNode->nKeys < (M - 1) / 2)
            rebalance(BT, sNode);
    }
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

// how to get parentIndex
#define UNDEFINED -1

void ins(BTree* BT, int key)
{
    SearchResult r = searchV2(BT, key);
    
    if (r.found == TRUE) {
        printf("%d already exists!\n", key);
        return;
    }
    
    // if the tree is empty create a new node
    if (BT->root == NULL) {
        BT->root = newNode();
        BT->root->parentIndex = UNDEFINED;
    }

    Node* ptr = NULL;

    for (;;) {
        r.node->keys[r.node->nKeys] = key;
        r.node->ptrs[r.node->nKeys + 1] = ptr;

        
    }

    /*
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
            } // todo: change to mergesort

            // now number of keys is increased by 1
            node->nKeys += 1;

            // if the node is overflown
            if (node->nKeys > M - 1) {
                // split the node

                int mid = node->nKeys / 2; // median key index
                int midKey = node->keys[mid]; //  median key
                Node* newnode = newNode(); // create a new node

                // move the second half to new node
                int i, j = 0;
                for (i = mid + 1; i < node->nKeys; ++i, ++j) {
                    newnode->keys[j] = node->keys[i];
                    newnode->ptrs[j] = node->ptrs[i];
                }
                newnode->ptrs[j] = node->ptrs[i]; // once more for ptrs[]

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
*/
}

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
