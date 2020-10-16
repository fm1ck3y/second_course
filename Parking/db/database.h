#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include "sqlite3.h"
#include <list>
#include <any>

class Database
{
private:
    sqlite3 *db = NULL;
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

protected:
    static char *zErrMsg;
    void Execute(std::string sql);

public:
    ~Database();
    static char *name_db;
    virtual void Save();
    virtual void Create();
    bool Connect();
};

#endif
