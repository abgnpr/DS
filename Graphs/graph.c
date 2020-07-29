// GRAPH using adjacency list

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNDIRECTED true // flip to make directed

struct Vertex; // forward declaration

// list of neighbours
typedef struct NeighbourList {
    struct Vertex** arr;
    int size, used;
} NbrList;

typedef struct Vertex {
    char val; // vertex value
    NbrList nbr; // list of pointers to neighbouring vertices
} Vertex;

Vertex* V; // vertex set
int sizeV = 10, usedV = 0;

void initNbrList(NbrList* nbr)
{
    nbr->arr = (Vertex**)malloc(sizeof(Vertex*));
    nbr->size = 1;
    nbr->used = 0;
}

void insertNbr(NbrList* nbr, Vertex* vp)
{
    for (int i = 0; i < nbr->used; ++i)
        if (nbr->arr[i] == vp)
            return;

    if (nbr->used == nbr->size) {
        nbr->size *= 2;
        nbr->arr = (Vertex**)realloc(nbr->arr, sizeof(Vertex*) * nbr->size);
    }

    nbr->arr[nbr->used++] = vp;
}

void removeNbr(NbrList* nbr, Vertex* vp)
{
    for (int i = 0; i < nbr->used; ++i) {
        if (nbr->arr[i] == vp) {
            for (int j = i + 1; j < nbr->used; ++j)
                nbr->arr[j - 1] = nbr->arr[j];
            nbr->used--;
            return;
        }
    }
}

// binary search on vertex set to find the
// vertex with value x; returns its index
int search(char x)
{
    int L = 0, R = usedV - 1, mid;

    while (L <= R) {
        mid = (L + R) / 2;
        if (x == V[mid].val)
            return mid;
        else if (x < V[mid].val)
            R = mid - 1;
        else
            L = mid + 1;
    }

    return -1;
}

// comparison function for sortVetrices()
int cmpVal(const void* a, const void* b)
{
    Vertex u = *(const Vertex*)a;
    Vertex v = *(const Vertex*)b;
    return (u.val > v.val) - (u.val < v.val);
}

// sorts the vertex set in increasing order of values
void sortVertices() { qsort(V, usedV, sizeof(Vertex), cmpVal); }

// tests whether there is an edge from the vertex x to the vertex y;
bool adjacent(const Vertex* a, const Vertex* b)
{
    for (int i = 0; i < a->nbr.used; ++i)
        if (a->nbr.arr[i] == b)
            return true;

    return false;
}

// adds the vertex x, if it is not there;
int addVertex(char x)
{
    int k = search(x);

    if (k < 0) {
        if (usedV == sizeV) {
            sizeV *= 2;
            V = (Vertex*)realloc(V, sizeof(Vertex) * sizeV);
        }

        k = usedV++;
        
        V[k].val = x;
        initNbrList(&V[k].nbr);

        sortVertices();
    }

    return k;
}

// removes the vertex x, if it is there;
void removeVertex(char x)
{
    int k = search(x);

    if (k >= 0) {
        if (UNDIRECTED)
            for (int i = 0; i < V[k].nbr.used; ++i)
                removeNbr(&(V[k].nbr.arr[i]->nbr), &V[k]);
        else
            for (int i = 0; i < usedV; ++i)
                if (i != k && adjacent(&V[i], &V[k]))
                    removeNbr(&V[i].nbr, &V[k]);

        for (int j = k + 1; j < usedV; ++j)
            V[j - 1] = V[j];
        usedV--;

        // deflate
    }
}

// adds the edge from the vertex x to the vertex y, if it is not there;
void addEdge(char x, char y)
{
    // add the vertices if they do not exist
    int p = addVertex(x);
    int q = addVertex(y);

    if (adjacent(&V[p], &V[q]))
        printf("Edge %c - %c already exists!\n", x, y);

    else {
        insertNbr(&V[p].nbr, &V[q]);
        if (UNDIRECTED)
            insertNbr(&V[q].nbr, &V[p]);
    }
}

// removes the edge from the vertex x to the vertex y, if it is there;
void removeEdge(char x, char y)
{
    int p = search(x);
    int q = search(y);
    if (adjacent(&V[p], &V[q])) {
        removeNbr(&V[p].nbr, &V[q]);
        if (UNDIRECTED)
            removeNbr(&V[q].nbr, &V[p]);

        // deflate

    } else
        printf("Edge %c - %c doesn't exist!\n", x, y);
}

// utility func to print the adj list
void print()
{
    for (int i = 0; i < usedV; ++i) {
        printf("[%c]: ", V[i].val);
        for (int j = 0; j < V[i].nbr.used; ++j)
            printf(" %c", V[i].nbr.arr[j]->val);
        printf("\n");
    }
}

// driver
void main(void)
{
    // vertex set must be sorted by values
    V = (Vertex*)malloc(sizeof(Vertex) * sizeV);

    addVertex('A');
    addVertex('9');

    addEdge('A', '9');

    addEdge('A', 'B');
    addEdge('A', 'C');
    addEdge('A', 'D');
    addEdge('C', 'B');
    addEdge('D', 'B');
    addEdge('D', 'C');

    print();
    printf("\n");

    // removeEdge('9', 'A');
    removeVertex('D');
    print();
}
