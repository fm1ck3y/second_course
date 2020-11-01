#include <iostream>
#include "List.h"
using namespace std;

template <typename T>
List<T>::List()
{
    this->head = NULL;
}

template <typename T>
List<T>::~List()
{
    this->Clear();
}

template <typename T>
void List<T>::Add(T value)
{
    Node *node = new Node(value, NULL);
    if (this->head == NULL)
        this->head = node;
    else
        this->tail->next = node;
    this->tail = node;
    this->Count++;
}

template <typename T>
void List<T>::Delete(int index)
{
    if (index >= this->Count)
    {
        std::cerr << "Index out of the range." << std::endl;
        exit(0);
    }
    else
    {
        Node *temp_node;
        if (index == 0)
        {
            temp_node = this->head;
            this->head = this->head->next;
        }
        else
        {
            int counter = 0;
            Node *node = this->head;
            while (counter++ != index - 1)
                node = node->next;
            temp_node = node->next;
            node->next = node->next->next;
            this->Count--;
        }
        delete temp_node;
    }
}

template <typename T>
void List<T>::Clear()
{
    if (this->head != NULL)
    {
        Node *node = this->head;
        Node *next;
        while (node != NULL)
        {
            next = node->next;
            delete node;
            node = next;
        }
        this->head = NULL;
    }
    Count = 0;
}

template <typename T>
T &List<T>::operator[](const int index)
{
    if (index >= this->Count)
    {
        std::cerr << "Index out of the range." << std::endl;
        exit(0);
    }
    else
    {
        if (index == Count - 1)
            return this->tail->value;
        int counter = 0;
        Node *node = this->head;
        while (counter++ != index)
            node = node->next;
        return node->value;
    }
}

template <typename T>
void List<T>::Print()
{
    if (this->Count == 0) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node *node = this->head;
    while (node != NULL)
    {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
int List<T>::GetCount() { return this->Count; }