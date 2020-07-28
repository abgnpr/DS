#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNDIRECTED true

struct Vertex;

// list of neighbours
typedef struct {
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

int search(char x)
{
    return -1;
}

// tests whether there is an edge from the vertex x to the vertex y;
bool adjacent(char x, char y)
{
    int p = search(x);
    int q = search(y);

    for (int i = 0; i < V[p].nbr.used; ++i)
        if (V[p].nbr.arr[i] == &V[q])
            return true;

    return false;
}

// adds the vertex x, if it is not there;
int addVertex(char x)
{
    int k = search(x);

    if (k >= 0)
        printf("Vertex '%c' already exists!\n", x);

    else {
        if (usedV == sizeV) {
            sizeV *= 2;
            V = (Vertex*)realloc(V, sizeof(Vertex) * sizeV);
        }

        k = usedV++;
        V[k].val = x;
        initNbrList(&V[k].nbr);
    }

    return k;
}

// removes the vertex x, if it is there;
void removeVertex(char x)
{
    int k = search(x);

    if (k >= 0) {
        for (int i = 0; i < V[k].nbr.used; ++i)
            removeNbr(&(V[k].nbr.arr[i]->nbr), &V[k]);
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

    if (adjacent(x, y))
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
    if (adjacent(x, y)) {
        int p = search(x);
        int q = search(y);
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

    addEdge('A', 'B');
    addEdge('A', 'C');
    addEdge('A', 'D');

    print();
}
