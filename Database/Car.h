#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <time.h>
#include <list>
// forward declaration
class HistoryVisit;
class User;

class Car
{
private:
    static int _id;
    int id;
    std::string CarModel;                   // модель автомобиля
    std::string Color;                      // цвет автомобиля
    std::string Place;                      // место на парковке
    std::string stateNumber;                // государственный номер автомобиля
    int region;                             // регион
    User *driver;                           // водитель (владелец)
    std::list<HistoryVisit *> historyVisit; // история посещений стоянки
    time_t DateEnd;                         // дата окончания оплаты за место
public:
    Car(std::string Place, std::string stateNumber, int region, User *driver,
    std::string CarModel ,  std::string Color);
    ~Car();
    int GetId();
    std::string GetPlace();
    std::string GetStateNumber();
    std::string GetCarModel();
    std::string GetColor();
    int GetRegion();
    User *GetDriver();
    std::list<HistoryVisit *> GetAllHistoryVisit();
    time_t GetDateEnd();

    void SetPlace(std::string Place);
    void AddHistoryVisit(HistoryVisit *historyVisit);
    void SetStateNumber(std::string stateNumber);
    void SetRegion(int region);
    void SetDriver(User *driver);
    void SetDateEnd(time_t DateEnd);
    void SetColor(std::string Color);
    void SetCarModel(std::string CarModel);
    void PrintInfo();
};
#endif