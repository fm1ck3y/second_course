#pragma once
#ifndef TREE_H
#define TREE_H
#include "NodeTree.h"

template <typename T>
class AVLTree
{
private:
    NodeTree<T> *root;                // корень дерева
    void TreePrintRec(NodeTree<T> *,NodeTree<T> *); // рекурсивная печать дерева(основная функция вывода)
    void FreeMemory(NodeTree<T> *);   // очистка памяти для отдельного узла
    void CopyTree(NodeTree<T> *);     // рекурсивный метод копирования

    NodeTree<T> *rightRotate(NodeTree<T> *);
    NodeTree<T> *leftRotate(NodeTree<T> *);
    int GetHeight(NodeTree<T> *) const;
    int GetBalance(NodeTree<T> *) const;
    void InsertAVLNode(NodeTree<T> *, NodeTree<T> *);
    NodeTree<T> *minValueNode(NodeTree<T> *) const;

    NodeTree<T> *InsertRec(NodeTree<T> *, T);
    NodeTree<T> *DeleteRec(NodeTree<T> *, T);

public:
    AVLTree();                // конструктор пустого дерева
    AVLTree(T *, int);        // конструктор создания дерева по массиву
    AVLTree(const AVLTree &); // конструктор копирования
    ~AVLTree();               // дестурктор дерева
    NodeTree<T> *GetRoot();   // получить корень дерева
    bool Insert(T);           // добавление нового элемента
    bool Delete(T);           // удаление элемента по ссылке на узел
    void TreePrint();         // печать дерева
    NodeTree<T> *FindNode(T); // поиск узла по значению
};

#endif