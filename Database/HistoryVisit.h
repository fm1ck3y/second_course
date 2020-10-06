#ifndef HISTORY_VISIT_H
#define HISTORY_VISIT_H
#include <iostream>
#include <time.h>

class Car; // forward declaration

class HistoryVisit
{
private:
    int id;
    Car *car;     // автомобиль, который посещал стоянку
    time_t date;  // дата визита
    bool arrival; // заезд = True, выезд = False
public:
    HistoryVisit(Car *car, time_t Date, bool arrival);

    int GetId();
    Car *GetCar();
    time_t GetDate();
    bool IsArrival();

    void SetCar(Car *car);
    void SetDate(time_t date);
    void SetArrival(bool arrival);
};
#endif
