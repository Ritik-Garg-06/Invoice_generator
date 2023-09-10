#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct items
{
    char item[20];
    int price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50], char date[30], int inv)
{
    printf("\n\n");
    printf("\t   ADV. Restaurent");
    printf("\n\t ----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\nInvoice To: %d", inv);
    printf("\n");
    printf("-----------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

void generateBillBody(char *item, int qty, int price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * (float)price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;
    printf("--------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t---------------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------");
}

void StartMenu()
{
    printf("\t=================ADV Restaurent===================");

    printf("\n\nPlease Select your preferd operation");

    printf("\n\n\n1. Generate Invoice");
    printf("\n2. Show all Invoices");
    printf("\n3. Search Invoice");
    printf("\n4. Update Data");
    printf("\n5. Delete a Specific Record");
    printf("\n6. Clear Database");
    printf("\n7. Exit");
}

int Invalid_String(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || str[i] == 32 || str[i] == 10))
            return 1;
    }
    return 0;
}

char *valid_String()
{
    char *temp = (char *)malloc(100 * sizeof(char));
    while (1)
    {
        if (fgets(temp, 100, stdin) != NULL)
        {
            temp[strcspn(temp, "\n")] = '\0'; // Remove newline character

            if (Invalid_String(temp) == 1)
            {
                printf("\nInvalid String Please Enter a valid String\n");
            }
            else
            {
                return temp;
            }
        }
        else
        {
            printf("\nError reading input.\n");
            free(temp);
            exit(1); // Handle input error
        }
    }
}

int valid_int()
{
    int opt = 0;
    while (1)
    {
        if (scanf("%d", &opt) != 1)
        {
            printf("\nEnter a valid numeric input\n");
            while (getchar() != '\n')
                ;
        }
        else
        {
            return opt;
        }
    }
}

void Generate_invoice(FILE *fp, struct orders ord)
{
    int numberofOrders = 0, total = 0, Invalid_Input = 0, n = 0;
    char saveBill;

    fp = fopen("RestaurentBill.txt", "rb"); // Open in binary read mode to check existing orders

    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        numberofOrders = ftell(fp) / sizeof(struct orders);
        fclose(fp);
    }

    int inv = numberofOrders + 1;

    printf("Please Enter the name of the Customer\n");

    strcpy(ord.customer, valid_String());

    strcpy(ord.date, __DATE__);

    printf("Please Enter the number of items\n");

    n = valid_int();

    ord.numOfItems = n;
    for (int i = 0; i < n; i++)
    {
        fgetc(stdin);
        printf("\n\nPlease Enter the item %d\t", i + 1);

        strcpy(ord.itm[i].item, valid_String());

        printf("\nPlease Enter the quantity of item:\t");

        ord.itm[i].qty = valid_int();

        printf("\nPlease enter the unit price:\t");

        ord.itm[i].price = valid_int();

        total += ord.itm[i].qty * ord.itm[i].price;
    }

    generateBillHeader(ord.customer, ord.date, inv);

    for (int i = 0; i < ord.numOfItems; i++)
        generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);

    generateBillFooter(total);

    printf("\nDo you want to save the Bill [Y/N]\n");
    scanf(" %c", &saveBill);

    if (saveBill == 'Y' || saveBill == 'y')
    {
        fp = fopen("RestaurentBill.txt", "ab"); // Open in binary append mode
        fwrite(&ord, sizeof(struct orders), 1, fp);

        if (fwrite != 0)
        {
            printf("\nSuccessfully Saved");
        }
        else
        {
            printf("\nError Saving");
        }
        fclose(fp);
    }
}

void ShowInvoice(FILE *fp, struct orders allOrders[])
{

    fp = fopen("RestaurentBill.txt", "rb");

    if (fp == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return;
    }

    printf("\n\t *******Your Previous Invoices********");

    int numberOfOrders = 0;

    while (fread(&allOrders[numberOfOrders], sizeof(struct orders), 1, fp))
    {
        numberOfOrders++;
    }

    fclose(fp);

    for (int i = 0; i < numberOfOrders; i++)
    {
        float tot = 0;
        generateBillHeader(allOrders[i].customer, allOrders[i].date, i + 1);
        for (int j = 0; j < allOrders[i].numOfItems; j++)
        {
            generateBillBody(allOrders[i].itm[j].item, allOrders[i].itm[j].qty, allOrders[i].itm[j].price);
            tot += allOrders[i].itm[j].qty * allOrders[i].itm[j].price;
        }
        generateBillFooter(tot);
    }
}

void SearchInvoice(FILE *fp, struct orders allOrders[])
{
    int searchby, billToFind, numberofOrders, Invalid_Input = 0;
    char name[50];
    int invoiceFound = 0; // Move this declaration here

    printf("\nWant to search with Invoice Number or Name \n Press 1 For Invoice No and Press 2 For Name\t");
    searchby = valid_int();
    getchar();

    if (searchby == 1)
    {
        printf("\nEnter the Invoice Number\t");
        billToFind = valid_int();
    }
    else if (searchby == 2)
    {
        printf("\nEnter the name of the Customer to Search:\t");
        strcpy(name, valid_String());
    }

    system("cls");
    fp = fopen("RestaurentBill.txt", "rb");

    numberofOrders = 0;

    while (fread(&allOrders[numberofOrders], sizeof(struct orders), 1, fp))
    {
        numberofOrders++;
    }

    fclose(fp);

    for (int i = 0; i < numberofOrders; i++)
    {
        float tot = 0;
        if ((searchby == 1 && i + 1 == billToFind) || (searchby == 2 && strcmp(allOrders[i].customer, name) == 0))
        {
            generateBillHeader(allOrders[i].customer, allOrders[i].date, i + 1);
            for (int j = 0; j < allOrders[i].numOfItems; j++)
            {
                generateBillBody(allOrders[i].itm[j].item, allOrders[i].itm[j].qty, allOrders[i].itm[j].price);
                tot += allOrders[i].itm[j].qty * allOrders[i].itm[j].price;
            }
            generateBillFooter(tot);
            invoiceFound = 1;
        }
    }

    if (!invoiceFound) // Move this check here, after going through all orders
    {
        printf("\nSorry the Invoice of %s does not found\n", name);
    }
}

void UpdateData(FILE *fp, struct orders allOrders[])
{
    int invoiceFound = 0, n = 0, total = 0, searchby = 0, billToFind = 0;
    char name[50];

    printf("\nWant to search with Invoice Number or Name \n Press 1 For Invoice No and Press 2 For Name\t");
    searchby = valid_int();
    getchar();

    if (searchby == 1)
    {
        printf("\nEnter the Invoice Number\t");
        billToFind = valid_int();
    }
    else if (searchby == 2)
    {
        printf("\nEnter the name of the Customer to Search:\t");
        strcpy(name, valid_String());
    }

    // Open the file in read mode to check existing orders
    fp = fopen("RestaurentBill.txt", "rb");

    if (fp == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return;
    }

    FILE *fpTemp = fopen("temp.txt", "wb"); // Open the temporary file in write mode

    int numberofOrders = 0;

    while (fread(&allOrders[numberofOrders], sizeof(struct orders), 1, fp))
    {
        numberofOrders++;
    }

    fclose(fp);

    for (int i = 0; i < numberofOrders; i++)
    {
        float tot = 0;

        if ((searchby == 1 && i + 1 == billToFind) || (searchby == 2 && !strcmp(allOrders[i].customer, name)))
        {
            invoiceFound = 1;
            printf("Please Enter the number of items\n");

            n = valid_int();

            allOrders[i].numOfItems = n;
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\nPlease Enter the item %d\t", i + 1);

                strcpy(allOrders[i].itm[i].item, valid_String());

                printf("\nPlease Enter the quantity of item:\t");

                allOrders[i].itm[i].qty = valid_int();

                printf("\nPlease enter the unit price:\t");

                allOrders[i].itm[i].price = valid_int();

                total += allOrders[i].itm[i].qty * allOrders[i].itm[i].price;
            }
        }

        fwrite(&allOrders[i], sizeof(struct orders), 1, fpTemp);
    }

    fclose(fpTemp);

    if (invoiceFound == 1)
    {
        // Remove the original file
        remove("RestaurentBill.txt");

        // Rename the temporary file to the original file name
        rename("temp.txt", "RestaurentBill.txt");

        printf("\nData Updated Successfully\n");
    }
    else
    {
        printf("\nSorry the Invoice of %s does not found\n", name);
    }
}

void DeleteRecord(FILE *fp, FILE *fp1, struct orders allOrders[])
{
    int invoiceFound = 0, searchby = 0, billToFind = 0;
    char name[50];

    printf("\nWant to search with Invoice Number or Name \n Press 1 For Invoice No and Press 2 For Name\t");
    searchby = valid_int();
    getchar();

    if (searchby == 1)
    {
        printf("\nEnter the Invoice Number\t");
        billToFind = valid_int();
    }
    else if (searchby == 2)
    {
        printf("\nEnter the name of the Customer to Search:\t");
        strcpy(name, valid_String());
    }

    fp = fopen("RestaurentBill.txt", "rb");
    fp1 = fopen("temp.txt", "wb");

    int numberofOrders = 0;

    while (fread(&allOrders[numberofOrders], sizeof(struct orders), 1, fp))
    {
        numberofOrders++;
    }

    fclose(fp);

    for (int i = 0; i < numberofOrders; i++)
    {
        if ((searchby == 1 && i + 1 == billToFind) || (searchby == 2 && !strcmp(allOrders[i].customer, name)))
            invoiceFound = 1;
        else
            fwrite(&allOrders[i], sizeof(struct orders), 1, fp1);
    }

    fclose(fp1);

    if (invoiceFound == 1)
    {
        numberofOrders--;
        fp1 = fopen("temp.txt", "rb");
        fp = fopen("RestaurentBill.txt", "wb");

        for (int i = 0; i < numberofOrders; i++)
        {
            fread(&allOrders[i], sizeof(struct orders), 1, fp1);
            fwrite(&allOrders[i], sizeof(struct orders), 1, fp);
        }

        printf("\nData Updated Successfully\n");

        fclose(fp);
        fclose(fp1);
    }
    else
        printf("\nSorry the Invoice not found\n");
}

char ContinueOperation()
{
    char choice[50];
    printf("\n\nDo you want to perform another operation? [y/n]\t");

    while (1)
    {
        scanf(" %s", choice);

        if (strlen(choice) == 1)
        {
            if (choice[0] == 'y' || choice[0] == 'Y')
            {
                return 'y';
            }
            else if (choice[0] == 'n' || choice[0] == 'N')
            {
                return 'n';
            }
        }

        printf("Invalid input. Please enter 'y' or 'n': ");
    }
}
