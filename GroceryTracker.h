#pragma once

#include <map>
#include <string>
#include "sqlite3.h"

class GroceryTracker {
private:
    std::map<std::string, int> groceryList;
    sqlite3* db;

public:
    void openDatabase(const std::string& dbPath);
    bool login(); // Add this method
    void addItem(const std::string& item, int frequency);
    void printLowStockItems();
    void loadFromFile(const std::string& fileName);
    int getItemFrequency(const std::string& item);
    void printGroceryList();
    void printHistogram();
    void backupData(const std::string& fileName);
};

