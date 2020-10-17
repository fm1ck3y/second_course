#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include "sqlite3.h"
#include <list>
#include <any>

class Database
{
private:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

protected:
    static sqlite3 *db;
    static char *zErrMsg;
    virtual void Save();
    virtual void Create();
    virtual void Delete();
    static void Execute(std::string sql);
public:
    static char *name_db;
    static bool Connect();
    static void Disconnect();
};

#endif
