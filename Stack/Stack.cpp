#include <iostream>
#include "Stack.h"
using namespace std;

template <typename T>
Stack<T>::Stack()
{
    this->head = NULL;
}

template <typename T>
Stack<T>::~Stack()
{
    this->Clear();
}

template <typename T>
T Stack<T>::Peek()
{
    if (this->head == NULL)
        std::cerr << "Head is null" << std::endl;
    return this->head->value;
}

template <typename T>
void Stack<T>::Push(T value)
{
    this->head = new Element(value, this->head);
    count++;
}

template <typename T>
void Stack<T>::Pop()
{
    if (this->head == NULL)
    {
        std::cerr << "Head is null" << std::endl;
    }
    else
    {
        Element *next = this->head->next;
        delete this->head;
        this->head = next;
        count--;
    }
}

template <typename T>
void Stack<T>::Clear()
{
    while (this->head != NULL)
        this->Pop();
}

template <typename T>
void Stack<T>::Print()
{
    if (head == NULL)
    {
        cout << "Stack is empty" << endl;
    }
    Element *head = this->head;
    while (head != NULL)
    {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}
template <typename T>
Stack<T>::Stack(const Stack &stack)
{
    Element *head = stack.head;
    while (head != NULL)
    {
        this->Push(head->value);
        head = head->next;
    }
}

template <typename T>
T &Stack<T>::operator[](const int index)
{
    int i = 0;
    if (index > this->count)
    {
        std::cerr << "Index out of the stack" << std::endl;
    }
    Element *head = this->head;
    while (count - i - 1 != index)
    {
        head = head->next;
        i++;
    }
    return head->value;
}

template <typename T>
int Stack<T>::GetCount() { return count; }