#pragma once
#ifndef STACK_H
#define STACK_H

#define MAX_STACK  100
template <typename T>
class Stack
{
private:
    const int max_stack = MAX_STACK;
    T *array = new T[MAX_STACK];
    int head;

public:
    Stack();                   // конструктор стека
    ~Stack();                  // деструктор стека (очистка памяти)
    T Peek();                  // взять верхний элемент стека
    T Pop();                   // удалить верхний элемент стека
    void Push(T value);        // добавить элемент в стек
    void Clear();              // очистить стек
    Stack(const Stack &stack); // конструктор копирование стека (переварачивает стек)
    int GetCount();            // количество элементов в стеке
};
#endif