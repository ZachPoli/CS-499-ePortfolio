#pragma once // Ensures that the header file is included only once in a compilation unit.

#include<map> // Include map library to store the grocery list and their frequency.
#include<string> // Include string library to handle the item names.

class GroceryTracker {
private:
    std::map<std::string, int> groceryList; // Map data structure to store the grocery items as keys and their frequency as values.

public:
    void addItem(const std::string& item, int frequency); // Method to add an item with a specified frequency

    void printLowStockItems(); // Method to print items with a stock count of 3 or less

    void loadFromFile(const std::string& fileName); // Method to load data from a file.

    int getItemFrequency(const std::string& item); // Method to get the frequency of an item from the grocery list.

    void printGroceryList(); // Method to print the list of grocery items.

    void printHistogram(); // Method to print a histogram representing the frequency of each item.

    void backupData(const std::string& fileName); // Method to save the grocery list to a backup file.
};
