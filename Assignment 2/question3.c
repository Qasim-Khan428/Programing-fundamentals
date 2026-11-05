/*
 * Question 3: Greenhouse Temperature Monitoring System
 * Uses a 2D array (rows = sensors, columns = hourly readings) .
 */
//Name:Muhammad Qasim Khan
//class:BDS-1A
//roll no.:26k-2529
#include <stdio.h>

#define MAX_SENSORS  20
#define MAX_READINGS 48

/* Inputs every temperature reading into the 2D array. */
void inputReadings(float temp[][MAX_READINGS], int sensors, int readings)
{
    int s, r;
    for (s = 0; s < sensors; s++)
    {
        printf("Sensor %d - enter %d readings: ", s + 1, readings);
        for (r = 0; r < readings; r++)
            scanf("%f", &temp[s][r]);
    }
}

/* Analyses the readings of ONE sensor; results are returned through pointers. */
void analyzeSensor(float readings[], int count,
                   float *total, float *average, float *highest, float *lowest,
                   int *critical, int *warning, int *longestStreak)
{
    int i, streak = 0;

    *total = 0;
    *highest = readings[0];
    *lowest = readings[0];
    *critical = 0;
    *warning = 0;
    *longestStreak = 0;

    for (i = 0; i < count; i++)
    {
        *total += readings[i];

        if (readings[i] > *highest)
            *highest = readings[i];
        if (readings[i] < *lowest)
            *lowest = readings[i];

        if (readings[i] >= 40)
            (*critical)++;
        else if (readings[i] >= 35)          /* 35 <= t < 40 */
            (*warning)++;

        if (readings[i] >= 35)               /* streak of hot hours */
        {
            streak++;
            if (streak > *longestStreak)
                *longestStreak = streak;
        }
        else
        {
            streak = 0;                      /* reading below 35 ends the streak */
        }
    }

    *average = *total / count;
}

/* Returns the sensor number (starting at 1) with the highest average;
   the winning average is returned through bestAverage. */
int findHighestAverageSensor(float temp[][MAX_READINGS], int sensors, int readings,
                             float *bestAverage)
{
    int s, r, bestSensor = 0;
    float sum, avg;

    *bestAverage = -1e9f;
    for (s = 0; s < sensors; s++)
    {
        sum = 0;
        for (r = 0; r < readings; r++)
            sum += temp[s][r];
        avg = sum / readings;

        if (avg > *bestAverage)
        {
            *bestAverage = avg;
            bestSensor = s + 1;
        }
    }
    return bestSensor;
}

int main(void)
{
    float temp[MAX_SENSORS][MAX_READINGS];
    int sensors, readings, s;

    printf("Enter number of sensors (1-%d): ", MAX_SENSORS);
    if (scanf("%d", &sensors) != 1 || sensors < 1 || sensors > MAX_SENSORS)
    {
        printf("Invalid number of sensors.\n");
        return 1;
    }

    printf("Enter number of hourly readings (1-%d): ", MAX_READINGS);
    if (scanf("%d", &readings) != 1 || readings < 1 || readings > MAX_READINGS)
    {
        printf("Invalid number of readings.\n");
        return 1;
    }

    inputReadings(temp, sensors, readings);

    printf("\n========== Individual Sensor Reports ==========\n");
    for (s = 0; s < sensors; s++)
    {
        float total, average, highest, lowest;
        int critical, warning, streak;

        analyzeSensor(temp[s], readings, &total, &average, &highest, &lowest,
                      &critical, &warning, &streak);

        printf("\nSensor %d\n", s + 1);
        printf("  Total of readings        : %.2f\n", total);
        printf("  Average temperature      : %.2f\n", average);
        printf("  Highest temperature      : %.2f\n", highest);
        printf("  Lowest temperature       : %.2f\n", lowest);
        printf("  Critical readings (>=40) : %d\n", critical);
        printf("  Warning readings (35-39) : %d\n", warning);
        printf("  Longest streak (>=35)    : %d hour(s)\n", streak);
    }

    float bestAvg;
    int bestSensor = findHighestAverageSensor(temp, sensors, readings, &bestAvg);

    printf("\n================ Final Report ================\n");
    printf("Sensor with the highest average temperature: Sensor %d\n", bestSensor);
    printf("Its average temperature: %.2f\n", bestAvg);

    return 0;
}
