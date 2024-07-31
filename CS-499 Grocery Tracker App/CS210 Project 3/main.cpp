/*
Author: Zachary Maness
Class: CS-210
Date: 06/14/2023
*/

#include "GroceryTracker.h"
#include <iostream>
#include <limits>

int main() {
    GroceryTracker myTracker; // create an instance of the GroceryTracker class
    myTracker.loadFromFile("CS210_Project_Three_Input_File.txt"); // load grocery items from the input file

    // Interacting with the program via a menu
    int option = 0;
    std::string item;
    while (true) {
        // present the options to the user
        std::cout << "\n1. Get the frequency of an item\n"
            << "2. Print the list of items\n"
            << "3. Print histogram\n"
            << "4. Exit\n"
            << "5. Check for low stock items\n"
            << "6. Add a new item\n"
            << "Enter your option: ";
        std::cin >> option;

        // If the user input was not an integer, cin will enter a fail state.
        // We need to clear this state and ignore the bad input before we continue.
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option. Please try again.\n";
            continue;
        }

        // handle the user's choice
        switch (option) {
        case 1: // user wants to get the frequency of an item
            std::cout << "Enter item name: ";
            std::cin >> item;
            std::cout << "Frequency of " << item << ": "
                << myTracker.getItemFrequency(item) << std::endl;
            break;
        case 2: // user wants to print the list of items
            myTracker.printGroceryList();
            break;
        case 3: // user wants to print the histogram
            myTracker.printHistogram();
            break;
        case 4: // user wants to exit the program
            myTracker.backupData("frequency.dat"); // before exiting, backup the data
            return 0; // exit the program
        case 5: // Option to print items with low stock
            myTracker.printLowStockItems();
            break;
        case 6: // Option to add a new item
            std::cout << "Enter item name: ";
            std::cin >> item;
            int freq;
            std::cout << "Enter frequency: ";
            std::cin >> freq;
            myTracker.addItem(item, freq);
            std::cout << item << " added with a frequency of " << freq << std::endl;
            break;
        default: // the user entered an invalid option
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0; // the program should never reach this line under normal operation
}
