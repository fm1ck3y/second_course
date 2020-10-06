#include <iostream>
#include <time.h>
#include "HistoryVisit.h"
#include "Car.h"
HistoryVisit::HistoryVisit(Car *car, time_t Date, bool arrival)
{
    this->car = car;
    this->date = date;
    this->arrival = arrival;
}

int HistoryVisit::GetId() { return this->id; }
Car *HistoryVisit::GetCar() { return this->car; }
time_t HistoryVisit::GetDate() { return this->date; }
bool HistoryVisit::IsArrival() { return this->arrival; }

void HistoryVisit::SetCar(Car *car) { this->car = car; }
void HistoryVisit::SetDate(time_t date) { this->date = date; }
void HistoryVisit::SetArrival(bool arrival) { this->arrival = arrival; }