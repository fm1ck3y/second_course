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

void Database::AddUserToDatabase(User *user)
{
    for (auto _user : this->users)
        if (user->GetId() == _user->GetId())
            return;
    this->users.push_back(user);
    std::string sql = "INSERT INTO User(FIO,address,numberPhone,passport_number) VALUES ('" + user->GetFIO() + "', '" + user->GetAddress() + "', '" + user->GetNumberPhone() + "', '" + user->GetPassportNumber() + "')";
    char sql_char[sql.length()];
    strcpy(sql_char, sql.c_str());
    if (Connect())
        if (sqlite3_exec(db, sql_char, callback, 0, &zErrMsg) != SQLITE_OK)
            std::cerr << "Bad execute : " << sqlite3_errmsg << std::endl;
    sqlite3_close(db);
}

void Database::ClearDatabase()
{
    for (auto car : this->cars)
        delete car;
    this->cars = std::list<Car *>();

    for (auto user : this->users)
        delete user;
    this->users = std::list<User *>();

    for (auto visit : this->visits)
        delete visit;
    this->visits = std::list<Visit *>();

    for (auto payment : this->payments)
        delete payment;
    this->payments = std::list<Payment *>();
}

void Database::DownloadAllDatabase()
{
    this->ClearDatabase();
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
    char *sql = "Select * From Visit";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            Visit *visit = new Visit();
            visit->SetID(std::stoi(std::string(reinterpret_cast<const char *>(
                sqlite3_column_text(statement, 0)))));
            visit->SetDate(std::stol(std::string(reinterpret_cast<const char *>(
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
            this->visits_for_save.push_back(new Visit(*visit));
        }
        sqlite3_finalize(statement);
    }
    //delete statement;
    //delete[] sql;
}

void Database::DownloadAllPayments()
{
    char *sql = "Select * From Payment";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            Payment *payment = new Payment();
            payment->SetID(std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 0)))));
            payment->SetDate(std::stol(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1)))));
            payment->SetAmount(std::stof(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 2)))));
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
            this->payments_for_save.push_back(new Payment(*payment));
        }
        sqlite3_finalize(statement);
    }
    //delete statement;
    //delete[] sql;
}

void Database::DownloadAllUsers()
{
    char *sql = "Select * From User";
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
            this->users_for_save.push_back(new User(*user));
        }
        sqlite3_finalize(statement);
    }
    //delete[] sql;
}

void Database::DownloadAllCars()
{
    char *sql = "Select * From Car";
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
            this->cars_for_save.push_back(new Car(*car));
        }
        sqlite3_finalize(statement);
    }
    //delete[] sql;
}

void Database::AddCarToDatabase(Car *car)
{
    for (auto _car : this->cars)
        if (car->GetId() == _car->GetId())
            return;
    this->cars.push_back(car);
    std::string sql = "INSERT INTO Car(CarModel,Color,Place,stateNumber,region,dateEnd,user_id) VALUES ('" + car->GetCarModel() + "','" + car->GetColor() + "', '" + car->GetPlace() + "','" + car->GetStateNumber() + "','" + std::to_string(car->GetRegion()) + "','" + std::to_string(car->GetDateEnd()) + "','" + std::to_string(car->GetDriver()->GetId()) + "')";
    char sql_char[sql.length()];
    strcpy(sql_char, sql.c_str());
    if (Connect())
        if (sqlite3_exec(db, sql_char, callback, 0, &zErrMsg) != SQLITE_OK)
            std::cerr << "Bad execute : " << sqlite3_errmsg << std::endl;
    sqlite3_close(db);
}

void Database::AddVisitToDatabase(Visit *visit)
{
    for (auto _visit : this->visits)
        if (visit->GetId() == _visit->GetId())
            return;
    this->visits.push_back(visit);
    std::string sql = "INSERT INTO Visit(date,arrival,car_id) VALUES ('" + std::to_string(visit->GetDate()) + "','" + std::to_string(visit->IsArrival()) + "', '" + std::to_string(visit->GetCar()->GetId()) + "')";
    char sql_char[sql.length()];
    strcpy(sql_char, sql.c_str());
    if (Connect())
        if (sqlite3_exec(db, sql_char, callback, 0, &zErrMsg) != SQLITE_OK)
            std::cerr << "Bad execute : " << sqlite3_errmsg << std::endl;
    sqlite3_close(db);
}

void Database::AddPaymentToDatabase(Payment *payment)
{
    for (auto _payment : this->payments)
        if (payment->GetId() == _payment->GetId())
            return;
    this->payments.push_back(payment);
    std::string sql = "INSERT INTO Payment(date,amount,car_id) VALUES ('" + std::to_string(payment->GetDate()) + "','" + std::to_string(payment->GetAmount()) + "', '" + std::to_string(payment->GetCar()->GetId()) + "')";
    char sql_char[sql.length()];
    strcpy(sql_char, sql.c_str());
    if (Connect())
        if (sqlite3_exec(db, sql_char, callback, 0, &zErrMsg) != SQLITE_OK)
            std::cerr << "Bad execute : " << sqlite3_errmsg << std::endl;
    sqlite3_close(db);
}

void Database::UpdateCar(Car *car)
{
    std::string sql_req = "";
    std::list<Car *> cars = this->cars_for_save;
    Car *this_car = nullptr;
    for (auto _car : cars)
    {
        if (car->GetId() == _car->GetId())
        {
            this_car = _car;
            break;
        }
    }
    if (this_car != nullptr)
    {
        if (Connect())
        {
            if (this_car->GetPlace() != car->GetPlace())
                sql_req += "UPDATE Car SET Place ='" + car->GetPlace() + "' WHERE id =" + std::to_string(car->GetId()) + ";\n";
            if (this_car->GetStateNumber() != car->GetStateNumber())
                sql_req += "UPDATE Car SET stateNumber ='" + car->GetStateNumber() + "' WHERE id =" + std::to_string(car->GetId()) + ";\n";
            if (this_car->GetCarModel() != car->GetCarModel())
                sql_req += "UPDATE Car SET CarNodel ='" + car->GetCarModel() + "' WHERE id =" + std::to_string(car->GetId()) + ";\n";
            if (this_car->GetColor() != car->GetColor())
                sql_req += "UPDATE Car SET Color ='" + car->GetColor() + "' WHERE id =" + std::to_string(car->GetId()) + ";\n";
            if (this_car->GetRegion() != car->GetRegion())
                sql_req += "UPDATE Car SET region ='" + std::to_string(car->GetRegion()) + "' WHERE id =" + std::to_string(car->GetId()) + ";\n";
            if (this_car->GetDriver()->GetId() != car->GetDriver()->GetId())
                sql_req += "UPDATE Car SET user_id ='" + std::to_string(car->GetDriver()->GetId()) + "' WHERE id =" + std::to_string(car->GetId()) + ";\n";
            if (this_car->GetDateEnd() != car->GetDateEnd())
                sql_req += "UPDATE Car SET dateEnd ='" + std::to_string(car->GetDateEnd()) + "' WHERE id =" + std::to_string(car->GetId()) + ";\n";
            if (sql_req != "")
            {
                char sql_char[sql_req.length()];
                strcpy(sql_char, sql_req.c_str());
                if (sqlite3_exec(db, sql_char, callback, 0, &zErrMsg) != SQLITE_OK)
                    std::cerr << "Bad execute : " << sqlite3_errmsg << std::endl;
                sqlite3_close(db);
                this->DownloadAllDatabase();
            }
        }
    }
    delete this_car;
}

std::list<Car *> Database::GetAllCars() { return this->cars; }
std::list<User *> Database::GetAllUsers() { return this->users; }
std::list<Payment *> Database::GetAllPayment() { return this->payments; };
std::list<Visit *> Database::GetAllVisit() { return this->visits; }