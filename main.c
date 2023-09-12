#include <stdio.h>  // Standard Input/Output library for basic I/O operations
#include <stdlib.h> // Standard library for dynamic memory allocation functions like calloc and malloc
#include <string.h> // Standard library for string manipulation functions
#include <ctype.h>  // Standard library for character classification functions
#include "calc.h"   // Library to include the functions which are used in this

int main()
{
    struct orders ord;           // This is used to take input of a single order in Generate Invoice fuction
    struct orders allOrders[50]; // This structure is used in function when user is reading data from file and storing it in this here we have set the invoices limit to 50 but can increase or decrease it with our ease
    char contflag = 'y';
    FILE *fp, *fp1; // Used to handle file fp is for RestaurentBill.txt and fp1 is for temp.txt

    while (contflag == 'y')
    {

        StartMenu();

        int opt = 0;

        printf("\n\nYour Choice\t");

        opt = valid_int(); // Asked from user that which operation to perform;

        getchar();

        switch (opt)
        {
        case 1:
            system("clear"); // This is used to clear the terminal
            Generate_invoice(fp, ord);
            break;

        case 2:
            system("clear");
            ShowInvoice(fp, allOrders);
            break;

        case 3:
            system("clear");
            SearchInvoice(fp, allOrders);
            break;

        case 4:
            system("clear");
            UpdateData(fp, allOrders);
            break;

        case 5:
            system("clear");
            DeleteRecord(fp, fp1, allOrders);
            break;

        case 6:
            system("clear");
            // This operation is for clearing the database for clearing we will open the file in write mode and then the data of fill will automatically cleared

            fp = fopen("RestaurentBill.txt", "w");
            fclose(fp);
            printf("\nData Cleared Sucessfully\n");
            break;

        case 7:
            system("clear");
            // Used to exit from the program
            printf("\nThanks for using :)\n");
            exit(0);
            break;

        default:
            // If user enters any number except numbers from 0-7
            printf("Sorry Invalid Option");
            break;
        }

        contflag = ContinueOperation();
    }
    printf("\nThanks for using :)\n");

    // Program Ended

    return 0;
}