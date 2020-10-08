#include <iostream>
#include <time.h>
#include "Payment.h"
#include "Car.h"
Payment::Payment(time_t Date, double amount, Car *car)
{
    this->car = car;
    this->Date;
    this->amount = amount;
}

double Payment::GetAmount() { return this->amount; }
Car *Payment::GetCar() { return this->car; }
time_t Payment::GetDate() { return this->Date; }
int Payment::GetId() { return this->id; }

void Payment::SetAmount(double amount) { this->amount = amount; }
void Payment::SetCar(Car *car) { this->car = car; }
void Payment::SetDate(time_t date) { this->Date = date; }
void Payment::PrintInfo()
{
    std::cout << "Оплата: " << std::endl;
    std::cout << "\tДата: " << this->Date << std::endl;
    std::cout << "\tСумма оплаты: " << this->amount << std::endl;
    this->car->PrintInfo();
}