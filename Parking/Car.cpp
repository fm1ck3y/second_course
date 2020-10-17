#include <iostream>
#include <time.h>
#include <list>
#include "Car.h"
#include "User.h"

Car::Car(std::string Place, std::string stateNumber, int region, User *driver,
         std::string CarModel, std::string Color)
{
    this->Place = Place;
    this->stateNumber = stateNumber;
    this->region = region;
    this->driver = driver;
    this->DateEnd = time(0);
    this->CarModel = CarModel;
    this->Color = Color;
}
Car::~Car()
{
    
}

Car::Car()
{
    this->Place = "";
    this->stateNumber = "";
    this->region = -1;
    this->driver = NULL;
    this->DateEnd = -1;
    this->CarModel = "";
    this->Color = "";
}

Car::Car(const Car &car)
{
    this->id = car.id;
    this->Color = car.Color;
    this->CarModel = car.CarModel;
    this->Place = car.Place;
    this->stateNumber = car.stateNumber;
    this->driver = car.driver;
    this->region = car.region;
    this->DateEnd = car.DateEnd;
}

std::string Car::GetPlace() { return this->Place; }
std::string Car::GetStateNumber() { return this->stateNumber; }
int Car::GetId() { return this->id; }
int Car::GetRegion() { return this->region; }
User *Car::GetDriver() { return this->driver; }
time_t Car::GetDateEnd() { return this->DateEnd; }
std::string Car::GetCarModel() { return this->CarModel; }
std::string Car::GetColor() { return this->Color; }

void Car::SetPlace(std::string Place) { this->Place = Place; }
void Car::SetStateNumber(std::string stateNumber) { this->stateNumber = stateNumber; }
void Car::SetRegion(int region) { this->region = region; }
void Car::SetDriver(User *driver) { this->driver = driver; }
void Car::SetDateEnd(time_t DateEnd) { this->DateEnd = DateEnd; }
void Car::SetColor(std::string Color) { this->Color = Color; }
void Car::SetCarModel(std::string CarModel) { this->CarModel = CarModel; }

void Car::PrintInfo()
{
    std::cout << "Автомобиль" << std::endl;
    std::cout << "\tМарка автомобиля : " << this->CarModel << std::endl;
    std::cout << "\tЦвет автомобиля : " << this->Color << std::endl;
    std::cout << "\tМесто: " << this->Place << std::endl;
    std::cout << "\tНомер автомобиля: " << this->stateNumber << " Регион: " << this->region << std::endl;
    std::cout << "\tДата окончания бронирования места: " << this->DateEnd << std::endl; // изменить на нормальный вывод даты
}

void Car::Create()
{
    std::string sql = "INSERT INTO Car(CarModel,Color,Place,stateNumber,region,dateEnd,user_id) VALUES ('" + this->CarModel + "','" + this->Color + "', '" + this->Place + "','" + this->stateNumber + "','" + std::to_string(this->region) + "','" + std::to_string(this->DateEnd) + "','" + std::to_string(this->driver->GetId()) + "')";
    Execute(sql);
}

void Car::Select()
{
    char *sql = "Select * From Car";
    sqlite3_stmt *statement_cars;
    if (sqlite3_prepare_v2(db, sql, -1, &statement_cars, 0) == SQLITE_OK)
    {
        while (sqlite3_step(statement_cars) == SQLITE_ROW)
        {
            Car *car = new Car();
            car->id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 0))));
            car->CarModel = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 1)));
            car->Color = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 2)));
            car->Place = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 3)));
            car->stateNumber = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 4)));
            car->region = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 5))));
            car->DateEnd = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 6))));
            int user_id = std::stoi(std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement_cars, 7))));
            
            User::Select();
            for (auto user : User::users)
            {
                if (user->GetId() == user_id)
                {
                    car->driver = user;
                    break;
                }
            }

            // если объект уже существует в списке, то его нужно изменить, а не выделить новую память
            Car *this_car = nullptr;
            for (auto _car : Car::cars)
                if (car->id == _car->id)
                    this_car = _car;
            if (this_car != nullptr)
            {
                if (this_car->CarModel != car->CarModel)
                    this_car->CarModel = car->CarModel;
                if (this_car->Color != car->Color)
                    this_car->Color = car->Color;
                if (this_car->Place != car->Place)
                    this_car->Place = car->Place;
                if (this_car->stateNumber != car->stateNumber)
                    this_car->stateNumber = car->stateNumber;
                if (this_car->region != car->region)
                    this_car->region = car->region;
                if (this_car->DateEnd != car->DateEnd)
                    this_car->DateEnd = car->DateEnd;
                if (this_car->driver != car->driver)
                    this_car->driver = car->driver;
                delete car;
            }
            else
            {
                Car::cars.push_back(car);
            }
        }
        sqlite3_finalize(statement_cars);
    }
}

void Car::Save()
{
    if (this->id == -1)
        this->Create();
    else
    {
        std::string sql = "";
        sql += "UPDATE Car SET CarModel = '" + this->CarModel + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Car SET Color = '" + this->Color + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Car SET Place = '" + this->Place  + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Car SET stateNumber = '" + this->stateNumber  + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Car SET region = '" + std::to_string(this->region)  + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Car SET dateEnd = '" + std::to_string(this->DateEnd)  + "' WHERE id = " + std::to_string(this->id) + ";\n";
        sql += "UPDATE Car SET user_id = '" + std::to_string(this->driver->GetId())  + "' WHERE id = " + std::to_string(this->id) + ";\n";
        Execute(sql);
    }
}


void Car::Delete()
{
    if(this->id != -1)
    {
        std::string sql = "DELETE FROM Car Where id =" + std::to_string(this->id);
        Execute(sql);
    }
    Car::cars.remove(this);
    delete this;
}

std::list<Car *> Car::cars;