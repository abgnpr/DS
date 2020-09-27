#include <stdio.h>

/* searches N in the sorted sequence of NUMBERS 
having length LEN; returns the position of N if found,
-1 otherwise */
int binarySearch(int n, int numbers[], int len)
{
    int lo = 0, hi = len - 1, mid;

    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (n < numbers[mid])
            hi = mid - 1;
        else if (n > numbers[mid])
            lo = mid + 1;
        else
            return mid; // found match
    }

    return -1; // no match
}

// driver
void main(void)
{
    int numbers[] = {-10, 12, 25, 47, 100}; // pre-sorted
    int len = 5;

    int n = 100;
    int pos = binarySearch(n, numbers, len);

    if (pos == -1)
        printf("Not found!\n");
    else
        printf("Found %d at position: %d\n", n, pos);
}