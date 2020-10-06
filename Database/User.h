#ifndef USER_H
#define USER_H

#include <iostream>
#include <list>

// forward declaration
class HistoryPayment;
class Car;

class User
{
private:
    static int _id;
    int id;
    std::string FIO;                // ФИО водителя
    std::string address;            // адрес проживания
    std::list<Car *> cars;          // автомобиль водителя
    std::list<HistoryPayment*> historyPayment; // история оплаты места
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
    std::list<HistoryPayment*> GetAllHistoryPayment();
    std::string GetNumberPhone();

    void SetFIO(std::string FIO);
    void SetAddress(std::string adress);
    void AddCar(Car *car);
    void AddToHistoryPayment(HistoryPayment *historyPayment);
    void SetNumberPhone(std::string numberPhone);
    void PrintInfo();
};
#endif
