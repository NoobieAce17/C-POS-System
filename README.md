# Project Overview
Welcome to the Coffee Ko Cafe POS System! This project is a C++ implementation of a Point of Sale system designed for a fictional coffee shop, "Coffee Ko Cafe." The goal of this project is to showcase my understanding of C++ programming concepts, including data structures, file handling, and user interface design.

## Features
This POS system comes packed with several exciting features:

- Menu Management : Easily manage a menu of coffee drinks and pastries, complete with their prices.
- Order Processing : Customers can select items from various categories, choose beverage sizes, and specify quantities.
- Receipt Generation : The system generates detailed receipts with transaction information, including:
  - Transaction ID
  - Date and time
  - Customer name
  - Itemized list of purchases
  - Payment details
  - Change calculation for cash payments
- Transaction History : Authorized users can access a history of all transactions, complete with summary statistics.
- Visual Interface : Enjoy a colorful and user-friendly terminal interface, thanks to ANSI escape codes.
## Technical Implementation
Here's a look at the technical side of things:

- Utilizes C++ standard libraries
- Employs structs for organizing data (Item and Transaction)
- Uses vectors for dynamic data storage
- Incorporates time functions for transaction timestamps
- Leverages string manipulation for formatting
- Features ANSI escape codes for terminal styling
## How to Run
To get the POS system up and running, follow these steps:

1. Compile the Program :
   
   - Open a terminal or command prompt.
   - Navigate to the project directory.
   - Run the following command to compile the program:
     ```
     g++ main.cpp -o 
     pos_system
     ```
2. Execute the Program :
   
   - Run the compiled executable:
     ```
     ./pos_system
     ```
3. Using the System :
   
   - Enter the customer's name when prompted.
   - Select items from the menu categories (Coffee or Pastries).
   - Choose specific items, sizes, and quantities.
   - Complete the order and select a payment method.
   - View the generated receipt.
   - For admin functions, use the password "admin123" when prompted.
