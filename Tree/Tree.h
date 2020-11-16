#pragma once
#ifndef TREE_H
#define TREE_H
#include "NodeTree.h"

template <typename T>
class Tree
{
private:
    NodeTree<T> *root;                // корень дерева
    void TreePrintRec(NodeTree<T> *); // рекурсивная печать дерева(основная функция вывода)
    void FreeMemory(NodeTree<T> *);   // очистка памяти для отдельного узла
    void CopyTree(NodeTree<T> *);     // рекурсивный метод копирования

public:
    Tree();                     // конструктор пустого дерева
    Tree(T *, int);             // конструктор создания дерева по массиву
    Tree(const Tree &);         // конструктор копирования
    ~Tree();                    // дестурктор дерева
    NodeTree<T> *GetRoot();     // получить корень дерева
    void Insert(T);             // добавление нового элемента
    void Delete(NodeTree<T> *); // удаление элемента по ссылке на узел
    void Delete(T);             // удаление элемента по значению (первый найденный)
    void TreePrint();           // печать дерева
    NodeTree<T> *FindNode(T);   // поиск узла по значению
};

#endif