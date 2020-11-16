#pragma once
#ifndef NODETREE_H
#define NODETREE_H

template <typename T>
class Tree
{
private:
    class NodeTree
    {
    public:
        NodeTree(T value, NodeTree *l, NodeTree *r)
        {
            this->value = value;
            this->left = l;
            this->right = r;
        }
        T value;         // значения узла
        NodeTree *left;  // левый узел
        NodeTree *right; // правый узел
    };
    NodeTree *root;                    // корень дерева
    void TreePrintRec(NodeTree *root); // рекурсивная печать дерева(основная функция вывода)

public:
    Tree();                                      // конструктор пустого дерева
    Tree(T *array, int length);                  // конструктор создания дерева по массиву
    Tree(const Tree &list);                      // конструктор копирования
    ~Tree();                                     // дестурктор дерева
    NodeTree *GetRoot();                         // получить корень дерева
    void Insert(T value, NodeTree *root = NULL); // добавление нового элемента
    void Delete(NodeTree *);                     // удаление элемента
    void FreeMemory(NodeTree *);                 // очистка памяти для отдельного узла
    void TreePrint();                            // печать дерева
    void Search(T value);                        // поиск значения в дереве
};

#endif