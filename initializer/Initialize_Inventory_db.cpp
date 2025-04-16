#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

void InitializeDatabase() {
    sqlite3 *db;
    int rc = sqlite3_open("inventory.db", &db);
    if (rc) {
        cerr << "Unable to Open " << sqlite3_errmsg(db) << endl;
        return;
    }

    string sql = R"(
        CREATE TABLE IF NOT EXISTS Inventory (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            item TEXT NOT NULL,
            price REAL NOT NULL,
            quantity INTEGER NOT NULL,
            name TEXT NOT NULL
        );
    )";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Table creation failed: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Inventory table created successfully (or already exists)." << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    InitializeDatabase();
    return 0;
}

