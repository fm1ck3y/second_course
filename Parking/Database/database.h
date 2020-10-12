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
    std::list<Car *> cars;
    std::list<User *> users;
    std::list<Payment *> payments;
    std::list<Visit *> visits;

    void DownloadAllCars();
    void DownloadAllUsers();
    void DownloadAllVisits();
    void DownloadAllPayments();

public:
    Database(char *name_db);
    ~Database();

    bool Connect();
    void AddUserToDatabase(User *user);
    void AddCarToDatabase(Car *car);
    void AddVisitToDatabase(Visit *visit);
    void AddPaymentToDatabase(Payment *payment);
    void ClearDatabase();
    void DownloadAllDatabase();
    std::list<Car *> GetAllCars();
    std::list<User *> GetAllUsers();
    std::list<Payment *> GetAllPayment();
    std::list<Visit *> GetAllVisit();
    // need to implement
    void UpdateCar(User *user);
    void UpdateUser(Car *car);
    void UpdatePayment(Payment *payment);
    void UpdateVisit();
};
#endif