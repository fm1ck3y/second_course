#pragma once
#ifndef DBLLISTH_H
#define DBLLISTH_H
template <typename T>
class List
{
private:
    class Node
    {
    public:
        T value;    // значение элемента
        Node *next; // следующий элемент
        Node *prev; // предыдущий элемент
        Node(T value, Node *next, Node *prev)
        {
            this->value = value;
            this->next = next;
            this->prev = prev;
        }
    };
    Node *head;       // верхний элемент спиcка
    Node *tail;       // нижний элемент списка
    static int Count; // количество элементов списка

public:
    List();                         // конструктор списка
    ~List();                        // деструктор списка (очистка памяти)
    List(const List &list);         // конструктор копирование списка
    T &operator[](const int index); // оператор индексации в списке
    int GetCount();                 // количество элементов в списке
    void Add(T value);              // добавление элемента в список
    void Delete(int index);         // удаление элемента из списка по индексу
    void Clear();                   // очищение спика
    void Print();                   // вывести все  элементы на экран
};

template <typename T>
int List<T>::Count = 0;
#endif