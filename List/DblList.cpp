#include <iostream>
#include "DblList.h"
using namespace std;

template <typename T>
List<T>::List()
{
    this->head = NULL;
    this->tail = NULL;
}

template <typename T>
List<T>::~List()
{
    this->Clear();
}

template <typename T>
List<T>::List(const List &list)
{
    Node *node = list.head;
    while (node != NULL){
        this->Add(node->value);
        node = node->next;
    }
}

template <typename T>
void List<T>::Add(T value)
{
    Node *node = new Node(value, NULL, this->tail);
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
        if (index == 0)
        {
            Node *temp_node = this->head;
            if (this->head->next != NULL)
                this->head->next->prev = NULL;
            this->head = this->head->next;
            delete temp_node;
        }
        else
        {
            int counter = 0;
            Node *node = this->head;
            while (counter++ != index)
                node = node->next;
            node->prev->next = node->next;
            if (node->next != NULL)
                node->next->prev = node->prev;
            delete node;
        }
    }
}

template <typename T>
void List<T>::Clear()
{
    if (this->head != NULL)
    {
        Node *node = this->head;
        while (node->next != NULL)
        {
            node = node->next;
            if (node->prev != NULL)
                delete node->prev;
        }
        delete node;
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
    if (this->Count == 0)
    {
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