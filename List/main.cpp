#include <iostream>
#include "List.cpp"
using namespace std;

int main()
{
    List<int> list;
    list.Add(5);
    list.Add(7);
    list.Add(4);
    list.Add(3);
    list.Add(1);
    list.Add(9);
    list.Print();
    cout << "Second node in list: " << list[1] << endl;
    list.Delete(1);
    cout << "Second node in list: " << list[1] << endl;
    list.Print();
    list.Clear();
    list.Print();
    cout << "Count nodes in list: " << list.GetCount() << endl;
    cout << "Second node in list: " << list[2] << endl;
}