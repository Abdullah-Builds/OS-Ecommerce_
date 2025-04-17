#include <iostream>
#include <sqlite3.h>
#include "auth.h"

using namespace std;

bool Authenticate_User(const std::string& name) {
    sqlite3* db;
    sqlite3_stmt* stmt;

    int rc = sqlite3_open("./database/users.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "Unable to Open" << sqlite3_errmsg(db) << endl;
        return false;
    }

    string sql = "SELECT COUNT(*) FROM Users WHERE name = ?";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        exists = (count > 0);
    } else {
        cerr << "Failed to execute statement" << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return exists;
}
