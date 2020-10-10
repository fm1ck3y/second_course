#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include "database.h"
#include <list>
#include "../Car.h"
#include "../User.h"
#include "../Visit.h"
#include "../Payment.h"

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
    strcpy(sql_char, sql.c_str());
    if (Connect())
        sqlite3_exec(db, sql_char, callback, 0, &zErrMsg);
    sqlite3_close(db);
}

void Database::DownloadAllDatabase()
{
    if (Connect())
    {
        this->DownloadAllUsers();
        this->DownloadAllCars();
        this->DownloadAllVisits();
        this->DownloadAllPayments();
    }
}

void Database::DownloadAllVisits()
{
    char sql[] = "Select * From Visit";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            Visit *visit = new Visit();
            visit->SetID(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 0)))));
            visit->SetDate(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 1)))));
            visit->SetArrival(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 2)))));
            int car_id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 3))));
            for (auto car : this->cars)
            {
                if (car->GetId() == car_id)
                {
                    visit->SetCar(car);
                    break;
                }
            }
            this->visits.push_back(visit);
        }
        sqlite3_finalize(statement);
    }
    //delete statement;
    //delete sql;
}

void Database::DownloadAllPayments()
{
    char sql[] = "Select * From Payment";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            Payment *payment = new Payment();
            payment->SetID(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 0)))));
            payment->SetDate(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 1)))));
            payment->SetAmount(std::stof(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 2)))));
            int car_id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 3))));
            for (auto car : this->cars)
            {
                if (car->GetId() == car_id)
                {
                    payment->SetCar(car);
                    break;
                }
            }
            this->payments.push_back(payment);
        }
        sqlite3_finalize(statement);
    }
    //delete statement;
    //delete sql;
}

void Database::DownloadAllUsers()
{
    char sql[] = "Select * From User";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            User *user = new User();
            user->SetID(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 0)))));
            user->SetFIO(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 1))));
            user->SetAddress(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 2))));
            user->SetPassportNumber(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 3))));
            user->SetNumberPhone(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 4))));
            this->users.push_back(user);
        }
        sqlite3_finalize(statement);
    }

}

void Database::DownloadAllCars()
{
    char sql[] = "Select * From Car";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            Car *car = new Car();
            car->SetID(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 0)))));
            car->SetCarModel(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 1))));
            car->SetColor(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 2))));
            car->SetPlace(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 3))));
            car->SetStateNumber(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 4))));
            car->SetRegion(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 5)))));
            
            car->SetDateEnd(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 6)))));
            int user_id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 7))));
            for (auto user : this->users)
            {
                if (user->GetId() == user_id)
                {
                    car->SetDriver(user);
                    break;
                }
            }
            this->cars.push_back(car);
        }
        sqlite3_finalize(statement);
    }
}

std::list<Car *> Database::GetAllCars() { return this->cars; }
std::list<User *> Database::GetAllUsers() { return this->users; }
std::list<Payment *> Database::GetAllPayment() { return this->payments; };
std::list<Visit *> Database::GetAllVisit() { return this->visits; }