#include "HashTable.cpp"
#include <list>
#include <iostream>

int main(void)
{
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
    delete hashtab;
}