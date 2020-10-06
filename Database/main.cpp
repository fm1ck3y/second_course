#include <iostream>
#include <time.h>
#include "Car.cpp"
#include "User.cpp"
#include "HistoryVisit.cpp"
#include "HistoryPayment.cpp"

int main()
{
    User *Artem = new User("Vdovin Artem Adnreevich","Pushkina d.32 kv 99", "7912355678", "22 13 123456");
    Car *car = new Car("A21","Y775KK",52,Artem,"Mitsubishi Lancer X", "Red");
    car->PrintInfo();
}