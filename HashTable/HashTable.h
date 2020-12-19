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
    HashInfo(K k, V v) : key(k), value(v){};
    HashInfo() : key(0), value(0){};
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

template <typename K, typename V>
class HashTable
{

private:
    uint8_t size;
    std::list<HashInfo<K, V>> **table;
    uint8_t HashFunc(int);
    uint8_t HashFunc(std::string);

public:
    ~HashTable();
    HashTable(uint8_t size);
    HashTable(const HashTable &);
    void Add(K key, V value);
    void Remove(K Key);
    void Print();
    bool IsExist(K key);
    V &operator[](const K key);
};

#endif