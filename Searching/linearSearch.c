#include <stdio.h>

/* searches N in NUMBERS of length LEN;
returns the position of N if found, -1 otherwise */
int linearSearch(int number, int numbers[], int len)
{
    for (int pos = 0; pos < len; pos++)
        if (number == numbers[pos])
            return pos;

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
