#include <iostream>
#include <time.h>
#include "Car.cpp"
#include "User.cpp"
#include "Visit.cpp"
#include "Payment.cpp"

using namespace std;
int main()
{
    User *Artem = new User("Vdovin Artem Adnreevich", "Pushkina d.32 kv 99", "7912355678", "22 13 123456");
    Artem->PrintInfo();
    Artem->Save();
    Car *car = new Car("A21", "Y775KK", 52, Artem, "Mitsubishi Lancer X", "Red");
    car->AddToHistoryPayment(new Payment(time(0), 2000., car));
    car->AddToHistoryPayment(new Payment(time(0), 5000., car));
    car->AddToHistoryVisit(new Visit(car,time(0),true));
    car->AddToHistoryVisit(new Visit(car,time(0),false));
    for (auto hp : car->GetAllHistoryPayment())
    {
        hp->PrintInfo();
        cout << endl << endl;
    }

    for (auto hv : car->GetAllHistoryVisit())
    {
        hv->PrintInfo();
        cout << endl << endl;
    }
}