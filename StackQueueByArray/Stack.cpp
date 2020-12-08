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
    if (head >= MAX_STACK)
        std::cerr << "Stack is full" << std::endl;
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
    int counter = stack.head;
    while (counter >= 0){
        this->array[counter] = stack.array[counter];
        counter--;
    }
}

template <typename T>
int Stack<T>::GetCount() { return this->head + 1; }
