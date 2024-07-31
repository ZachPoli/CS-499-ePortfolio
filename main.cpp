#include "GroceryTracker.h"
#include <iostream>

int main() {
    GroceryTracker myTracker;
    myTracker.openDatabase("GroceryTrackerDB.db");

    // Login process
    bool loggedIn = false;
    while (!loggedIn) {
        loggedIn = myTracker.login();
        if (!loggedIn) {
            std::cout << "Please try again.\n";
        }
    }

    int option;
    std::string item;
    while (true) {
        std::cout << "\n1. Get the frequency of an item\n"
            << "2. Print the list of items\n"
            << "3. Print histogram\n"
            << "4. Exit\n"
            << "5. Check for low stock items\n"
            << "6. Add a new item\n"
            << "Enter your option: ";
        std::cin >> option;

        switch (option) {
        case 1:
            std::cout << "Enter item name: ";
            std::cin >> item;
            std::cout << "Frequency of " << item << ": "
                << myTracker.getItemFrequency(item) << std::endl;
            break;
        case 2:
            myTracker.printGroceryList();
            break;
        case 3:
            myTracker.printHistogram();
            break;
        case 4:
            myTracker.backupData("frequency.dat");
            return 0;
        case 5:
            myTracker.printLowStockItems();
            break;
        case 6:
            std::cout << "Enter item name: ";
            std::cin >> item;
            int freq;
            std::cout << "Enter frequency: ";
            std::cin >> freq;
            myTracker.addItem(item, freq);
            std::cout << item << " added with a frequency of " << freq << std::endl;
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    }
}
