#include <iostream>
#include <time.h>
#include "Car.h"
#include "User.h"
#include "Visit.h"
#include "Payment.h"
#include "Database/database.h"

using namespace std;
int main()
{
    User *Artem = new User("Vdovin Artem Adnreevich", "Pushkina d.32 kv 99", "7912355678", "22 13 123456");
    //Artem->PrintInfo();
    Database *db = new Database("/home/m1ck3y/programming/cpp/secondCourse/Parking/Database/mydata.db");
    db->DownloadAllDatabase();
    list<Car*> cars = db->GetAllCars();
    for (auto car : cars){
        car->PrintInfo();
        cout << endl << endl;
    }

    list<User*> users = db->GetAllUsers();
    for (auto user : users){
        user->PrintInfo();
        cout << endl << endl;
    }
}