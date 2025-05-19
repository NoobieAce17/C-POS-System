#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// ANSI Escape Codes for Colors and Formatting
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"
#define BG_BLACK "\033[40m"

// Item structure to store product details
struct Item {
    string name;
    int quantity;
    double price;
    string size;
};

// Transaction structure to store order details
struct Transaction {
    string customerName;
    vector<Item> items;
    double totalBill;
    string paymentMode;
    double cashReceived;
    double change;
    time_t timestamp;
    string transactionId;
};

// Global variables
vector<Transaction> transactions;

// Function to generate a unique transaction ID
string generateTransactionId() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", localTime);
    return string("TRX") + buffer;
}

// Function to display current date and time
void displayCurrentDateTime(ostream& os) {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char dateBuffer[80];
    strftime(dateBuffer, sizeof(dateBuffer), "%B %d, %Y %I:%M %p", localTime);
    os << dateBuffer;
}

// Function to print a stylish receipt
void printReceipt(const Transaction& trans) {
    system("cls"); // Clear screen for better presentation
    
    cout << CYAN << BOLD << "\n╔═══════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << BOLD << "║" << BG_BLACK << WHITE << BOLD << "           COFFEE KO CAFE RECEIPT           " << RESET << CYAN << BOLD << "║" << RESET << endl;
    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════╝" << RESET << endl;
    
    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << " Transaction ID: " << BOLD << trans.transactionId << RESET << endl;
    cout << CYAN << "│" << RESET << " Date: ";
    displayCurrentDateTime(cout);
    cout << endl;
    cout << CYAN << "│" << RESET << " Customer: " << BOLD << trans.customerName << RESET << endl;
    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
    
    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << BOLD << " PURCHASED ITEMS" << RESET << endl;
    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
    cout << CYAN << "│" << RESET << left << setw(4) << " #" << setw(16) << "Item" << setw(8) << "Size" << setw(5) << "Qty" << setw(10) << "Price" << "Subtotal" << endl;
    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
    
    int itemNum = 1;
    for (const auto& item : trans.items) {
        double subtotal = item.price * item.quantity;
        cout << CYAN << "│" << RESET << " " << left << setw(3) << itemNum++
             << setw(16) << item.name
             << setw(8) << item.size
             << setw(5) << item.quantity
             << "P" << setw(9) << fixed << setprecision(2) << item.price
             << "P" << setw(8) << fixed << setprecision(2) << subtotal << endl;
    }
    
    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
    
    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << BOLD << " PAYMENT DETAILS" << RESET << endl;
    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
    cout << CYAN << "│" << RESET << " Total Amount: " << BOLD << "P" << fixed << setprecision(2) << trans.totalBill << RESET << endl;
    cout << CYAN << "│" << RESET << " Payment Mode: " << BOLD << trans.paymentMode << RESET << endl;
    
    if (trans.paymentMode == "Cash") {
        cout << CYAN << "│" << RESET << " Cash Received: P" << fixed << setprecision(2) << trans.cashReceived << endl;
        cout << CYAN << "│" << RESET << " Change: " << BOLD << "P" << fixed << setprecision(2) << trans.change << RESET << endl;
    }
    
    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
    
    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << GREEN << BOLD << "          Thank you for your purchase!         " << RESET << CYAN << "│" << RESET << endl;
    cout << CYAN << "│" << RESET << "          Please come again soon!             " << CYAN << "│" << RESET << endl;
    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
}

// Function to record a transaction
void recordTransaction(const Transaction& trans) {
    transactions.push_back(trans);
}

// Function to view all transactions
void viewTransactions() {
    string password;
    cout << YELLOW << "\nEnter password to view transactions: " << RESET;
    cin >> password;
    
    if (password == "admin123") {
        system("cls"); // Clear screen for better presentation
        
        cout << CYAN << BOLD << "\n╔═══════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
        cout << CYAN << BOLD << "║" << BG_BLACK << WHITE << BOLD << "                           TRANSACTION HISTORY                            " << RESET << CYAN << BOLD << "║" << RESET << endl;
        cout << CYAN << BOLD << "╚═══════════════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
        
        if (transactions.empty()) {
            cout << YELLOW << "\nNo transactions recorded for today.\n" << RESET;
            return;
        }
        
        cout << CYAN << "┌───────────────────────────────────────────────────────────────────────────────────┐" << RESET << endl;
        cout << CYAN << "│" << RESET << left 
             << setw(12) << " Trans ID" 
             << setw(20) << "Customer" 
             << setw(20) << "Date/Time" 
             << setw(15) << "Total Bill" 
             << "Payment" << endl;
        cout << CYAN << "├───────────────────────────────────────────────────────────────────────────────────┤" << RESET << endl;
        
        for (const auto& trans : transactions) {
            tm* localTime = localtime(&trans.timestamp);
            char dateBuffer[80];
            strftime(dateBuffer, sizeof(dateBuffer), "%b %d, %Y %I:%M %p", localTime);
            
            cout << CYAN << "│" << RESET << " " << left 
                 << setw(11) << trans.transactionId 
                 << setw(20) << trans.customerName 
                 << setw(20) << dateBuffer 
                 << "P" << setw(14) << fixed << setprecision(2) << trans.totalBill 
                 << trans.paymentMode << endl;
        }
        
        cout << CYAN << "└───────────────────────────────────────────────────────────────────────────────────┘" << RESET << endl;
        
        // Display summary statistics
        double totalSales = 0;
        int cashTransactions = 0, digitalTransactions = 0;
        
        for (const auto& trans : transactions) {
            totalSales += trans.totalBill;
            if (trans.paymentMode == "Cash") cashTransactions++;
            else digitalTransactions++;
        }
        
        cout << CYAN << "┌───────────────────────────────────────────────────────────────────────────────────┐" << RESET << endl;
        cout << CYAN << "│" << RESET << BOLD << " SUMMARY" << RESET << endl;
        cout << CYAN << "├───────────────────────────────────────────────────────────────────────────────────┤" << RESET << endl;
        cout << CYAN << "│" << RESET << " Total Transactions: " << BOLD << transactions.size() << RESET << endl;
        cout << CYAN << "│" << RESET << " Total Sales: " << BOLD << "P" << fixed << setprecision(2) << totalSales << RESET << endl;
        cout << CYAN << "│" << RESET << " Cash Transactions: " << BOLD << cashTransactions << RESET << endl;
        cout << CYAN << "│" << RESET << " Digital Transactions: " << BOLD << digitalTransactions << RESET << endl;
        cout << CYAN << "└───────────────────────────────────────────────────────────────────────────────────┘" << RESET << endl;
    } else {
        cout << RED << "Incorrect password.\n" << RESET;
    }
}

// Main function
int main() {
    // Menu items with prices
    vector<pair<string, double>> coffeeMenu = {
        {"Americano", 100},
        {"Espresso", 80},
        {"Mocha", 170},
        {"Cappuccino", 130},
        {"Chocolate", 150},
        {"Latte", 140},
        {"Cold Brew", 160}
    };
    
    vector<pair<string, double>> pastryMenu = {
        {"Croissant", 50},
        {"Muffin", 70},
        {"Danish Pastry", 120},
        {"Eclair", 90},
        {"Cheesecake", 150},
        {"Brownie", 80}
    };
    
    // Size options
    vector<pair<string, double>> sizeOptions = {
        {"Tall", 1.0},    // Regular price
        {"Grande", 1.2},  // +20%
        {"Venti", 1.5}    // +50%
    };
    
    // Variables
    int category, itemChoice, sizeChoice, qty;
    char anotherCategory, anotherItem;
    string customerName;
    vector<Item> purchasedItems;
    
    // Welcome screen
    system("cls"); // Clear screen for better presentation
    cout << CYAN << BOLD << "\n╔═══════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << BOLD << "║" << BG_BLACK << WHITE << BOLD << "          WELCOME TO COFFEE KO CAFE! ☕        " << RESET << CYAN << BOLD << "║" << RESET << endl;
    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════╝" << RESET << endl;
    
    // Get customer name
    cout << "\nEnter Customer's Name: ";
    cin.ignore();
    getline(cin, customerName);
    
    // Order processing
    do {
        system("cls"); // Clear screen for better menu display
        cout << CYAN << BOLD << "\n╔═══════════════════════════════════════════════╗" << RESET << endl;
        cout << CYAN << BOLD << "║" << BG_BLACK << WHITE << BOLD << "               COFFEE KO MENU                " << RESET << CYAN << BOLD << "║" << RESET << endl;
        cout << CYAN << BOLD << "╚═══════════════════════════════════════════════╝" << RESET << endl;
        
        cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
        cout << CYAN << "│" << RESET << BOLD << " SELECT CATEGORY:" << RESET << endl;
        cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
        cout << CYAN << "│" << RESET << " 1. ☕ Coffee" << endl;
        cout << CYAN << "│" << RESET << " 2. 🥐 Pastries" << endl;
        cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
        cout << "Choose Category [1-2]: ";
        cin >> category;
        
        switch (category) {
            case 1: { // Coffee selection
                do {
                    system("cls"); // Clear screen for better menu display
                    cout << CYAN << BOLD << "\n╔═══════════════════════════════════════════════╗" << RESET << endl;
                    cout << CYAN << BOLD << "║" << BG_BLACK << WHITE << BOLD << "             COFFEE SELECTION               " << RESET << CYAN << BOLD << "║" << RESET << endl;
                    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════╝" << RESET << endl;
                    
                    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
                    cout << CYAN << "│" << RESET << BOLD << " COFFEE MENU:" << RESET << endl;
                    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
                    
                    for (size_t i = 0; i < coffeeMenu.size(); ++i) {
                        cout << CYAN << "│" << RESET << " " << i+1 << ". " << left << setw(20) << coffeeMenu[i].first 
                             << "P" << fixed << setprecision(2) << coffeeMenu[i].second << endl;
                    }
                    
                    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
                    cout << "Choose Coffee [1-" << coffeeMenu.size() << "]: ";
                    cin >> itemChoice;
                    
                    if (itemChoice < 1 || itemChoice > (int)coffeeMenu.size()) {
                        cout << RED << "Invalid coffee choice. Please select a valid option.\n" << RESET;
                        system("pause");
                        continue;
                    }
                    
                    // Size selection
                    cout << CYAN << "\n┌───────────────────────────────────────────────┐" << RESET << endl;
                    cout << CYAN << "│" << RESET << BOLD << " SELECT SIZE:" << RESET << endl;
                    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
                    
                    for (size_t i = 0; i < sizeOptions.size(); ++i) {
                        cout << CYAN << "│" << RESET << " " << i+1 << ". " << left << setw(10) << sizeOptions[i].first;
                        if (i == 0) cout << "(Regular Price)" << endl;
                        else cout << "(+" << (sizeOptions[i].second - 1.0) * 100 << "%)" << endl;
                    }
                    
                    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
                    cout << "Choose Size [1-" << sizeOptions.size() << "]: ";
                    cin >> sizeChoice;
                    
                    while (sizeChoice < 1 || sizeChoice > (int)sizeOptions.size()) {
                        cout << RED << "Invalid size choice. Please choose again (1-" << sizeOptions.size() << "): " << RESET;
                        cin >> sizeChoice;
                    }
                    
                    string coffeeName = coffeeMenu[itemChoice-1].first;
                    double basePrice = coffeeMenu[itemChoice-1].second;
                    string sizeName = sizeOptions[sizeChoice-1].first;
                    double priceMultiplier = sizeOptions[sizeChoice-1].second;
                    
                    cout << "How many " << sizeName << " " << coffeeName << "? ";
                    cin >> qty;
                    
                    while (qty <= 0) {
                        cout << RED << "Invalid quantity. Please enter a positive number: " << RESET;
                        cin >> qty;
                    }
                    
                    // Add to purchased items
                    purchasedItems.push_back({coffeeName, qty, basePrice * priceMultiplier, sizeName});
                    
                    cout << GREEN << "\n✓ Added to order: " << qty << "x " << sizeName << " " << coffeeName << RESET << endl;
                    cout << "\nDo you want to order another coffee? (Y/N): ";
                    cin >> anotherItem;
                } while (toupper(anotherItem) == 'Y');
                break;
            }
            
            case 2: { // Pastry selection
                do {
                    system("cls"); // Clear screen for better menu display
                    cout << CYAN << BOLD << "\n╔═══════════════════════════════════════════════╗" << RESET << endl;
                    cout << CYAN << BOLD << "║" << BG_BLACK << WHITE << BOLD << "             PASTRY SELECTION               " << RESET << CYAN << BOLD << "║" << RESET << endl;
                    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════╝" << RESET << endl;
                    
                    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
                    cout << CYAN << "│" << RESET << BOLD << " PASTRY MENU:" << RESET << endl;
                    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
                    
                    for (size_t i = 0; i < pastryMenu.size(); ++i) {
                        cout << CYAN << "│" << RESET << " " << i+1 << ". " << left << setw(20) << pastryMenu[i].first 
                             << "P" << fixed << setprecision(2) << pastryMenu[i].second << endl;
                    }
                    
                    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
                    cout << "Choose Pastry [1-" << pastryMenu.size() << "]: ";
                    cin >> itemChoice;
                    
                    if (itemChoice < 1 || itemChoice > (int)pastryMenu.size()) {
                        cout << RED << "Invalid pastry choice. Please select a valid option.\n" << RESET;
                        system("pause");
                        continue;
                    }
                    
                    string pastryName = pastryMenu[itemChoice-1].first;
                    double basePrice = pastryMenu[itemChoice-1].second;
                    
                    cout << "How many " << pastryName << "? ";
                    cin >> qty;
                    
                    while (qty <= 0) {
                        cout << RED << "Invalid quantity. Please enter a positive number: " << RESET;
                        cin >> qty;
                    }
                    
                    // Add to purchased items
                    purchasedItems.push_back({pastryName, qty, basePrice, "Regular"});
                    
                    cout << GREEN << "\n✓ Added to order: " << qty << "x " << pastryName << RESET << endl;
                    cout << "\nDo you want to order another pastry? (Y/N): ";
                    cin >> anotherItem;
                } while (toupper(anotherItem) == 'Y');
                break;
            }
            
            default:
                cout << RED << "\nInvalid Category. Please choose again.\n" << RESET;
                system("pause");
        }
        
        cout << "\nDo you want to purchase from another category? (Y/N): ";
        cin >> anotherCategory;
    } while (toupper(anotherCategory) == 'Y');
    
    // Calculate total bill
    double totalBill = 0;
    for (const auto& item : purchasedItems) {
        totalBill += item.price * item.quantity;
    }
    
    // Payment processing
    system("cls"); // Clear screen for payment
    cout << CYAN << BOLD << "\n╔═══════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << BOLD << "║" << BG_BLACK << WHITE << BOLD << "                  PAYMENT                    " << RESET << CYAN << BOLD << "║" << RESET << endl;
    cout << CYAN << BOLD << "╚═══════════════════════════════════════════════╝" << RESET << endl;
    
    // Display order summary
    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << BOLD << " ORDER SUMMARY:" << RESET << endl;
    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
    
    for (const auto& item : purchasedItems) {
        cout << CYAN << "│" << RESET << " " << left << setw(3) << item.quantity << "x " 
             << setw(15) << item.name;
        if (item.size != "Regular") {
            cout << "(" << item.size << ")";
        }
        cout << right << setw(10) << "P" << fixed << setprecision(2) << (item.price * item.quantity) << endl;
    }
    
    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
    cout << CYAN << "│" << RESET << " " << BOLD << left << setw(30) << "TOTAL:" 
         << right << setw(10) << "P" << fixed << setprecision(2) << totalBill << RESET << endl;
    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
    
    // Payment mode selection
    cout << CYAN << "┌───────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << BOLD << " SELECT PAYMENT MODE:" << RESET << endl;
    cout << CYAN << "├───────────────────────────────────────────────┤" << RESET << endl;
    cout << CYAN << "│" << RESET << " 1. 💵 Cash" << endl;
    cout << CYAN << "│" << RESET << " 2. 💳 Digital Payment" << endl;
    cout << CYAN << "└───────────────────────────────────────────────┘" << RESET << endl;
    cout << "Your choice: ";
    
    int paymentChoice;
    string paymentMode;
    double cashReceived = 0, change = 0;
    
    cin >> paymentChoice;
    
    if (paymentChoice == 1) {
        paymentMode = "Cash";
        cout << "\nEnter Payment Amount: P";
        cin >> cashReceived;
        
        while (cashReceived < totalBill) {
            cout << RED << "Insufficient payment. Please pay the exact amount or more.\n" << RESET;
            cout << "Enter Payment Amount: P";
            cin >> cashReceived;
        }
        
        change = cashReceived - totalBill;
        cout << GREEN << "\n✓ Payment received. Change: P" << fixed << setprecision(2) << change << RESET << endl;
    } else {
        paymentMode = "Digital";
        cashReceived = totalBill; // For consistency in the transaction record
        change = 0;
        cout << GREEN << "\n✓ Digital payment processed successfully.\n" << RESET;
    }
    
    // Create and record transaction
    Transaction trans;
    trans.customerName = customerName;
    trans.items = purchasedItems;
    trans.totalBill = totalBill;
    trans.paymentMode = paymentMode;
    trans.cashReceived = cashReceived;
    trans.change = change;
    trans.timestamp = time(0);
    trans.transactionId = generateTransactionId();
    
    recordTransaction(trans);
    
    cout << "\nPress Enter to view receipt...";
    cin.ignore();
    cin.get();
    
    // Print receipt
    printReceipt(trans);
    
    // Option to view transactions
    cout << "\nDo you want to view all transactions? (Y/N): ";
    char viewOption;
    cin >> viewOption;
    
    if (toupper(viewOption) == 'Y') {
        viewTransactions();
    }
    
    cout << "\nThank you for using Coffee Ko POS System!\n";
    system("pause");
    return 0;
}