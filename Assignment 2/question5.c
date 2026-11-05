/*
 * Question 5: University Library Management System
 * Menu-driven program using arrays, loops, conditions and user-defined functions.
 */
//Name:Muhammad Qasim Khan
//class:BDS-1A
//roll no.:26k-2529
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BORROW   3
#define STUDENT      1
#define FACULTY      2
#define WAIVER_CODE  "LIB2026"

/*  small safe-input helper  */
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

/* Displays all menu options. */
void displayMenu()
{
    printf("\n========= University Library =========\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("======================================\n");
}

/* Inputs and stores the member's registration details. */
void registerMember(char name[], int *studentID, int *memberType)
{
    printf("Enter member name: ");
    scanf(" %49[^\n]", name);

    do
    {
        *studentID = readInt("Enter student ID: ");
        if (*studentID <= 0)
            printf("Invalid ID. It must be a positive number.\n");
    } while (*studentID <= 0);

    do
    {
        *memberType = readInt("Membership type (1 = Student, 2 = Faculty): ");
        if (*memberType != STUDENT && *memberType != FACULTY)
            printf("Invalid membership type. Enter 1 or 2.\n");
    } while (*memberType != STUDENT && *memberType != FACULTY);

    printf("Registration successful. Allowed borrowing period: %d days.\n",
           *memberType == STUDENT ? 14 : 30);
}

/*  Displays all books in a table. */
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    int i;
    printf("\n%-8s %-35s %s\n", "Book ID", "Title", "Available Copies");
    printf("-------------------------------------------------------------\n");
    for (i = 0; i < totalBooks; i++)
        printf("%-8d %-35s %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
}

/*  Borrows a book after validating ID, availability and the 3-book limit. */
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    int id, days, i, index = -1;
    int allowed = (memberType == STUDENT) ? 14 : 30;

    if (*borrowedCount >= MAX_BORROW)
    {
        printf("Borrowing limit reached. You can borrow a maximum of %d books at a time.\n",
               MAX_BORROW);
        return;
    }

    id = readInt("Enter book ID: ");
    for (i = 0; i < totalBooks; i++)
        if (bookIDs[i] == id)
        {
            index = i;
            break;
        }

    if (index == -1)
    {
        printf("Invalid book ID.\n");
        return;
    }
    if (availableCopies[index] == 0)
    {
        printf("Sorry, no copies of \"%s\" are currently available.\n", bookTitles[index]);
        return;
    }

    do
    {
        days = readInt("Enter number of days you intend to keep the book: ");
        if (days <= 0)
            printf("Number of days must be positive.\n");
    } while (days <= 0);

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;

    printf("You borrowed \"%s\".\n", bookTitles[index]);
    if (days > allowed)
        printf("Note: your permitted period is %d days. Late fines apply after that.\n", allowed);
}

/*  Returns a book, calculates fine, applies waiver; returns fine payable now. */
float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    int id, days, i, pos = -1, index = -1;
    int allowed = (memberType == STUDENT) ? 14 : 30;
    int ratePerDay = (memberType == STUDENT) ? 20 : 10;
    float fine = 0, payable = 0;
    char code[30];

    if (*borrowedCount == 0)
    {
        printf("You have no borrowed books to return.\n");
        return 0;
    }

    id = readInt("Enter book ID to return: ");
    for (i = 0; i < *borrowedCount; i++)
        if (borrowedBookIDs[i] == id)
        {
            pos = i;
            break;
        }

    if (pos == -1)
    {
        printf("You have not borrowed a book with ID %d.\n", id);
        return 0;
    }

    do
    {
        days = readInt("Enter actual number of days the book was kept: ");
        if (days <= 0)
            printf("Number of days must be positive.\n");
    } while (days <= 0);

    /* increase the available copies */
    for (i = 0; i < totalBooks; i++)
        if (bookIDs[i] == id)
        {
            index = i;
            break;
        }
    if (index != -1)
        availableCopies[index]++;

    /* late fine */
    if (days > allowed)
    {
        fine = (float)(days - allowed) * ratePerDay;
        printf("Book returned %d day(s) late. Fine: Rs. %.2f\n", days - allowed, fine);

        *totalFine += fine;                 /* cumulative fine BEFORE waiver */

        printf("Enter membership code for fine waiver (or any text to skip): ");
        scanf("%29s", code);

        if (strcmp(code, WAIVER_CODE) == 0)
        {
            payable = fine * 0.5f;
            printf("Valid code! 50%% waiver applied.\n");
        }
        else
        {
            payable = fine;
            printf("Incorrect code. No waiver applied.\n");
        }
        printf("Fine payable for this return: Rs. %.2f\n", payable);
    }
    else
    {
        printf("Book returned on time. No fine.\n");
    }

    /* remove the book from the current borrowing list */
    for (i = pos; i < *borrowedCount - 1; i++)
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    (*borrowedCount)--;

    return payable;
}

/*  Displays the member's information and borrowing record. */
void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver)
{
    int i;
    printf("\n------------- Member Record -------------\n");
    printf("Name            : %s\n", name);
    printf("Student ID      : %d\n", studentID);
    printf("Membership type : %s\n", memberType == STUDENT ? "Student" : "Faculty");

    printf("Borrowed books  : ");
    if (borrowedCount == 0)
        printf("None");
    else
        for (i = 0; i < borrowedCount; i++)
            printf("%d ", borrowedBookIDs[i]);
    printf("\n");

    printf("Total fine (before waiver) : Rs. %.2f\n", totalFine);
    printf("Final fine payable         : Rs. %.2f\n", fineAfterWaiver);
    printf("-----------------------------------------\n");
}

int main()
{
    /* book inventory */
    int  bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {
        "Programming Fundamentals",
        "Data Structures",
        "Database Systems",
        "Discrete Mathematics",
        "Operating Systems"
    };
    int availableCopies[5] = {3, 2, 1, 4, 2};
    int totalBooks = 5;

    /* member record */
    char  name[50] = "";
    int   studentID = 0, memberType = 0;
    int   borrowedBookIDs[MAX_BORROW];
    int   borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0;
    int   registered = 0;
    int   choice;

    do
    {
        displayMenu();
        choice = readInt("Enter your choice: ");

        switch (choice)
        {
        case 1:
            if (registered && borrowedCount > 0)
            {
                printf("Please return all borrowed books before registering a new member.\n");
                break;
            }
            registerMember(name, &studentID, &memberType);
            registered = 1;
            borrowedCount = 0;
            totalFine = 0;
            fineAfterWaiver = 0;
            break;

        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
            break;

        case 3:
            if (!registered)
                printf("Please register first (option 1).\n");
            else
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                           borrowedBookIDs, &borrowedCount, memberType);
            break;

        case 4:
            if (!registered)
                printf("Please register first (option 1).\n");
            else
                fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks,
                                              borrowedBookIDs, &borrowedCount,
                                              memberType, &totalFine);
            break;

        case 5:
            if (!registered)
                printf("Please register first (option 1).\n");
            else
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs,
                                    borrowedCount, totalFine, fineAfterWaiver);
            break;

        case 6:
            printf("Thank you for using the library system. Goodbye!\n");
            break;

        default:
            printf("Invalid choice. Please select 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}
