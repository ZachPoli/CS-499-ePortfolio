#include "GroceryTracker.h"
#include <iostream>
#include <fstream>
#include <sstream>

void GroceryTracker::openDatabase(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1); // Exit if cannot open database
    }
}

bool GroceryTracker::login() {
    std::string username, password;
    std::cout << "Enter username:(SNHU) ";
    std::cin >> username;
    std::cout << "Enter password:(SNHU) ";
    std::cin >> password;

    std::string sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    bool loginSuccess = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        loginSuccess = true;
    }

    sqlite3_finalize(stmt);

    if (loginSuccess) {
        std::cout << "Login successful!\n";
    }
    else {
        std::cout << "Login failed! Incorrect username or password.\n";
    }

    return loginSuccess;
}

void GroceryTracker::addItem(const std::string& item, int frequency) {
    groceryList[item] += frequency;

    // Insert or update the item in the database
    std::string sql = "INSERT INTO groceries (item_name, frequency) VALUES (?, ?) ON CONFLICT(item_name) DO UPDATE SET frequency = frequency + excluded.frequency";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, item.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, frequency);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting/updating data: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void GroceryTracker::printLowStockItems() {
    std::cout << "Items with low stock:\n";
    for (const auto& pair : groceryList) {
        if (pair.second <= 3) {
            std::cout << pair.first << " (only " << pair.second << " left)\n";
        }
    }
}

void GroceryTracker::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Unable to open file " << fileName << std::endl;
        return;
    }
    std::string line, item;
    int frequency;
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> item >> frequency) {
            addItem(item, frequency);
        }
    }
}

int GroceryTracker::getItemFrequency(const std::string& item) {
    return groceryList[item];
}

void GroceryTracker::printGroceryList() {
    std::cout << "Grocery List:\n";
    for (const auto& pair : groceryList) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void GroceryTracker::printHistogram() {
    std::cout << "Grocery Frequency Histogram:\n";
    for (const auto& pair : groceryList) {
        std::cout << pair.first << ": ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

void GroceryTracker::backupData(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file) {
        std::cerr << "Unable to open backup file " << fileName << std::endl;
        return;
    }
    for (const auto& pair : groceryList) {
        file << pair.first << " " << pair.second << std::endl;
    }
}
