#include <stdio.h>

/* searches N in NUMBERS of length LEN;
returns the position of N if found, -1 otherwise */
int seqSearch(int n, int numbers[], int len)
{
    for (int i = 0; i < len; i++)
        if (n == numbers[i])
            return i;

    return -1;
}

// driver
void main(void)
{
    int numbers[] = {25, 47, 12, -10, 100};
    int len = 5;

    int n = 12;
    int pos = seqSearch(n, numbers, len);

    if (pos == -1)
        printf("Not found!\n");
    else
        printf("Found %d at position: %d\n", n, pos);
}
