#ifndef VISIT_H
#define VISIT_H
#include <iostream>
#include <time.h>
#include "db/database.h"
class Car; // forward declaration

class Visit : Database
{
private:
    int id;
    Car *car;     // автомобиль, который посещал стоянку
    time_t date;  // дата визита
    bool arrival; // заезд = True, выезд = False
public:
    Visit(Car *car, time_t Date, bool arrival); // конструктор с параметрами
    Visit();                                    // обычный конструктор
    ~Visit();                                   // деструктор
    Visit(const Visit &visit);                  // конструктор копирования
    static std::list<Visit *> visits;           // список всех визитов
    int GetId();
    Car *GetCar();
    time_t GetDate();
    bool IsArrival();

    void SetCar(Car *car);
    void SetDate(time_t date);
    void SetArrival(bool arrival);
    void PrintInfo();

    void Create() override final;
    void Save() override final;
    void Delete() override final;
    static void Select(); // выгрузка из БД
};
#endif
