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
    Database *db = new Database("/home/m1ck3y/programming/cpp/second_course/Parking/Database/mydata.db");
    db->DownloadAllDatabase();
    list<Car*> cars = db->GetAllCars();
    for (auto car : cars){
        car->PrintInfo();
        cout << endl << endl;
    }
    
    //db->AddUserToDatabase(new User("Софронов Лев Владимирович","Lenana 44", "78005553535","22 15 444444"));
    
    //db->AddVisitToDatabase(new Visit(*cars.begin(),time(0),1));
    //db->AddVisitToDatabase(new Visit(*cars.begin(),time(0),0));
    //db->AddPaymentToDatabase(new Payment(time(0),2000.0,*cars.begin()));
    //db->AddPaymentToDatabase(new Payment(time(0),5000.0,*cars.begin()));
    list<User*> users = db->GetAllUsers();
    for (auto user : users){
        user->PrintInfo();
        cout << endl << endl;
    }
    //db->AddCarToDatabase(new Car("B21","Y322KK",152,*(++users.begin()),"Lada Kalina","Black"));
    list<Visit*> visits = db->GetAllVisit();
    for(auto visit : visits)
    {
        visit->PrintInfo();
        cout << endl << endl;
    } 

    list<Payment*> payments = db->GetAllPayment();
    for(auto payment : payments)
    {
        payment->PrintInfo();
        cout << endl << endl;
    } 
}