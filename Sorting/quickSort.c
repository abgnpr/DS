#include <stdio.h>
#include <stdbool.h>

void swap(int A[], int p, int q)
{
    int temp = A[p];
    A[p] = A[q];
    A[q] = temp;
}

int partition(int A[], int beg, int end)
{
    int left = beg, right = end;
    int loc = beg;
    bool flag = false;

    while (!flag)
    {
        while (A[loc] <= A[right] && loc != right)
            right -= 1;

        if (loc == right)
            flag = true;
        else if (A[loc] > A[right]) {
            swap(A, loc, right);
            loc = right;
        }

        if (!flag)
        {
            while (A[left] <= A[loc] && loc != left)
                left += 1;

            if (loc == left)
                flag = true;
            else if (A[left] > A[loc]) {
                swap(A, loc, left);
                loc = left;
            }
        }
    }

    return loc;
}

void quickSort(int A[], int beg, int end)
{
    if (beg < end) {
        int loc = partition(A, beg, end);
        quickSort(A, beg, loc - 1);
        quickSort(A, loc + 1, end);
    }
}

void main(void)
{
    int A[] = {21, 34, 11, 9, 1, 0, 22};
    int n = 7;

    quickSort(A, 0, n - 1);

    // print
    for (int i = 0; i < n; ++i)
        printf("%d ", A[i]);
    printf("\n");
}