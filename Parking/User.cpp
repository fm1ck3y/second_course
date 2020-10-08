#include <iostream>
#include <list>
#include "Car.h"
#include "User.h"
#include "Database/database.cpp"
User::User(std::string FIO, std::string address,
           std::string numberPhone, std::string passport_number)
{
    this->id = NULL;
    this->FIO = FIO;
    this->address = address;
    this->numberPhone = numberPhone;
    this->passport_number = passport_number;
}

User::~User()
{
    for (auto car : this->cars)
        delete car;
}

int User::GetId() { return this->id; }
std::string User::GetFIO() { return this->FIO; }
std::string User::GetAddress() { return this->address; }
std::list<Car *> User::GetAllCars() { return this->cars; }
std::string User::GetNumberPhone() { return this->numberPhone; }

void User::SetFIO(std::string FIO) { this->FIO = FIO; }
void User::SetAddress(std::string adress) { this->address = address; }
void User::AddCar(Car *car) { this->cars.push_back(car); }
void User::SetNumberPhone(std::string numberPhone) { this->numberPhone = numberPhone; }
void User::Save()
{
    if (this->id == NULL)
    {
        try
        {
            Database *db = new Database("/home/m1ck3y/programming/cpp/secondCourse/Parking/Database/mydata.db");
            db->AddUserToDatabase(this->FIO, this->address, this->numberPhone, this->passport_number);
            delete db;
        }
        catch (std::string err)
        {
            std::cerr << err << std::endl;
        }
    }
}

void User::PrintInfo()
{
    std::cout << "Владелец: " << std::endl;
    std::cout << "\tФИО : " << this->FIO << std::endl;
    std::cout << "\tАдрес : " << this->address << std::endl;
    std::cout << "\tНомер телефона : " << this->numberPhone << std::endl;
    std::cout << "\tПаспортные данные : " << this->passport_number << std::endl;
}