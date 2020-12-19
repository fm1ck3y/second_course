#include "HashTable.cpp"
#include <list>
#include <iostream>
int main(void)
{
    // std::list<HashInfo<int,int>> ** table = (std::list<HashInfo<int,int>> **)malloc(9 * sizeof(std::list<HashInfo<int,int>>));
    // for(std::size_t i = 0 ; i < 9; i++)
    //     table[i] = new std::list<HashInfo<int,int>>();
    // std::list<HashInfo<int,int>> *_l = table[1];
    // HashInfo<int,int> *hs = new HashInfo<int,int>(1,2);
    // _l->push_back(*hs);
    // for (auto el : *_l)
    //    std::cout << el << std::endl;

    HashTable<std::string, int> *hashtab = new HashTable<std::string, int>(4);
    hashtab->Add("hello", 22);
    hashtab->Add("world", 333);
    hashtab->Add("kek", 999);
    hashtab->Print();
    std::cout << (*hashtab)["kek"] << std::endl;
    std::cout << hashtab->IsExist("kek") << std::endl;
    std::cout << hashtab->IsExist("l") << std::endl << std::endl;
    hashtab->Print();
    delete hashtab;
}