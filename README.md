## Project Overview
This is my C++ implementation of a Point of Sale (POS) system for a fictional coffee shop called "Coffee Ko Cafe". I created this project to demonstrate my understanding of C++ programming concepts including data structures, file handling, and user interface design.

## Features
I've implemented several key features in this POS system:

- Menu Management : The system includes a menu of coffee drinks and pastries with their respective prices.
- Order Processing : Customers can select items from different categories, choose sizes for beverages, and specify quantities.
- Receipt Generation : The system generates stylized receipts with transaction details, including:
  - Transaction ID
  - Date and time
  - Customer name
  - Itemized list of purchases
  - Payment information
  - Change calculation for cash payments
- Transaction History : Authorized users can view a history of all transactions with summary statistics.
- Visual Interface : I used ANSI escape codes to create a colorful and user-friendly terminal interface.
## Technical Implementation
For this project, I used:

- C++ standard libraries
- Structs for data organization (Item and Transaction)
- Vectors for dynamic data storage
- Time functions for transaction timestamps
- String manipulation for formatting
- ANSI escape codes for terminal styling
