/*
 * Question 4: Bakery Festival Sales Management System
 * Uses loops, a one-dimensional array and user-defined functions.
 */
//Name:Muhammad Qasim Khan
//class:BDS-1A
//roll no.:26k-2529
#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 7

/* Safe integer input: re-asks if the user types something that is not a number. */
static int readInt(const char *prompt)
{
    int value, c;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1)
            return value;
        printf("Invalid input. Please enter a number.\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        if (c == EOF)
            exit(1);
    }
}

/* Safe float input. */
static float readFloat(const char *prompt)
{
    float value;
    int c;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1)
            return value;
        printf("Invalid input. Please enter a number.\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        if (c == EOF)
            exit(1);
    }
}

/* Keeps asking until the number of festival days is between 1 and 7. */
int getValidDays()
{
    int days;
    do
    {
        days = readInt("Enter number of festival days (1-7): ");
        if (days < 1 || days > MAX_DAYS)
            printf("Invalid! Days must be between 1 and 7.\n");
    } while (days < 1 || days > MAX_DAYS);
    return days;
}

/* Processes one day: inputs orders, displays statistics, returns total sales. */
float calculateDailySales(int dayNumber)
{
    int orders, i;
    float amount, total = 0, highest = 0;
    char prompt[60];

    printf("\n--- Day %d ---\n", dayNumber);

    do
    {
        orders = readInt("Number of orders: ");
        if (orders < 1)
            printf("There must be at least one order.\n");
    } while (orders < 1);

    for (i = 1; i <= orders; i++)
    {
        sprintf(prompt, "Amount of order %d (Rs.): ", i);
        amount = readFloat(prompt);
        while (amount <= 0)                    /* ask again for the SAME order */
        {
            printf("Invalid amount! It must be greater than zero.\n");
            amount = readFloat(prompt);
        }

        total += amount;
        if (amount > highest)
            highest = amount;
    }

    printf("Day %d total sales        : Rs. %.2f\n", dayNumber, total);
    printf("Day %d average order      : Rs. %.2f\n", dayNumber, total / orders);
    printf("Day %d highest order      : Rs. %.2f\n", dayNumber, highest);

    return total;
}

/* Returns the (1-based) day with the highest sales; earliest day wins ties. */
int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i, best = 0;
    for (i = 1; i < numberOfDays; i++)
        if (dailySales[i] > dailySales[best])   /* strictly greater keeps earliest */
            best = i;
    return best + 1;
}

/* One asterisk for every complete Rs. 100 of a day's sales. */
void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, stars;

    printf("\nDaily Sales Bar Chart (each * = Rs. 100)\n");
    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++)
            printf("*");
        printf("\n");
    }
}

int main()
{
    float dailySales[MAX_DAYS];
    float festivalTotal = 0;
    int numberOfDays, i, bestDay;

    numberOfDays = getValidDays();

    for (i = 0; i < numberOfDays; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    bestDay = findHighestSalesDay(dailySales, numberOfDays);

    printf("\n========== Festival Sales Summary ==========\n");
    printf("Total sales for the festival : Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales       : Day %d (Rs. %.2f)\n",
           bestDay, dailySales[bestDay - 1]);

    displayBarChart(dailySales, numberOfDays);

    return 0;
}
