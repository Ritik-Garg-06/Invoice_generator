#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items
{
    char item[20];
    float price;
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

void generateBillBody(char *item, int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
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
void Generate_invoice(FILE *fp, struct orders ord)
{
    int numberofOrders = 0, n = 0, total = 0;
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
    fgets(ord.customer, 50, stdin);
    ord.customer[strlen(ord.customer) - 1] = '\0';

    strcpy(ord.date, __DATE__);

    printf("Please Enter the number of items:\t");
    scanf("%d", &n);
    ord.numOfItems = n;

    for (int i = 0; i < n; i++)
    {
        fgetc(stdin);
        printf("\n\nPlease Enter the item %d\t", i + 1);
        fgets(ord.itm[i].item, 20, stdin);
        ord.itm[i].item[strlen(ord.itm[i].item) - 1] = '\0';

        printf("\nPlease Enter the quantity of item:\t");
        scanf("%d", &ord.itm[i].qty);

        printf("\nPlease enter the unit price:\t");
        scanf("%f", &ord.itm[i].price);

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
    int searchby, billToFind, numberofOrders;
    char name[50];
    int invoiceFound = 0; // Move this declaration here

    printf("\nWant to search with Invoice Number or Name \n Press 1 For Invoice No and Press 2 For Name\t");
    scanf("%d", &searchby);
    getchar();

    if (searchby == 1)
    {
        printf("\nEnter the Invoice Number\t");
        scanf("%d", &billToFind);
        getchar();
    }
    else
    {
        printf("\nEnter the name of the Customer to Search:\t");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove newline character
    }

    system("cls");
    fp = fopen("RestaurentBill.txt", "rb");
    printf("\n\t *******Invoice of %s********", name);

    numberofOrders = 0;

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
    scanf("%d", &searchby);
    getchar();

    if (searchby == 1)
    {
        printf("\nEnter the Invoice Number\t");
        scanf("%d", &billToFind);
        getchar();
    }
    else
    {
        printf("\nEnter the name of the Customer to update:\t");
        fgets(name, 50, stdin);
        name[strlen(name) - 1] = 0;
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
            printf("Please Enter the number of items:\t");
            scanf("%d", &n);
            allOrders[i].numOfItems = n;

            for (int j = 0; j < n; j++)
            {
                fgetc(stdin);
                printf("\n\nPlease Enter the item %d\t", j + 1);
                fgets(allOrders[i].itm[j].item, 20, stdin);
                allOrders[i].itm[j].item[strlen(allOrders[i].itm[j].item) - 1] = '\0';

                printf("\nPlease Enter the quantity of item:\t");
                scanf("%d", &allOrders[i].itm[j].qty);

                printf("\nPlease enter the unit price:\t");
                scanf("%f", &allOrders[i].itm[j].price);

                total += allOrders[i].itm[j].qty * allOrders[i].itm[j].price;
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
    scanf("%d", &searchby);
    getchar();

    if (searchby == 1)
    {
        printf("\nEnter the Invoice Number\t");
        scanf("%d", &billToFind);
        getchar();
    }

    else
    {
        printf("\nEnter the name of the Customer to update:\t");
        fgets(name, 50, stdin);
        name[strlen(name) - 1] = 0;
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
        printf("\nSorry the Invoice of %s does not found\n", name);
}
