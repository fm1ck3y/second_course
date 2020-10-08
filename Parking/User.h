#ifndef USER_H
#define USER_H

#include <iostream>
#include <list>

// forward declaration
class Car;

class User
{
private:
    int id;
    std::string FIO;                // ФИО водителя
    std::string address;            // адрес проживания
    std::list<Car *> cars;          // автомобиль водителя
    std::string numberPhone;        // номер телефона водителя
    std::string passport_number;    // паспортные данные (номер и серия)
    //добавить фото
public:
    User(std::string FIO, std::string address,
         std::string numberPhone, std::string passport_number);
    ~User();
    int GetId();
    std::string GetFIO();
    std::string GetAddress();
    std::list<Car *> GetAllCars();
    std::string GetNumberPhone();

    void SetFIO(std::string FIO);
    void SetAddress(std::string adress);
    void AddCar(Car *car);
    void SetNumberPhone(std::string numberPhone);
    void PrintInfo();

    void Save();
};
#endif