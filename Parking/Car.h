#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <time.h>
#include <list>
#include "db/database.h"

class User; // forward declaration

class Car : Database
{
private:
    int id;
    std::string CarModel;    // модель автомобиля
    std::string Color;       // цвет автомобиля
    std::string Place;       // место на парковке
    std::string stateNumber; // государственный номер автомобиля
    User *driver;            // владелец авто
    int region;              // регион
    time_t DateEnd;          // дата окончания оплаты за место
public:
    Car();
    Car(std::string Place, std::string stateNumber, int region, User *driver,
        std::string CarModel, std::string Color);
    Car(const Car &car);
    ~Car();
    int GetId();
    std::string GetPlace();
    std::string GetStateNumber();
    std::string GetCarModel();
    std::string GetColor();
    int GetRegion();
    User *GetDriver();
    time_t GetDateEnd();

    void SetID(int id);
    void SetPlace(std::string Place);
    void SetStateNumber(std::string stateNumber);
    void SetRegion(int region);
    void SetDriver(User *driver);
    void SetDateEnd(time_t DateEnd);
    void SetColor(std::string Color);
    void SetCarModel(std::string CarModel);
    void PrintInfo();

    void Create() override final;
};
#endif