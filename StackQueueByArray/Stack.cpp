#include <iostream>
#include "Stack.h"

template <typename T>
Stack<T>::Stack()
{
    this->head = -1;
}

template <typename T>
Stack<T>::~Stack()
{
    // this->Clear();
    free(array);
}

template <typename T>
T Stack<T>::Peek()
{
    if (this->head == -1)
        std::cerr << "Head is NULL" << std::endl;
    return this->array[head];
}

template <typename T>
void Stack<T>::Push(T value)
{
    this->array[++head] = value;
}

template <typename T>
T Stack<T>::Pop()
{
    if (this->head == -1)
        std::cerr << "Head is NULL" << std::endl;
    else
        return this->array[head--];
}

template <typename T>
void Stack<T>::Clear()
{
    while (this->head != -1)
        this->Pop();
}

template <typename T>
Stack<T>::Stack(const Stack &stack)
{
    this->head = stack.head;
    int _head = stack.head;
    while (stack.head != -1)
        this->array[_head--] = stack.array[_head];
}

template <typename T>
int Stack<T>::GetCount() { return this->head + 1; }
