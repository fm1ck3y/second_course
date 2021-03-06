#ifndef USER_H
#define USER_H

#include <iostream>
#include <list>
#include "db/database.h"
#include <any>

class Car; // forward declaration

class User : Database
{
private:
    int id;
    std::string FIO;             // ФИО водителя
    std::string address;         // адрес проживания
    std::string numberPhone;     // номер телефона водителя
    std::string passport_number; // паспортные данные (номер и серия)
    //добавить фото
public:
    static std::list<User *> users; // список всех пользователей
    User(std::string FIO, std::string address,
         std::string numberPhone, std::string passport_number); // конструктор с параметрами
    User();                                                     // обычный конструктор
    ~User();                                                    // деструктор
    User(const User &user);                                     // конструктор копирования
    int GetId();
    std::string GetFIO();
    std::string GetAddress();
    std::string GetNumberPhone();
    std::string GetPassportNumber();

    void SetFIO(std::string FIO);
    void SetAddress(std::string adress);
    void SetPassportNumber(std::string passport);
    void SetNumberPhone(std::string numberPhone);
    void PrintInfo();

    void Create() override final;
    void Save() override final;
    void Delete() override final;
    static void Select(); // загрузка из БД
};
#endif
