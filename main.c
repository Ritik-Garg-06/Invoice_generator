#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "calc.h"

int main()
{
    struct orders ord;
    struct orders allOrders[50];
    char contflag = 'Y';
    FILE *fp, *fp1;

    while (contflag == 'y' || contflag == 'Y')
    {

        StartMenu();

        int opt = 0;

        printf("\n\nYour Choice\t");
        scanf("%d", &opt);
        getchar();

        switch (opt)
        {
        case 1:
            system("clear");
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
            UpdateData(fp, fp1, allOrders);
            break;

        case 5:
            system("clear");
            DeleteRecord(fp, fp1, allOrders);
            break;

        case 6:
            fp = fopen("RestaurentBill.txt", "w");
            fclose(fp);
            printf("\nData Cleared Sucessfully\n");
            break;

        case 7:
            printf("\nThanks for using :)\n");
            exit(0);
            break;

        default:

            printf("Sorry Invalid Option");
            break;
        }

        printf("\n\nDo you want to Perform another operation? [y/n]\t");
        scanf(" %c", &contflag);
    }
    printf("\nThanks for using :)\n");

    return 0;
}
