#include <iostream>
#include <time.h>
#include "Visit.h"
#include "Car.h"
#include <any>
Visit::Visit(Car *car, time_t Date, bool arrival)
{
    this->car = car;
    this->date = date;
    this->arrival = arrival;
}
Visit::Visit()
{
    this->car = nullptr;
    this->date = 0;
    this->arrival = false;
}

Visit::Visit(const Visit &visit)
{
    this->id = visit.id;
    this->car = visit.car;
    this->date = visit.date;
    this->arrival = visit.arrival;
}
Visit::~Visit()
{
    
}

int Visit::GetId() { return this->id; }
Car *Visit::GetCar() { return this->car; }
time_t Visit::GetDate() { return this->date; }
bool Visit::IsArrival() { return this->arrival; }

void Visit::SetCar(Car *car) { this->car = car; }
void Visit::SetDate(time_t date) { this->date = date; }
void Visit::SetArrival(bool arrival) { this->arrival = arrival; }

void Visit::PrintInfo()
{
    std::cout << "Запись посещения парковки: " << std::endl;
    if (this->arrival)
        std::cout << "\tАвтомобиль заехал" << std::endl;
    else
        std::cout << "\tАвтомобиль выехал" << std::endl;
    std::cout << "\tДата: " << this->date << std::endl;
    this->car->PrintInfo();
}

void Visit::Create()
{
    std::string sql = "INSERT INTO Visit(date,arrival,car_id) VALUES ('" + std::to_string(this->date) + "','" + std::to_string(this->arrival) + "', '" + std::to_string(this->car->GetId()) + "')";
    Execute(sql);
}

void Visit::Select()
{
    char *sql = "Select * From Visit";
    sqlite3_stmt *statement_visit;
    if (sqlite3_prepare_v2(db, sql, -1, &statement_visit, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement_visit) == SQLITE_ROW)
        {
            Visit *visit = new Visit();
            visit->id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_visit, 0))));
            visit->date = std::stol(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_visit, 1))));
            visit->arrival = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_visit, 2))));
            int car_id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_visit, 3))));
            Car::Select();
            for (auto car : Car::cars)
            {
                if (car->GetId() == car_id)
                {
                    visit->car = car;
                    break;
                }
            }
            Visit *this_visit = nullptr;
            for (auto _visit : Visit::visits)
                if (visit->id == _visit->id)
                    this_visit = _visit;
            if (this_visit != nullptr)
            {
                if (this_visit->date != visit->date)
                    this_visit->date = visit->date;
                if (this_visit->arrival != visit->arrival)
                    this_visit->arrival = visit->arrival;
                if (this_visit->car != visit->car)
                    this_visit->car = visit->car;
                delete visit;
            }
            else
            {
                Visit::visits.push_back(visit);
            }
        }
        sqlite3_finalize(statement_visit);
    }
}

void Visit::Save()
{
    if (this->id == -1)
        this->Create();
    else
    {
        std::string sql = "";
        sql += "UPDATE Visit SET date = '" + std::to_string(this->date) + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Visit SET arrival = '" + std::to_string(this->arrival) + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Visit SET car_id = '" + std::to_string(this->car->GetId()) + "' WHERE id = " + std::to_string(this->id) + ";\n";
        Execute(sql);
    }
}

void Visit::Delete()
{
    if(this->id != -1)
    {
        std::string sql = "DELETE FROM Visit Where id =" + std::to_string(this->id);
        Execute(sql);
    }
    delete this;
}

std::list<Visit *> Visit::visits;