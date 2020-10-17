#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#define MAX_QUEUE 100

template <typename T>
class Queue
{
private:
    T *array = new T[MAX_QUEUE];
    int start;
    int end;

public:
    Queue();                   // конструктор
    ~Queue();                  // деструктор (очистка памяти)
    T Dequeue();               // добавить элемент в очередь
    T Peek();                  // верхний элемент
    void Enqueue(T value);     // удалить последний элемент
    bool IsEmpty();            // пустая очередь или нет
    void Print();              // вывод очереди
    Queue(const Queue &queue); // конструктор копирование
};
#endif