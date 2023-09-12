#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct items
{
    char item[20]; // Item name
    int price;     // Item Price
    int qty;       // Item Quantity
};

// This is a layout how each item will be stored

struct orders
{
    char customer[50]; // Customer's Name
    char date[50];
    int numOfItems;
    struct items itm[50]; // Array for storing all items for a single order
};

// This is the layout for orders

// This Program will generate Bill Header
void generateBillHeader(char name[50], char date[30], int inv)
{
    printf("\n\n");
    printf("\t\tWalmart\t");
    printf("\n\t ----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\nInvoice No: %d", inv);
    printf("\n");
    printf("-----------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

// This Program willl generate Body of the bill
void generateBillBody(char *item, int qty, int price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * (float)price); // Price of items is Calculated
    printf("\n");
}

// Here tax and other charges are Calculated
void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total; // Discount is Calculated
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst; // Tax is Calculated
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
    printf("\n\tThanks for Shopping\n");
    printf("\tPlease Visit Again\n");
}

// This is the Start menu which gives option that which operation to choose
void StartMenu()
{
    printf("\t=================Walmart===================");

    printf("\n\nPlease Select your preferd operation");

    printf("\n\n\n1. Generate Invoice");
    printf("\n2. Show all Invoices");
    printf("\n3. Search Invoice");
    printf("\n4. Update Data");
    printf("\n5. Delete a Specific Record");
    printf("\n6. Clear Database");
    printf("\n7. Exit");
}

// Check if string contain any invalid character
int Invalid_String(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || str[i] == 32 || str[i] == 10))
            return 1;

        // If character is other than alphabet , blank space and \n it will return 1
    }
    return 0;
}

// This function is used to ask the user that whether the user wants to save the bill or not the functionality of this will be known later
char BillDone()
{
    char choice[50];
    printf("\n\nDo you want to save the bill? [y/n]\t");

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

// Repeatedly gives the prompt till the correct value is not entered for string
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

// Repeatedly gives the prompt till the correct value is not entered for Integer
int valid_int()
{
    int opt = 0;
    while (1)
    {
        if (scanf("%d", &opt) != 1)
        {
            printf("\nEnter a valid numeric input\n");
            while (getchar() != '\n'); // If Invalid Input clear input buffer
        }
        else
        {
            return opt; // In case of correct Input return the input
        }
    }
}

// This function is used to generate the invoice
void Generate_invoice(FILE *fp, struct orders ord)
{
    int numberofOrders = 0, total = 0, Invalid_Input = 0, n = 0;
    char saveBill;

    fp = fopen("RestaurentBill.txt", "rb"); // Open in binary read mode to check existing orders

    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END);                             // Take the file pointer to last position
        numberofOrders = ftell(fp) / sizeof(struct orders); // No of Orders id location of file pointer {which is last} divided by size of one order
    }

    fclose(fp);

    int inv = numberofOrders + 1; // As new Invoice no will be always one greater than number of orders already present

    printf("Please Enter the name of the Customer\n");

    strcpy(ord.customer, valid_String()); // As string is immutable so used strcpy to take input

    strcpy(ord.date, __DATE__); //__DATE__ is a predefined macro in C that represents the current compilation date as a string literal.

    printf("Please Enter the number of items\n");

    n = valid_int(); // total No of items for a single order is enterd here

    ord.numOfItems = n;
    for (int i = 0; i < n; i++)
    {
        fgetc(stdin);
        printf("\n\nPlease Enter the item %d\t", i + 1);

        strcpy(ord.itm[i].item, valid_String()); // Name of i th item is entered here

        // Here we have itm array as it can be more than one itm

        printf("\nPlease Enter the quantity of item:\t");

        ord.itm[i].qty = valid_int(); // Quantity of i th item is enterd here

        printf("\nPlease enter the unit price:\t");

        ord.itm[i].price = valid_int(); // Used for entering price of i th iitem

        total += ord.itm[i].qty * ord.itm[i].price;

        // Here we are inputting quantity of item [i] ans well as price of one piece for that item so here the total price for that item is calculated
    }

    // As all the inputs are taken now these are passed to generate the bill
    generateBillHeader(ord.customer, ord.date, inv);

    // this loop will run the no of items a single order have
    for (int i = 0; i < ord.numOfItems; i++)
        generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);

    generateBillFooter(total);

    // Here i am giving user option that if the bill is final do you want to save this bill in the database

    // Here the implementation of BillDone function comes which we discussed earlier

    saveBill = BillDone();

    // If user input is yes the bill will be saved in our database
    if (saveBill == 'Y' || saveBill == 'y')
    {
        fp = fopen("RestaurentBill.txt", "ab"); // Opening file in append mode to add our Bill to the database

        // In this case fwrite function is used to put input of ord into fp
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

// This function is used to show the previous invoices which are already present in the Database
// It is taking two things as input one is fp and other is allOrders we can take it also as without any formal parameter but in that case fp and allOrders are defined evertime we will run this function
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

    // This loop is used to know that there are total how many orders present in the database
    // It is working like it has a large database it counts the portion eith size struct orders
    while (fread(&allOrders[numberOfOrders], sizeof(struct orders), 1, fp))
    {
        numberOfOrders++;
    }

    fclose(fp);

    // As we get the total number of orders here data for each order is printed individually
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

// Suppose you want to search a Particular Invoice with invoice number or you want to search all the invoices of a particular person than this function will do your work
void SearchInvoice(FILE *fp, struct orders allOrders[])
{
    int searchby, billToFind, numberofOrders, Invalid_Input = 0;
    char name[50];
    int invoiceFound = 0; // This is the flag to check whether invoice is present or not initially it is set to invoice not present

    // Asking user whether want to search with invoice number or through name
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

    system("clear");
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

        // Here we have applied condition that if searchby is 1 and i+1 == billToFind {i+1} is our invoice number
        // if the searchby == 2 then we will traverse the database till ord.customer does not equals to the name which we have entered
        if ((searchby == 1 && i + 1 == billToFind) || (searchby == 2 && strcmp(allOrders[i].customer, name) == 0))
        {
            generateBillHeader(allOrders[i].customer, allOrders[i].date, i + 1);
            for (int j = 0; j < allOrders[i].numOfItems; j++)
            {
                generateBillBody(allOrders[i].itm[j].item, allOrders[i].itm[j].qty, allOrders[i].itm[j].price);
                tot += allOrders[i].itm[j].qty * allOrders[i].itm[j].price;
            }
            generateBillFooter(tot);

            // If Invoice found then the flag will be uppdated with value 1
            invoiceFound = 1;
        }
    }

    if (!invoiceFound) // if the value of flag remains 0 then it will give error
    {
        printf("\nSorry the Invoice of %s does not found\n", name);
    }
}

// If the user entered any incorrect data but the user wants to change that without changing the invoice number then in that case user can use this operation
void UpdateData(FILE *fp, struct orders allOrders[]) {
    int invoiceFound = 0, n = 0, total = 0, searchby = 0, billToFind = 0;
    char name[50];

    printf("\nWant to search with Invoice Number or Name \n Press 1 For Invoice No and Press 2 For Name\t");
    searchby = valid_int();
    getchar();

    if (searchby == 1) {
        printf("\nEnter the Invoice Number\t");
        billToFind = valid_int();
    }
    else if (searchby == 2) {
        printf("\nEnter the name of the Customer to Search:\t");
        strcpy(name, valid_String());
    }

    fp = fopen("RestaurentBill.txt", "rb");

    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    // Here we are creating a new temp.txt file to store the database with updated data as data is in structure form so we are opening file in binary mode
    FILE *fp1 = fopen("temp.txt", "wb");

    int numberofOrders = 0;

    while (fread(&allOrders[numberofOrders], sizeof(struct orders), 1, fp)) {
        numberofOrders++;
    }

    fclose(fp);

    for (int i = 0; i < numberofOrders; i++) {
        float tot = 0;

        if ((searchby == 1 && i + 1 == billToFind) || (searchby == 2 && !strcmp(allOrders[i].customer, name))) {
            invoiceFound = 1;
            printf("Please Enter the number of items\n");

            n = valid_int();

            allOrders[i].numOfItems = n;
            for (int j = 0; j < n; j++) {
                fgetc(stdin);
                printf("\n\nPlease Enter the item %d\t", j + 1);

                strcpy(allOrders[i].itm[j].item, valid_String());

                printf("\nPlease Enter the quantity of item:\t");

                allOrders[i].itm[j].qty = valid_int();

                printf("\nPlease enter the unit price:\t");

                allOrders[i].itm[j].price = valid_int();

                total += allOrders[i].itm[j].qty * allOrders[i].itm[j].price;
            }
        }

        // This command will run for each case irrespective of any condition
        // Here all the data of Restaurent.txt is being copied to temp.txt
        fwrite(&allOrders[i], sizeof(struct orders), 1, fp1);
    }

    fclose(fp1);

    if (invoiceFound == 1) {
        // As we got all the data in temp.txt so we will remove temp.txt from the system
        remove("RestaurentBill.txt");

        // As we are using RestaurentBill.txt everywhere so we will update the name of temp.txt to RestaurentBill.txt
        rename("temp.txt", "RestaurentBill.txt");

        // Message Printed if all the data is updated Sucessfully in the database
        printf("\nData Updated Successfully\n");
    }
    else {
        // If invoice Not found this error message will be printed on the terinal
        printf("\nSorry the Invoice not found\n");
    }
}

// If the user wanted to remove a particular invoice from the database from the system then this function is used
void DeleteRecord(FILE *fp, FILE *fp1, struct orders allOrders[])
{
    int invoiceFound = 0, searchby = 0, billToFind = 0;
    char name[50];

    printf("\nEnter the Invoice Number\t");
    billToFind = valid_int();

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
        if (i + 1 == billToFind)
            invoiceFound = 1;
        else
            fwrite(&allOrders[i], sizeof(struct orders), 1, fp1);
    }

    fclose(fp1);

    if (invoiceFound == 1)
    {
        remove("RestaurentBill.txt");

        rename("temp.txt", "RestaurentBill.txt");

        printf("\nData Updated Successfully\n");
    }
    else
        printf("\nSorry the Invoice not found\n");
}

// This function is used to maintain error handlin in character
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