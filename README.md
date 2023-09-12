## Walmart Billing System
The Walmart Billing System is a command-line application written in C that helps manage invoices for a retail store. It allows you to generate, view, search, update, and delete invoices. This README provides instructions on how to use the program effectively.

## Table of Contents

  Installation
  Usage
  Features
  Contributing

## Installation
1) Clone the repository to your local machine using the following command:
```bash
  git clone https://github.com/Ritik-Garg-06/Invoice_generator.git
```
2) Compile the C program using a C compiler like GCC:
```bash
  gcc main.c -o walmart_billing
```
3) Run the program:
```bash
  ./walmart_billing
```
## Usage
  When you run the Walmart Billing System program, you will encounter a user-friendly main menu offering various options for efficiently managing your invoices:
  
 1. Generate Invoice: Create a new invoice for a customer. You'll be prompted to enter the customer's name, the number of items in the invoice, and details for each item, including the item name, quantity, and unit price.
  
 2. Show all Invoices: Easily access a list of previously generated invoices. This feature provides a comprehensive view of essential invoice information, including the customer's name, date, and invoice number.
  
 3. Search Invoice: Option 3 enables you to search for invoices with precision. You have the choice to search by either invoice number or customer name. Simply input your search criteria when prompted, and the program will display the matching invoices.
  
 4. Update Data: Modify the details of an existing invoice as needed. You can initiate the search for the specific invoice using either its invoice number or the customer's name. Once located, you can effortlessly adjust the item details.
  
 5. Delete a Specific Record: Remove a particular invoice from the system. Enter the invoice number associated with the invoice you wish to delete, and the program will promptly remove it from your records.
  
 6. Clear Database: Choose option 6 to clear all stored invoices from the database. Please exercise caution when using this option, as it will permanently erase all data, making it irretrievable.
  
 7. Exit: To gracefully exit the program, select this option. It allows you to conclude your billing activities with ease.
  
  The Walmart Billing System simplifies your invoice management tasks, offering a range of features to enhance your retail store's efficiency.

## Features
  Generate and manage invoices for a retail store.
  Search for invoices by invoice number or customer name.
  Update invoice data if errors are made.
  Delete specific invoices or clear the entire database.

## Contributing
Contributions are welcome! If you have any suggestions, improvements, or bug fixes, please open an issue or create a pull request.
