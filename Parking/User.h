#ifndef USER_H
#define USER_H

#include <iostream>
#include <list>

class Car; // forward declaration

class User
{
private:
    int id;
    std::string FIO;             // ФИО водителя
    std::string address;         // адрес проживания
    std::string numberPhone;     // номер телефона водителя
    std::string passport_number; // паспортные данные (номер и серия)
    //добавить фото
public:
    User(std::string FIO, std::string address,
         std::string numberPhone, std::string passport_number);
    User();
    ~User();
    int GetId();
    std::string GetFIO();
    std::string GetAddress();
    std::string GetNumberPhone();
    std::string GetPassportNumber();

    void SetID(int id);
    void SetFIO(std::string FIO);
    void SetAddress(std::string adress);
    void SetPassportNumber(std::string passport);
    void SetNumberPhone(std::string numberPhone);
    void PrintInfo();

    void Save();
};
#endif
