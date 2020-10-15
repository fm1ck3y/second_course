#include <iostream>
#include <list>
#include "User.h"

User::User(std::string FIO, std::string address,
           std::string numberPhone, std::string passport_number)
{
    this->id = -1;
    this->FIO = FIO;
    this->address = address;
    this->numberPhone = numberPhone;
    this->passport_number = passport_number;
}
User::User()
{
    this->id = -1;
    this->FIO = "";
    this->address = "";
    this->numberPhone = "";
    this->passport_number = "";
}


User::~User() {}

User::User(const User &user)
{
    this->id = user.id;
    this->address = user.address;
    this->FIO = user.FIO;
    this->numberPhone = user.numberPhone;
    this->passport_number = passport_number;
}

int User::GetId() { return this->id; }
std::string User::GetFIO() { return this->FIO; }
std::string User::GetAddress() { return this->address; }
std::string User::GetNumberPhone() { return this->numberPhone; }
std::string User::GetPassportNumber() { return this->passport_number; }

void User::SetID(int id) { this->id = id; }
void User::SetFIO(std::string FIO) { this->FIO = FIO; }
void User::SetAddress(std::string address) { this->address = address; }
void User::SetNumberPhone(std::string numberPhone) { this->numberPhone = numberPhone; }
void User::SetPassportNumber(std::string passport) { this->passport_number = passport; }

void User::PrintInfo()
{
    std::cout << "Владелец: " << std::endl;
    std::cout << "\tФИО : " << this->FIO << std::endl;
    std::cout << "\tАдрес : " << this->address << std::endl;
    std::cout << "\tНомер телефона : " << this->numberPhone << std::endl;
    std::cout << "\tПаспортные данные : " << this->passport_number << std::endl;
}