#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int findBiggest(int A[], int n)
{
    int biggest = A[0];
    for (int i = 1; i < n; ++i)
        if (A[i] > biggest)
            biggest = A[i];

    return biggest;
}

int digits(int N)
{
    N = abs(N);
    int nd = 1;
    while ((N /= 10) > 0)
        nd++;

    return nd;
}

int digitAt(int pos, int N) { return (N / (int)pow(10, pos)) % 10; }

#define SIZE 10

void radixSort(int A[], int n)
{
    int bucket[SIZE][SIZE], bucketCount[SIZE];
    int nod = digits(findBiggest(A, n)); // digits in the biggest number

    for (int pass = 0; pass <= nod; ++pass)
    {
        for (int i = 0; i < SIZE; ++i)
            bucketCount[i] = 0;

        for (int i = 0; i < SIZE; ++i)
        {
            int digit = digitAt(pass, A[i]);
            bucket[digit][bucketCount[digit]] = A[i];
            bucketCount[digit]++;
        }

        // collect
        for (int i = 0, k = 0; i < SIZE; ++i)
            for (int j = 0; j < bucketCount[i]; ++j)
                A[k++] = bucket[i][j];
    }
}

void main(void)
{
    int A[] = {346, 654, 924, 123, 567, 472, 555, 808, 911};
    int n = sizeof A / sizeof *A;

    radixSort(A, n);

    for (int i = 0; i < n; ++i)
        printf("%d ", A[i]);
    printf("\n");
}