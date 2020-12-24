#include "HashTable.cpp"
#include <list>
#include <iostream>
#include <stdlib.h>

enum Menu
{
    Add = 1,
    Delete,
    GetValue,
    Print,
    IsExist,
    Exit
};

void PrintMenu()
{
    std::cout << "1.Add value" << std::endl;
    std::cout << "2.Delete value" << std::endl;
    std::cout << "3.Get value by key" << std::endl;
    std::cout << "4.Print table" << std::endl;
    std::cout << "5.Check on exist" << std::endl;
    std::cout << "6.Exit" << std::endl
              << std::endl;
}

int GetInput()
{
    int menuIn;
    std::cout << "Enter >> ";
    std::cin >> menuIn;
    if (!std::cin)
    {
        std::cin.clear();
        std::cin.ignore(INT64_MAX, '\n');
        return -1;
    }
    return menuIn;
}

template <typename K, typename V>
bool HandlerMenu(int menuIn, HashTable<K, V> *hashtab)
{
    system("clear");
    switch (menuIn)
    {
    case Menu::Add:
    {
        V value;
        K key;
        std::cout << "Enter key for add >> ";
        std::cin >> key;
        std::cout << "Enter value for add >> ";
        std::cin >> value;
        hashtab->Add(key, value);
        std::cout << "Value added successfully!" << std::endl;
        break;
    }

    case Menu::Delete:
    {
        K key;
        std::cout << "Enter key for delete >> ";
        std::cin >> key;
        hashtab->Remove(key);
        std::cout << "Value is removed." << std::endl;
        break;
    }

    case Menu::GetValue:
    {
        K key;
        std::cout << "Enter key for get >> ";
        std::cin >> key;
        if (!hashtab->IsExist(key)){
            std::cout << "Value not found." << std::endl;
            break;
        }
        std::cout << std::endl
                  << "Table[" << key << "] = " << (*hashtab)[key] << std::endl;
        break;
    }

    case Menu::Print:
    {
        hashtab->Print();
        break;
    }

    case Menu::IsExist:
    {
        K key;
        std::cout << "Enter key for check >> ";
        std::cin >> key;
        if (hashtab->IsExist(key))
            std::cout << "Value found." << std::endl;
        else
            std::cout << "Value not found." << std::endl;
        break;
    }

    case Menu::Exit:
        return true;

    default:
    {
        std::cout << "Invalid enter number. Try again." << std::endl;
        break;
    }
    }
    std::cout << std::endl;
    return false;
}

int main(void)
{
    HashTable<std::string, int> *hashtab = new HashTable<std::string, int>(17);
    bool IsExit = false;
    system("clear");
    while (!IsExit)
    {
        PrintMenu();
        int menuIn = GetInput();
        IsExit = HandlerMenu(menuIn, hashtab);
    }

    /*
    HashTable<std::string, int> *hashtab = new HashTable<std::string, int>(17);
    hashtab->Add("hello", 22);
    hashtab->Add("world", 333);
    hashtab->Add("kek", 999);
    hashtab->Add("Hello world", -25);
    hashtab->Print();
    std::cout << "Value by key: 'kek' => " << (*hashtab)["kek"] << std::endl;
    std::cout << "Key 'kek' is exist =>'" << hashtab->IsExist("kek") << std::endl;
    std::cout << "Key 'l' is exist =>'" << hashtab->IsExist("l") << std::endl
              << std::endl;
    hashtab->Print();
    */
    delete hashtab;
}