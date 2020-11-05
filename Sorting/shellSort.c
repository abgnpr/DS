#include <stdio.h>
#include <stdbool.h>

void shellSort(int A[], int n)
{
    bool flag = true;
    int gap = n;
    while (flag || gap > 1)
    {
        flag = true;
        gap = (gap + 1) / 2;
        for (int i = 0; i < n - gap; ++i)
        {
            if (A[i + gap] < A[i])
            {
                int temp = A[i + gap];
                A[i + gap] = A[i];
                A[i] = temp;
                flag = false;
            }
        }
    }
}

void main(void)
{
    int A[] = {346, 654, 924, 123, 567, 472, 555, 808, 911};
    int n = sizeof A / sizeof *A;

    shellSort(A, n);

    for (int i = 0; i < n; ++i)
        printf("%d ", A[i]);
    printf("\n");
}
