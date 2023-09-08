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

void generateBillHeader(char name[50], char date[30], int inv);
void DeleteRecord(FILE *fp, FILE *fp1, struct orders allOrders[]);
void UpdateData(FILE *fp, FILE *fp1, struct orders allOrders[]);
void SearchInvoice(FILE *fp, struct orders allOrders[]);
void ShowInvoice(FILE *fp, struct orders allOrders[]);
void Generate_invoice(FILE *fp, struct orders ord);
void StartMenu();
void generateBillFooter(float total);
void generateBillBody(char *item, int qty, float price);
