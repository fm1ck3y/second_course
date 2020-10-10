#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include "sqlite3.h"
#include <list>

class Car;
class User;
class Payment;
class Visit;

class Database
{
private:
    sqlite3 *db = NULL;
    char *name_db;
    char *zErrMsg;
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    std::list<Car*> cars;
    std::list<User*> users;
    std::list<Payment*> payments;
    std::list<Visit*> visits;

    void DownloadAllCars();
    void DownloadAllUsers();
    void DownloadAllVisits();
    void DownloadAllPayments();

public:
    Database(char *name_db);
    ~Database();

    bool Connect();
    void AddUserToDatabase(std::string FIO, std::string address, std::string numberPhone, std::string passport_number);

    // need to implement
    void DownloadAllDatabase();
    void AddCarToDatabase();     // need to add params
    void AddVisitToDatabase();   // need to add params
    void AddPaymentToDatabase(); // need to add params
    void UpdateCar(User *user);
    void UpdateUser(Car *car);
    void UpdatePayment(Payment *payment);
    void UpdateVisit();
    std::list<Car*> GetAllCars();
    std::list<User*> GetAllUsers();
    std::list<Payment*> GetAllPayment();
    std::list<Visit*> GetAllVisit();
};
#endif