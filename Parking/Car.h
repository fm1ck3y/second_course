#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <time.h>
#include <list>
// forward declaration
class Payment;
class Visit;
class User;

class Car
{
private:
    int id;
    std::string CarModel;                       // модель автомобиля
    std::string Color;                          // цвет автомобиля
    std::string Place;                          // место на парковке
    std::string stateNumber;                    // государственный номер автомобиля
    int region;                                 // регион
    User *driver;                               // водитель (владелец)
    std::list<Visit *> historyVisit;     // история посещений стоянки
    std::list<Payment *> historyPayment; // история оплаты места
    time_t DateEnd;                             // дата окончания оплаты за место
public:
    Car(std::string Place, std::string stateNumber, int region, User *driver,
        std::string CarModel, std::string Color);
    ~Car();
    int GetId();
    std::string GetPlace();
    std::string GetStateNumber();
    std::string GetCarModel();
    std::string GetColor();
    int GetRegion();
    User *GetDriver();
    std::list<Payment*> GetAllHistoryPayment();
    std::list<Visit *> GetAllHistoryVisit();
    time_t GetDateEnd();

    void SetPlace(std::string Place);
    void AddToHistoryVisit(Visit *historyVisit);
    void SetStateNumber(std::string stateNumber);
    void SetRegion(int region);
    void AddToHistoryPayment(Payment *payment);
    void SetDriver(User *driver);
    void SetDateEnd(time_t DateEnd);
    void SetColor(std::string Color);
    void SetCarModel(std::string CarModel);
    void PrintInfo();
};
#endif