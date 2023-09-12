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

When you run the program, you will see a main menu with several options:

1) Generate Invoice: Create a new invoice.
2) Show all Invoices: View all previously generated invoices.
3) Search Invoice: Search for invoices by invoice number or customer name.
4) Update Data: Modify the details of an existing invoice.
5) Delete a Specific Record: Remove an invoice from the system.
6) Clear Database: Clear all stored invoices.
7) Exit: Quit the program.

1) Generating an Invoice
  To generate a new invoice, select option 1 and follow the prompts. You'll be asked for the customer's name, the number of items, and details for each item (item name, quantity, and unit price).

2) Viewing Invoices
  To view all previously generated invoices, select option 2. The program will display the details of each invoice, including the customer's name, date, and invoice number.

3)Searching for Invoices
  Option 3 allows you to search for invoices. You can search by invoice number or customer name. Enter the search criteria when prompted, and the program will display the matching invoices.

4) Updating Invoice Data
  If you need to update the details of an existing invoice, select option 4. You can search for the invoice by invoice number or customer name. After finding the invoice, you can modify the item details.

5) Deleting an Invoice
  To delete a specific invoice, choose option 5. Enter the invoice number you want to delete, and the program will remove it from the system.

6) Clearing the Database
  Option 6 allows you to clear all stored invoices. Use this option with caution, as it will permanently delete all data.

## Features
  Generate and manage invoices for a retail store.
  Search for invoices by invoice number or customer name.
  Update invoice data if errors are made.
  Delete specific invoices or clear the entire database.

## Contributing
Contributions are welcome! If you have any suggestions, improvements, or bug fixes, please open an issue or create a pull request.
