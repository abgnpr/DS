#include <stdio.h>

// returns the nth fibonacci
int fib(int n)
{
    if (n == 0)  // base case 1
        return 0;
    if (n == 1)  // base case 2
        return 1;
    
    // recursive case
    return fib(n - 1) + fib(n - 2);
}

// driver
void main(void)
{   
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    printf("\n%dth fibonacci is: %d\n\n", n, fib(n));
}