#pragma once
#ifndef STACK_H
#define STACK_H
template <typename T>
class Stack
{
private:
    class Element
    {
    public:
        T value;       // значение элемента
        Element *next; // следующий элемент
        Element(T value, Element *next)
        {
            this->value = value;
            this->next = next;
        }
    };
    Element *head; // верхний элемент стека
    static int count;

public:
    Stack();                        // конструктор стека
    ~Stack();                       // деструктор стека (очистка памяти)
    T Peek();                       // взять верхний элемент стека
    void Pop();                     // удалить верхний элемент стека
    void Push(T value);             // добавить элемент в стек
    void Clear();                   // очистить стек
    void Print();                   // вывести стек в консоль
    Stack(const Stack &stack);      // конструктор копирование стека (переварачивает стек)
    T &operator[](const int index); // оператор индексации в стеке
    int GetCount();                 // количество элементов в стеке
};

template <typename T>
int Stack<T>::count = 0;
#endif