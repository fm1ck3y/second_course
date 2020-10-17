#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include "sqlite3.h"
#include <list>
#include <any>

class Database
{
protected:
    static sqlite3 *db;                   // файл БД
    static char *zErrMsg;                 // ошибки при запросах
    virtual void Save();                  // функция сохранения данных в БД
    virtual void Create();                // функция создания поля в БД
    virtual void Delete();                // функция удаления поля в БД
    static void Execute(std::string sql); // функция SQL запроса
public:
    static char *name_db;     // название БД
    static bool Connect();    // Подключение к БД
    static void Disconnect(); // Отключение
};

#endif
