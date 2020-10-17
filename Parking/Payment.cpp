#include <iostream>
#include <time.h>
#include "Payment.h"
#include "Car.h"

Payment::Payment(time_t Date, double amount, Car *car)
{
    this->car = car;
    this->Date;
    this->amount = amount;
}

Payment::Payment()
{
    this->car = nullptr;
    this->Date = -1;
    this->amount = -1;
}

Payment::Payment(const Payment &payment)
{
    this->id = payment.id;
    this->Date = payment.Date;
    this->amount = payment.amount;
    this->car = payment.car;
}

double Payment::GetAmount() { return this->amount; }
Car *Payment::GetCar() { return this->car; }
time_t Payment::GetDate() { return this->Date; }
int Payment::GetId() { return this->id; }

void Payment::SetAmount(double amount) { this->amount = amount; }
void Payment::SetCar(Car *car) { this->car = car; }
void Payment::SetDate(time_t date) { this->Date = date; }
void Payment::PrintInfo()
{
    std::cout << "Оплата: " << std::endl;
    std::cout << "\tДата: " << this->Date << std::endl;
    std::cout << "\tСумма оплаты: " << this->amount << std::endl;
    this->car->PrintInfo();
}

void Payment::Create()
{
    std::string sql = "INSERT INTO Payment(date,amount,car_id) VALUES ('" + std::to_string(this->Date) + "','" + std::to_string(this->amount) + "', '" + std::to_string(this->car->GetId()) + "')";
    Execute(sql);
}

void Payment::Select()
{
    char *sql = "Select * From Payment";
    sqlite3_stmt *statement_cars;
    if (sqlite3_prepare_v2(db, sql, -1, &statement_cars, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement_cars) == SQLITE_ROW)
        {
            Payment *payment = new Payment();
            payment->id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 0))));
            payment->Date = std::stol(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 1))));
            payment->amount = std::stof(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 2))));
            int car_id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 3))));
            Car::Select();
            for (auto car : Car::cars)
            {
                if (car->GetId() == car_id)
                {
                    payment->car = car;
                    break;
                }
            }
            
            // если объект уже существует в списке, то его нужно изменить, а не выделить новую память
            Payment *this_payment = nullptr;
            for (auto _payment : Payment::payments)
                if (payment->id == _payment->id)
                    this_payment = _payment;
            if (this_payment != nullptr)
            {
                if (this_payment->Date != payment->Date)
                    this_payment->Date = payment->Date;
                if (this_payment->amount != payment->amount)
                    this_payment->amount = payment->amount;
                if (this_payment->car != payment->car)
                    this_payment->car = payment->car;
                delete payment;
            }
            else
            {
                Payment::payments.push_back(payment);
            }
        }
        sqlite3_finalize(statement_cars);
    }
}

void Payment::Save()
{
    if (this->id == -1)
        this->Create();
    else
    {
        std::string sql = "";
        sql += "UPDATE Payment SET date = '" + std::to_string(this->Date) + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Payment SET amount = '" + std::to_string(this->amount) + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Payment SET car_id = '" + std::to_string(this->car->GetId()) + "' WHERE id = " + std::to_string(this->id) + ";\n";
        Execute(sql);
    }
}

void Payment::Delete()
{
    if (this->id != -1)
    {
        std::string sql = "DELETE FROM Payment Where id =" + std::to_string(this->id);
        Execute(sql);
    }
    Payment::payments.remove(this);
    delete this;
}

std::list<Payment *> Payment::payments;