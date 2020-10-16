#include <iostream>
#include <list>
#include <any>
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

void User::Create()
{
    std::string sql = "INSERT INTO User(FIO,address,numberPhone,passport_number) VALUES ('" + this->FIO + "', '" + this->address + "', '" + this->numberPhone + "', '" + this->passport_number + "')";
    Execute(sql);
}

void User::Select()
{
    char *sql = "Select * From User";
    sqlite3_stmt *statement_users;
    if (sqlite3_prepare_v2(db, sql, -1, &statement_users, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement_users) == SQLITE_ROW)
        {
            User *user = new User();
            user->id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_users, 0))));
            user->FIO = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_users, 1)));
            user->address = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_users, 2)));
            user->passport_number = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_users, 3)));
            user->numberPhone = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_users, 4)));

            User *this_user = nullptr;
            for (auto _user : User::users)
                if (user->id == _user->id)
                    this_user = _user;
            if (this_user != nullptr)
            {
                if (this_user->FIO != user->FIO)
                    this_user->FIO = user->FIO;
                if (this_user->address != user->address)
                    this_user->address = user->address;
                if (this_user->passport_number != user->passport_number)
                    this_user->passport_number = user->passport_number;
                if (this_user->numberPhone != user->numberPhone)
                    this_user->numberPhone = user->numberPhone;
                delete user;
            }
            else
            {
                User::users.push_back(user);
            }
        }
        sqlite3_finalize(statement_users);
    }
}
std::list<User *> User::users;