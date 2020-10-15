#ifndef VISIT_H
#define VISIT_H
#include <iostream>
#include <time.h>

class Car; // forward declaration

class Visit
{
private:
    int id;
    Car *car;     // автомобиль, который посещал стоянку
    time_t date;  // дата визита
    bool arrival; // заезд = True, выезд = False
public:
    Visit(Car *car, time_t Date, bool arrival);
    Visit();
    Visit(const Visit &visit);
    int GetId();
    Car *GetCar();
    time_t GetDate();
    bool IsArrival();

    void SetID(int id);
    void SetCar(Car *car);
    void SetDate(time_t date);
    void SetArrival(bool arrival);

    void PrintInfo();
};
#endif
