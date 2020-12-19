#include "HashTable.h"
#include <iostream>
#include <string>

template <typename K, typename V>
HashTable<K, V>::HashTable(uint8_t size)
{
    if ((!std::is_same<K, int>::value && !std::is_same<K, std::string>::value) || (!std::is_same<V, int>::value && !std::is_same<V, std::string>::value))
        std::cerr << "type not supported" << std::endl;
    this->table = (std::list<HashInfo<K, V>> **)malloc(size * sizeof(std::list<HashInfo<K, V>>));
    for (std::size_t i = 0; i < size; i++)
        this->table[i] = new std::list<HashInfo<K, V>>();
    this->size = size;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    for (std::size_t i = 0; i <= this->size; i++)
        delete this->table[i];
    free(this->table);
}

template <typename K, typename V>
uint8_t HashTable<K, V>::HashFunc(int key)
{
    return key % this->size;
}

template <typename K, typename V>
uint8_t HashTable<K, V>::HashFunc(std::string key)
{
    uint64_t hashvalue, pow_p = 1;
    for (std::size_t i = 0; i < key[i] != '\0'; i++){
        hashvalue += (uint64_t)key[i]*pow_p % this->size;
        pow_p *= this->p;
    }
    return hashvalue % this->size;
}

template <typename K, typename V>
void HashTable<K, V>::Add(K key, V value)
{
    uint8_t hashkey = this->HashFunc(key);
    HashInfo<K, V> *hs = new HashInfo<K, V>(key, value);
    std::list<HashInfo<K, V>> *_l = table[hashkey];
    _l->push_back(*hs);
    delete hs;
}

template <typename K, typename V>
void HashTable<K, V>::Print()
{
    std::cout << "{" << std::endl;
    for (std::size_t i = 0; i < this->size; i++)
    {
        std::list<HashInfo<K, V>> l = *this->table[i];
        if (l.size() <= 0)
            continue;
        std::cout << "\t" << i << " => "
                  << "[ ";
        for (auto el : l)
            std::cout << el;
        std::cout << "]" << std::endl;
    }
    std::cout << "}\n";
}

template <typename K, typename V>
void HashTable<K, V>::Remove(K key)
{
    uint8_t hashkey = this->HashFunc(key);
    std::list<HashInfo<K, V>> *_l = table[hashkey];
    for (auto it = _l->begin(); it != _l->end(); it++)
        if (key == it->key)
        {
            _l->remove(*it);
            return;
        }
}

template <typename K, typename V>
bool HashTable<K, V>::IsExist(K key)
{
    uint8_t hashkey = this->HashFunc(key);
    std::list<HashInfo<K, V>> *_l = table[hashkey];
    for (auto it = _l->begin(); it != _l->end(); it++)
        if (key == it->key)
        {
            return true;
        }
    return false;
}

template <typename K, typename V>
V &HashTable<K, V>::operator[](const K key)
{
    uint8_t hashkey = this->HashFunc(key);
    std::list<HashInfo<K, V>> *_l = table[hashkey];
    for (auto it = _l->begin(); it != _l->end(); it++)
        if (key == it->key)
        {
            return it->value;
        }
}
