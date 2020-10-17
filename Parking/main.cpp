#include <iostream>
#include <time.h>
#include "Car.h"
#include "User.h"
#include "Visit.h"
#include "Payment.h"
#include "db/database.h"

using namespace std;
int main()
{
    Database::name_db = "/home/m1ck3y/programming/cpp/secondCourse/Parking/db/mydata.db";
    Database::Connect();

    User::Select();
    Visit::Select();
    Payment::Select();
    Car::Select();

    for (auto user : User::users)
    {
        user->PrintInfo();
        cout << endl
             << endl;
    }
    cout << "-----------------------------------" << endl;
    for (auto car : Car::cars)
    {
        car->PrintInfo();
        cout << endl
             << endl;
    }
    cout << "-----------------------------------" << endl;
    for (auto visit : Visit::visits)
    {
        visit->PrintInfo();
        cout << endl
             << endl;
    }
    cout << "-----------------------------------" << endl;
    for (auto payment : Payment::payments)
    {
        payment->PrintInfo();
        cout << endl
             << endl;
    }

    // пример того, что при загрузке БД , новая память не выделяется
    User *user = *(User::users.begin());
    user->SetFIO("Софронов Лев Владимирович");
    user->Save();
    User::Select();
    cout << user->GetFIO() << endl;
    user->Delete();
    //User::Select();
    cout << "-----------------------------------" << endl;
    for (auto user : User::users)
    {
        user->PrintInfo();
        cout << endl
             << endl;
    }
    cout << "-----------------------------------" << endl;
    //user->Delete();
    //cout << user->GetFIO() << endl;
    for (auto user : User::users) delete user;
    for (auto payment : Payment::payments) delete payment;
    for (auto visit : Visit::visits) delete visit;
    for (auto car : Car::cars) delete car;
    Visit::visits = nullptr;
    Database::Disconnect();
    //User *user = new User("Вдовин Артём Андреевич","Линина 71", "78005553535","22 15 333333");
    //user->Create();
}