#include <sqlite3.h>
#include <iostream>

using namespace std;

int main() {
    sqlite3* db;
    char* errMsg = nullptr;

    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS Users ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "name TEXT UNIQUE NOT NULL);";
    rc = sqlite3_exec(db, create_table_sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error (creating table): " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    const char* names[] = {
        "Ahad", "Rayyan", "Abdullah", "Khan", "Masab",
        "Huzaifa", "Hassaan", "Hamees", "Noman", "Meeran"
    };

    sqlite3_stmt* stmt;
    const char* insert_sql = "INSERT INTO Users (name) VALUES (?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    for (const char* name : names) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            cerr << "Failed to insert " << name << ": " << sqlite3_errmsg(db) << endl;
        }
        
        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);

    cout << "users.db created and initialized with 10 users successfully." << endl;
    sqlite3_close(db);
    return 0;
}

