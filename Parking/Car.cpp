#include <iostream>
#include <time.h>
#include <list>
#include "Car.h"
#include "User.h"


Car::Car(std::string Place, std::string stateNumber, int region, User *driver,
         std::string CarModel, std::string Color)
{
    this->Place = Place;
    this->stateNumber = stateNumber;
    this->region = region;
    this->driver = driver;
    this->DateEnd = time(0);
    this->CarModel = CarModel;
    this->Color = Color;
}
Car::~Car()
{
}

Car::Car()
{
    this->Place = "";
    this->stateNumber = "";
    this->region = -1;
    this->driver = NULL;
    this->DateEnd = -1;
    this->CarModel = "";
    this->Color = "";
}

Car::Car(const Car &car)
{
    this->id = car.id;
    this->Color = car.Color;
    this->CarModel = car.CarModel;
    this->Place = car.Place;
    this->stateNumber = car.stateNumber;
    this->driver = car.driver;
    this->region = car.region;
    this->DateEnd = car.DateEnd;
}

std::string Car::GetPlace() { return this->Place; }
std::string Car::GetStateNumber() { return this->stateNumber; }
int Car::GetId() { return this->id; }
int Car::GetRegion() { return this->region; }
User *Car::GetDriver() { return this->driver; }
time_t Car::GetDateEnd() { return this->DateEnd; }
std::string Car::GetCarModel() { return this->CarModel; }
std::string Car::GetColor() { return this->Color; }

void Car::SetID(int id) { this->id = id; }
void Car::SetPlace(std::string Place) { this->Place = Place; }
void Car::SetStateNumber(std::string stateNumber) { this->stateNumber = stateNumber; }
void Car::SetRegion(int region) { this->region = region; }
void Car::SetDriver(User *driver) { this->driver = driver; }
void Car::SetDateEnd(time_t DateEnd) { this->DateEnd = DateEnd; }
void Car::SetColor(std::string Color) { this->Color = Color; }
void Car::SetCarModel(std::string CarModel) { this->CarModel = CarModel; }

void Car::PrintInfo()
{
    std::cout << "Автомобиль" << std::endl;
    std::cout << "\tМарка автомобиля : " << this->CarModel << std::endl;
    std::cout << "\tЦвет автомобиля : " << this->Color << std::endl;
    std::cout << "\tМесто: " << this->Place << std::endl;
    std::cout << "\tНомер автомобиля: " << this->stateNumber << " Регион: " << this->region << std::endl;
    std::cout << "\tДата окончания бронирования места: " << this->DateEnd << std::endl; // изменить на нормальный вывод даты
}