#ifndef HISTORY_PAYMENT_H
#define HISTORY_PAYMENT_H
#include <iostream>
#include <time.h>

class Car; // forward declaration

class HistoryPayment
{
private:
    int id;
    time_t Date;   // дата оплаты
    double amount; // сумма оплаты
    Car *car;      // машина, за которую платили
public:
    HistoryPayment(time_t Date, double amount, Car *car);

    int GetId();
    time_t GetDate();
    double GetAmount();
    Car *GetCar();

    void SetDate(time_t Date);
    void SetAmount(double amount);
    void SetCar(Car *car);
};
#endif