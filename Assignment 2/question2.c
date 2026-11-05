/*
 * Question 2 (Part A): Amicable Pairs
 * Displays all amicable pairs (a, b) with a < b and both <= n.
 */
//Name:Muhammad Qasim Khan
//class:BDS-1A
//roll no.:26k-2529
#include <stdio.h>

/* Returns the sum of the proper divisors of x (all divisors except x itself). */
int sumProperDivisors(int x)
{
    int i, sum;

    if (x < 2)
        return 0;               /* 1 (and below) has no proper divisors */

    sum = 1;                    /* 1 is a proper divisor of every x > 1 */
    for (i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            sum += i;           /* the small divisor */
            if (i != x / i)     /* do not add a square-root divisor twice */
                sum += x / i;   /* the matching large divisor (never x itself) */
        }
    }
    return sum;
}

int main(void)
{
    int n, a, b;
    int pairCount = 0;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 1)
    {
        printf("Invalid input. n must be a positive integer.\n");
        return 1;
    }

    printf("\nAmicable pairs with both numbers <= %d:\n", n);

    for (a = 2; a <= n; a++)
    {
        b = sumProperDivisors(a);

        /* b > a  -> smaller number first, each pair shown once,
                     and excludes perfect numbers (b == a) such as 6 and 28 */
        if (b > a && b <= n && sumProperDivisors(b) == a)
        {
            printf("(%d, %d)\n", a, b);
            pairCount++;
        }
    }

    if (pairCount == 0)
        printf("No amicable pairs were found.\n");
    else
        printf("\nTotal amicable pairs found: %d\n", pairCount);

    return 0;
}
