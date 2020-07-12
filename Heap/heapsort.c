// HEAPSORT

// note: uses max heap, so it sorts in descending order 

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define MAX 10
int
    heap[MAX], // a heap of size 'MAX'
    n = -1; // number of elements in the heap

// returns true if the heap is empty
int heapEmpty() { return (n == -1) ? 1 : 0; }

// returns true if the heap is full
int heapFull() { return (n == MAX - 1) ? 1 : 0; }

// swaps values at positions m and n in heap[]
void swap(int m, int n)
{
    int temp = heap[m];
    heap[m] = heap[n];
    heap[n] = temp;
}

// inserts a new 'data' element into the heap
int ins(int data)
{
    if (heapFull())
        return FAILURE; // no further insertions

    // else

    // place the new data at the next
    // empty position in the heap
    heap[++n] = data;

    int pos = n; // position of the new data
    int par = pos / 2; // position of its parent

    // move the new data to its appropriate place
    // by swaping it with its parent till its
    // parent is smaller than itself or it has
    // reaches the top of the heap.
    while (pos > 0 && heap[par] < heap[pos]) {
        swap(pos, par);
        pos = par;
        par = pos / 2;
    }

    // insert successful
    return SUCCESS;
}

// deletes an element from the root/top of the heap
int del()
{
    if (heapEmpty())
        return FAILURE; // no deletion possible

    // else

    // replace the root/top value with the
    // last value and delete the last value
    heap[0] = heap[n--];

    // Sink down the new root value to its
    // apt.place (to satisfy heap peoperty)
    // by swapping it with the bigger among
    // its children. Keep swapping till it
    // is smaller than either or both of its
    // children.

    // the value of the left child of node 'i'
    // is at the 2i th position in the array and
    // the value of its right child is at the
    // 2i+1 th position
    int pos = 0, L = 1, R = 2;

    for (;;) {
        // if pos has both children, and value at
        // pos is less than the value of either child
        if (L <= n && R <= n && (heap[pos] < heap[L] || heap[pos] < heap[R])) {
            // swap the value at pos with the child
            // that has a bigger value and that child
            // becomes the new pos
            if (heap[L] > heap[R]) {
                swap(L, pos);
                pos = L;
            } else {
                swap(R, pos);
                pos = R;
            }
        }

        // if pos has only the left child and its
        // value is less than that of the left child
        else if (L <= n && heap[pos] < heap[L]) {
            // swap the value at pos with the value
            // of the left child and the left child
            // becomes the new pos
            swap(L, pos);
            pos = L;
        }

        // lone right child doesn't occur in a heap
        // so we don't need to deal with that case

        else // we have reached a leaf
            return SUCCESS;

        // calculate the positions of the left and
        // the right child of the new pos
        L = 2 * pos;
        R = 2 * pos + 1;
    }
}

// returns the value of the root/top node of the heap
int top() { return heap[0]; }

//____________________________________________________
//           same as heap.c till here


// sorts the elements of A in descending order and
// puts them into B; both arrays must of the same 'size' 
void heapsort(int A[], int B[], int size)
{
    // heapify the elements
    for (int i = 0; i < size; ++i)
        ins(A[i]);

    // pop the top to get elements in desc. order
    for (int i = 0; i < size; ++i) {
        B[i] = top(); // store the elements in B[]
        del();
    }
}

//driver
void main(void)
{
    int
        A[] = { -10, 50, 100, 20, -30 },
        B[5];

    heapsort(A, B, 5);

    // print sorted
    for (int i = 0; i < 5; ++i)
        printf("%d ", B[i]);

    printf("\n");
}
