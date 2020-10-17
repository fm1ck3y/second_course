#include <iostream>
#include "Queue.h"

template <typename T>
Queue<T>::Queue()
{
    this->start = 0;
    this->end = 0;
}

template <typename T>
Queue<T>::~Queue()
{
    free(array);
}

template <typename T>
void Queue<T>::Enqueue(T value)
{
    if ((this->end == MAX_QUEUE - 1 && this->start == 0) || (this->start + 1 == this->end))
        std::cerr << "Queue is full" << std::endl;
    else
    {
        this->array[this->start++] = value;
        if (this->start == MAX_QUEUE)
            this->start = 0;
    }
}

template <typename T>
bool Queue<T>::IsEmpty()
{

    if (this->start == this->end)
        return true;
    return false;
}

template <typename T>
T Queue<T>::Dequeue()
{
    if (this->end == MAX_QUEUE)
        this->end = 0;
    if (!IsEmpty())
    {
        return this->array[end++];
    }
    else
    {
        std::cerr << "Queue is empty" << std::endl;
        throw;
    }
}

template <typename T>
void Queue<T>::Print()
{
    if(IsEmpty()){
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    std::cout << "Print Queue: " << std::endl;
    if (this->end >= MAX_QUEUE)
        this->end = 0;
    int _end = this->end;
    while (this->start != _end)
    {
        std::cout << this->array[_end++] << " ";
        if (_end >= MAX_QUEUE)
            _end = 0;
    }
    std::cout << std::endl;
}

template <typename T>
T Queue<T>::Peek()
{
    return this->array[end];
}

template <typename T>
Queue<T>::Queue(const Queue &queue)
{
    for (size_t i = 0; i < queue->array; i++)
        this->array[i] = queue->array[i];
    this->start = queue->start;
    this->end = queue->end;
}