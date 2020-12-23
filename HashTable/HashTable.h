#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <iostream>
#include <list>

template <typename K, typename V>
class HashInfo
{
public:
    K key;
    V value;
    HashInfo(K k, V v) : key(k), value(v){}; // constructor HashInfo
    HashInfo() : key(0), value(0){};         // defualt constructor HashInfo
};

template <typename K, typename V>
std::ostream &operator<<(std::ostream &out, const HashInfo<K, V> hi)
{
    return out << "[" << hi.key << " : " << hi.value << "] ";
};

template <typename K, typename V>
bool operator==(const HashInfo<K, V> &hashinfo_1, const HashInfo<K, V> &hashinfo_2)
{
    return (hashinfo_1.key == hashinfo_2.key) && (hashinfo_1.value == hashinfo_2.value);
};

// K - key type, V - value type
template <typename K, typename V>
class HashTable
{

private:
    uint8_t size;
    std::list<HashInfo<K, V>> **table; // array list
    uint8_t HashFunc(int);
    uint8_t HashFunc(std::string);
    const uint8_t p = 17; // for polinom hashfunc string

public:
    ~HashTable();                 // destructor
    HashTable(uint8_t size);      // constructor hashtable
    HashTable(const HashTable &); // copy constructor
    void Add(K key, V value);     // add value in hashtable
    void Remove(K Key);           // remove value by key
    void Print();                 // print all key => value with hash
    bool IsExist(K key);          // check value by key
    V &operator[](const K key);   // get value by key
};

#endif