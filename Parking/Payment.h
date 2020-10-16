#ifndef PAYMENT_H
#define PAYMENT_H
#include <iostream>
#include <time.h>
#include "db/database.h"

class Car; // forward declaration

class Payment : Database
{
private:
    int id;
    time_t Date;   // дата оплаты
    double amount; // сумма оплаты
    Car *car;      // машина, за которую платили
public:
    Payment(time_t Date, double amount, Car *car);
    Payment();
    Payment(const Payment &payment);
    static std::list<Payment*> payments;
    int GetId();
    time_t GetDate();
    double GetAmount();
    Car *GetCar();

    void SetDate(time_t Date);
    void SetAmount(double amount);
    void SetCar(Car *car);
    void PrintInfo();

    void Create() override final;
    static void Select();
};
#endif