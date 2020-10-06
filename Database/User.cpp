#include <iostream>
#include <list>
#include "Car.h"
#include "HistoryPayment.h"
#include "User.h"

User::User(std::string FIO, std::string address,
           std::string numberPhone, std::string passport_number)
{
    this->FIO = FIO;
    this->address = address;
    this->numberPhone = numberPhone;
    this->passport_number = passport_number;
}
User::~User()
{
    for (auto payment : this->historyPayment)
        delete payment;
    for (auto car : this->cars)
        delete car;
}

int User::GetId() { return this->id; }
std::string User::GetFIO() { return this->FIO; }
std::string User::GetAddress() { return this->address; }
std::list<Car *> User::GetAllCars() { return this->cars; }
std::list<HistoryPayment *> User::GetAllHistoryPayment() { return this->historyPayment; }
std::string User::GetNumberPhone() { return this->numberPhone; }

void User::SetFIO(std::string FIO) { this->FIO = FIO; }
void User::SetAddress(std::string adress) { this->address = address; }
void User::AddCar(Car *car) { this->cars.push_back(car); }
void User::AddToHistoryPayment(HistoryPayment *historyPayment) { this->historyPayment.push_back(historyPayment); }
void User::SetNumberPhone(std::string numberPhone) { this->numberPhone = numberPhone;}

void User::PrintInfo(){
    std::cout << "Владелец:" << std::endl;
    std::cout << "\tФИО :\t" << this->FIO << std::endl;
    std::cout << "\tАдрес :\t" << this->address << std::endl;
    std::cout << "\tНомер телефона :\t" << this->numberPhone << std::endl;
    std::cout << "\tПаспортные данные :\t" << this->passport_number << std::endl;
}