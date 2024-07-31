#include "GroceryTracker.h" // Include the header file for the GroceryTracker class.
#include<iostream> // Include the standard input/output stream library.
#include<fstream> // Include the file stream library for reading from and writing to files.

// Load the grocery list from a file.
void GroceryTracker::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName); // Open the file with the provided name.
    std::string item; // Variable to store each item read from the file.

    while (getline(file, item)) { // Read a line from the file into item.
        if (!item.empty()) { // If the line isn't empty...
            groceryList[item]++; // ...increment the count of the item in the grocery list.
        }
    }

    file.close(); // Close the file.
}

// Get the frequency of a specific item.
int GroceryTracker::getItemFrequency(const std::string& item) {
    if (groceryList.find(item) != groceryList.end()) // If the item is found in the grocery list...
        return groceryList[item]; // ...return its frequency.
    else
        return 0; // If the item is not in the list, return 0.
}

// Print the grocery list.
void GroceryTracker::printGroceryList() {
    for (auto& pair : groceryList) { // For each item in the grocery list...
        std::cout << pair.first << " " << pair.second << std::endl; // ...print the item and its frequency.
    }
}

// Print a histogram representing the frequency of each item.
void GroceryTracker::printHistogram() {
    for (auto& pair : groceryList) { // For each item in the grocery list...
        std::cout << pair.first << " "; // ...print the item...
        for (int i = 0; i < pair.second; i++) { // ...and for each occurrence of the item...
            std::cout << "*"; // ...print a star.
        }
        std::cout << std::endl; // Move to the next line after printing the histogram for one item.
    }
}

// Backup the grocery list to a file.
void GroceryTracker::backupData(const std::string& fileName) {
    std::ofstream file(fileName); // Open the file with the provided name.

    for (auto& pair : groceryList) { // For each item in the grocery list...
        file << pair.first << " " << pair.second << std::endl; // ...write the item and its frequency to the file.
    }

    file.close(); // Close the file.
}

void GroceryTracker::printLowStockItems() {
    std::cout << "Items with low stock:\n";
    for (const auto& pair : groceryList) {
        if (pair.second <= 3) {
            std::cout << pair.first << " (only " << pair.second << " left)\n";
        }
    }
}

void GroceryTracker::addItem(const std::string& item, int frequency) {
    // Update the map with the new item and frequency
    groceryList[item] += frequency;

    // Append the new item to the existing file
    std::ofstream file("CS210_Project_Three_Input_File.txt", std::ios_base::app);
    for (int i = 0; i < frequency; i++) {
        file << item << std::endl;
    }
    file.close();
}


