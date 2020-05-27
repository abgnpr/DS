#include <stdio.h>
#include <stdlib.h>

#define BALANCED 0
#define LEFT_HEAVY 1
#define RIGHT_HEAVY -1

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

int height(AVLTree *T) {
    return (T == NULL)? 0: T->height;
}

void updateHeight(Node* n)
{
    if (n) 
        n->height = max(height(n->left), height(n->right));
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
        Node *child = par;
        Node *childOfChild = newNode;
        
        while (cur) {
            // calculate the balance factor of current
            int bf = balanceFactor(cur);
            
            // if current is a critical node
            if (bf > 1 || bf < -1) {
                // determine the type of rotation needed 
                // to rebalance and then rotate
                if (childOfChild == cur->left->left) {
                    // LL
                    
                } else if (childOfChild == cur->right->right) {
                    // RR
                } else if (childOfChild == cur->left->right) {
                    // LR
                } else if (childOfChild == cur->right->left) {
                    // RL
                }
            }
            
            // move up
            childOfChild = child;
            child = cur;
            cur = cur->parent;
            
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
