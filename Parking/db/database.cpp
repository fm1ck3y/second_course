#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <list>
#include "database.h"

void Database::Disconnect()
{
    if (db != NULL)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

void Database::Execute(std::string sql)
{
    char sql_char[sql.length()];
    std::strcpy(sql_char, sql.c_str());
    if (Connect())
        if (sqlite3_exec(db, sql_char, NULL, 0, &Database::zErrMsg) != SQLITE_OK)
            std::cerr << "Bad execute : " << sqlite3_errmsg << std::endl;
}

bool Database::Connect()
{
    if (SQLITE_OK != sqlite3_open(Database::name_db, &db))
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }
    return true;
}

void Database::Create() { return; }
void Database::Save() { return; }
void Database::Delete() { return; }
char* Database::name_db = nullptr;
char* Database::zErrMsg = nullptr;
sqlite3 * Database::db = nullptr;