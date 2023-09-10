#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

int main()
{
    struct orders ord;
    struct orders allOrders[50];
    char contflag = 'y';
    FILE *fp, *fp1;

    while (contflag == 'y')
    {

        StartMenu();

        int opt = 0;

        printf("\n\nYour Choice\t");

        opt = valid_int();

        getchar();

        switch (opt)
        {
        case 1:
            system("cls");
            Generate_invoice(fp, ord);
            break;

        case 2:
            system("cls");
            ShowInvoice(fp, allOrders);
            break;

        case 3:
            system("cls");
            SearchInvoice(fp, allOrders);
            break;

        case 4:
            system("cls");
            UpdateData(fp, allOrders);
            break;

        case 5:
            system("cls");
            DeleteRecord(fp, fp1, allOrders);
            break;

        case 6:
            system("cls");
            fp = fopen("RestaurentBill.txt", "w");
            fclose(fp);
            printf("\nData Cleared Sucessfully\n");
            break;

        case 7:
            system("cls");
            printf("\nThanks for using :)\n");
            exit(0);
            break;

        default:
            printf("Sorry Invalid Option");
            break;
        }

        contflag = ContinueOperation();
    }
    printf("\nThanks for using :)\n");

    return 0;
}