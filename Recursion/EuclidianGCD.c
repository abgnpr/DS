#include <stdio.h>

// returns the GCD of a and b
int GCD(int a, int b)
{
    if (a % b == 0) // base case
        return b;

    return GCD(b, a % b); // recursive case
}

// driver
void main(void)
{
    printf("GCD of 62 and 8 = %d\n", GCD(62, 8));
}