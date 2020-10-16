#include <iostream>
#include <time.h>
#include "Visit.h"
#include "Car.h"
#include <any>
Visit::Visit(Car *car, time_t Date, bool arrival)
{
    this->car = car;
    this->date = date;
    this->arrival = arrival;
}
Visit::Visit()
{
    this->car = new Car();
    this->date = 0;
    this->arrival = false;
}

Visit::Visit(const Visit &visit)
{
    this->id = visit.id;
    this->car = visit.car;
    this->date = visit.date;
    this->arrival = visit.arrival;
}

int Visit::GetId() { return this->id; }
Car *Visit::GetCar() { return this->car; }
time_t Visit::GetDate() { return this->date; }
bool Visit::IsArrival() { return this->arrival; }

void Visit::SetID(int id) { this->id = id; }
void Visit::SetCar(Car *car) { this->car = car; }
void Visit::SetDate(time_t date) { this->date = date; }
void Visit::SetArrival(bool arrival) { this->arrival = arrival; }

void Visit::PrintInfo()
{
    std::cout << "Запись посещения парковки: " << std::endl;
    if (this->arrival)
        std::cout << "\tАвтомобиль заехал" << std::endl;
    else
        std::cout << "\tАвтомобиль выехал" << std::endl;
    std::cout << "\tДата: " << this->date << std::endl;
    this->car->PrintInfo();
}

void Visit::Create()
{
    std::string sql = "INSERT INTO Visit(date,arrival,car_id) VALUES ('" + std::to_string(this->date) + "','" + std::to_string(this->arrival) + "', '" + std::to_string(this->car->GetId()) + "')";
    Execute(sql);
}