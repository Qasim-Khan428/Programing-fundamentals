/*
 * Question 1: Cinema Hall Seat Booking Management System
 * Uses a two-dimensional array .
 */
//Name:Muhammad Qasim Khan
//class:BDS-1A
//roll no.:26k-2529
#include <stdio.h>

#define MAX_ROWS  50
#define MAX_SEATS 50

int main(void)
{
    int hall[MAX_ROWS][MAX_SEATS];
    int rows, seats;
    int i, j;

    /*  Input seating plan */
    printf("Enter number of rows (1-%d): ", MAX_ROWS);
    if (scanf("%d", &rows) != 1 || rows < 1 || rows > MAX_ROWS)
    {
        printf("Invalid number of rows.\n");
        return 1;
    }

    printf("Enter number of seats per row (1-%d): ", MAX_SEATS);
    if (scanf("%d", &seats) != 1 || seats < 1 || seats > MAX_SEATS)
    {
        printf("Invalid number of seats.\n");
        return 1;
    }

    printf("\nEnter seat status (0 = available, 1 = booked):\n");
    for (i = 0; i < rows; i++)
    {
        printf("Row %d (%d values): ", i, seats);
        for (j = 0; j < seats; j++)
        {
            if (scanf("%d", &hall[i][j]) != 1 || (hall[i][j] != 0 && hall[i][j] != 1))
            {
                printf("Invalid seat status. Only 0 or 1 is allowed.\n");
                return 1;
            }
        }
    }

    /*  Display seating arrangement  */
    printf("\nSeating Arrangement (_ = available, X = booked)\n");
    printf("       ");
    for (j = 0; j < seats; j++)
        printf("%2d ", j);
    printf("\n");
    for (i = 0; i < rows; i++)
    {
        printf("Row %2d ", i);
        for (j = 0; j < seats; j++)
            printf(" %c ", hall[i][j] == 0 ? '_' : 'X');
        printf("\n");
    }

    /*  Seat availability report */
    int rowFree, totalFree = 0;
    printf("\nSeat Availability Report\n");
    for (i = 0; i < rows; i++)
    {
        rowFree = 0;
        for (j = 0; j < seats; j++)
            if (hall[i][j] == 0)
                rowFree++;
        printf("Row %d: %d available seat(s)\n", i, rowFree);
        totalFree += rowFree;
    }
    printf("Total available seats in the hall: %d\n", totalFree);

    /* Group booking input  */
    int k;
    printf("\nEnter number of customers to sit together (k): ");
    if (scanf("%d", &k) != 1 || k <= 0 || k > seats)
    {
        printf("Invalid group size. It must be greater than 0 and not more than %d.\n", seats);
        return 1;
    }

    /*  Search using the seat allocation rules  */
    int mid = rows / 2;
    int d, side, row, count;
    int found = 0, foundRow = -1, startSeat = -1;

    for (d = 0; d < rows && !found; d++)           /* distance from middle row */
    {
        for (side = 0; side < 2 && !found; side++)  /* side 0: smaller row first */
        {
            if (d == 0 && side == 1)
                continue;                           /* middle row checked only once */

            row = (side == 0) ? mid - d : mid + d;
            if (row < 0 || row >= rows)
                continue;

            count = 0;
            for (j = 0; j < seats; j++)
            {
                if (hall[row][j] == 0)
                {
                    count++;
                    if (count == k)
                    {
                        found = 1;
                        foundRow = row;
                        startSeat = j - k + 1;
                        break;
                    }
                }
                else
                {
                    count = 0;                      /* booked seat breaks the block */
                }
            }
        }
    }

    /* . Confirm booking / handle failure */
    if (found)
    {
        for (j = startSeat; j < startSeat + k; j++)
            hall[foundRow][j] = 1;

        printf("\nBooking confirmed!\n");
        printf("Allocated row: %d\n", foundRow);
        printf("Allocated seat numbers: ");
        for (j = startSeat; j < startSeat + k; j++)
            printf("%d ", j);
        printf("\n");

        printf("\nUpdated Seating Arrangement (_ = available, X = booked)\n");
        printf("       ");
        for (j = 0; j < seats; j++)
            printf("%2d ", j);
        printf("\n");
        for (i = 0; i < rows; i++)
        {
            printf("Row %2d ", i);
            for (j = 0; j < seats; j++)
                printf(" %c ", hall[i][j] == 0 ? '_' : 'X');
            printf("\n");
        }

        totalFree -= k;
        printf("\nRemaining available seats: %d\n", totalFree);
    }
    else
    {
        printf("\nSorry, no row has %d consecutive available seats. "
               "The seating plan is unchanged.\n", k);
    }

    return 0;
}
