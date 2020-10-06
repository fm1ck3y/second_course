#include <iostream>
#include <time.h>
#include "HistoryPayment.h"
#include "Car.h"
HistoryPayment::HistoryPayment(time_t Date, double amount, Car *car)
{
    this->car = car;
    this->Date;
    this->amount = amount;
}

 double HistoryPayment::GetAmount() { return this->amount; }
Car *HistoryPayment::GetCar() { return this->car; }
time_t HistoryPayment::GetDate() { return this->Date; }
int HistoryPayment::GetId() { return this->id; }

void HistoryPayment::SetAmount(double amount) { this->amount = amount; }
void HistoryPayment::SetCar(Car *car) { this->car = car; }
void HistoryPayment::SetDate(time_t date) { this->Date = date; }