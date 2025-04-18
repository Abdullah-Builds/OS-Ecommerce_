#include "Inventory.h"
#include <sqlite3.h>
#include <string>
#include "auth.h" 


sqlite3* OpenDatabase() {
    sqlite3* db;
    int rc = sqlite3_open("./database/inventory.db", &db);
    if (rc) {
        cerr << "Unable to Open " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }
    return db;
}

void Inventory::Add_Inventory() {
    cout << "Enter your registered name: ";
    cin >> name;

    if (!Authenticate_User(name)) {
        cout << "User not found. Please register first." << endl;
        return;
    }

    cout << "Enter item name: ";
    cin >> item;
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;

    sqlite3* db = OpenDatabase();
    if (!db) return;

    string sql = "INSERT INTO Inventory (item, price, quantity, name) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, item.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, price);
    sqlite3_bind_int(stmt, 3, quantity);
    sqlite3_bind_text(stmt, 4, name.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Inventory item added successfully!" << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Inventory::Display_Inventory() {
    cout << "Enter your registered name: ";
    cin >> name;

    if (!Authenticate_User(name)) {
        cout << "User not found. Cannot display inventory." << endl;
        return;
    }

    sqlite3* db = OpenDatabase();
    if (!db) return;

    string sql = "SELECT item, price, quantity FROM Inventory WHERE name = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    cout << "Your Inventory:\n";
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        string item = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        double price = sqlite3_column_double(stmt, 1);
        int quantity = sqlite3_column_int(stmt, 2);
        cout << "Item: " << item << ", Price: " << price << ", Quantity: " << quantity << endl;
    }

    if (rc != SQLITE_DONE) {
        cerr << "Error reading data: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Inventory::Update_Inventory() {
    cout << "Enter your registered name: ";
    cin >> name;

    if (!Authenticate_User(name)) {
        cout << "User not found. Cannot update inventory." << endl;
        return;
    }

    cout << "Enter item to update: ";
    cin >> item;

    sqlite3* db = OpenDatabase();
    if (!db) return;

    cout << "Enter new price: ";
    cin >> price;
    cout << "Enter new quantity: ";
    cin >> quantity;

    string sql = "UPDATE Inventory SET price = ?, quantity = ? WHERE item = ? AND name = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_double(stmt, 1, price);
    sqlite3_bind_int(stmt, 2, quantity);
    sqlite3_bind_text(stmt, 3, item.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, name.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Inventory updated successfully!" << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Inventory::Remove_Inventory() {
    cout << "Enter your registered name: ";
    cin >> name;

    if (!Authenticate_User(name)) {
        cout << "User not found. Cannot remove inventory." << endl;
        return;
    }

    cout << "Enter item to remove: ";
    cin >> item;

    sqlite3* db = OpenDatabase();
    if (!db) return;

    string sql = "DELETE FROM Inventory WHERE item = ? AND name = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, item.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Remove failed: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Item removed successfully!" << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

