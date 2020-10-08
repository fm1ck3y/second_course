#include <bits/stdc++.h>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "database.h"

int Database::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

Database::Database(char *name_db)
{
    this->name_db = name_db;
}

Database::~Database()
{
    if (db != NULL)
    {
        sqlite3_close(db);
    }
}

bool Database::Connect()
{
    if (SQLITE_OK != sqlite3_open(name_db, &db))
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }
    return true;
}

void Database::AddUserToDatabase(std::string FIO, std::string address, std::string numberPhone, std::string passport_number)
{
    std::string sql = "INSERT INTO User(FIO,address,numberPhone,passport_number) VALUES ('" + FIO + "','" + address + "', '" + numberPhone + "','" + passport_number + "')";
    char sql_char[sql.length()]; 
    strcpy(sql_char,sql.c_str());
    if (Connect())
        sqlite3_exec(db, sql_char, callback, 0, &zErrMsg);
    sqlite3_close(db);
}