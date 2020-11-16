#include <iostream>
#include "Tree.h"

template <typename T>
Tree<T>::Tree()
{
    this->root = NULL;
}

template <typename T>
Tree<T>::~Tree()
{
    FreeMemory(this->root);
}

template <typename T>
Tree<T>::Tree(T *array, int length)
{
    this->root = NULL;
    for (int i = 0; i < length; i++)
        this->Insert(array[i]); // добавляем каждый элемент массива в дерево
}

template <typename T>
Tree<T>::Tree(const Tree &tree)
{
    this->root = NULL;
    this->CopyTree(tree.root); // заполняем дерево рекурсивно
}

template <typename T>
void Tree<T>::CopyTree(NodeTree<T> *node)
{
    if (node == NULL) // проверяем, существует ли узел
        return;
    // если существует, то
    this->Insert(node->value);   // вставляем значение узла в дерево
    this->CopyTree(node->left);  // рекурсивно добавляем левый узел
    this->CopyTree(node->right); // рекурсивно добавляем правый узел
}

template <typename T>
void Tree<T>::Insert(T value)
{
    NodeTree<T> *node = new NodeTree<T>(value, NULL, NULL, NULL); // создаем новый узел
    if (this->root == NULL) // если корень дерева не существует, то добавляем его
    {
        this->root = node;
        return;
    }

    NodeTree<T> *parent = NULL; // родитель искаемого узла
    NodeTree<T> *current = this->root; // сам узел
    // данный цикл находит узел, куда мы должны добавить новый узел
    while (current)
    {
        parent = current; 
        if (node->value > current->value)
            current = current->right;
        else
            current = current->left;
    }
    node->parent = parent; // присваеваем новому узлу родительский узел
    // если значение нового узла меньше родительского, то добавляем его в левый узел
    // иначе соответственно в правый 
    if (node->value < parent->value) 
        parent->left = node;
    else
        parent->right = node;
}

template <typename T>
void Tree<T>::TreePrintRec(NodeTree<T> *root)
{
    if (root == NULL)
        return;
    // рекурсивный вывод дерева (думаю ,что объяснять не стоит)
    TreePrintRec(root->left); 
    std::cout << root->value << " ";
    TreePrintRec(root->right);
}

template <typename T>
void Tree<T>::TreePrint()
{
    this->TreePrintRec(this->root);
    std::cout << std::endl;
}

template <typename T>
void Tree<T>::FreeMemory(NodeTree<T> *node)
{
    // рекурсивная очистка памяти
    if (node == NULL) 
        return;
    FreeMemory(node->left);
    FreeMemory(node->right);
    if (node->parent != NULL) // если родитель не существует (данный узел не является корнем)
    {
        // дальше находим , "кто" узел по отношению к родителю (левый или правый узел)
        // обозначаем, что узел больше не существует
        if (node == node->parent->left)
            node->parent->left = NULL;
        if (node == node->parent->right)
            node->parent->right = NULL;
    }
    delete node; // удаляем узел из памяти
}

template <typename T>
NodeTree<T> *Tree<T>::FindNode(T value)
{
    NodeTree<T> *current = this->root; // поиск начинается с корня дерева
    while (current) // пока узел существует
    {
        if (value == current->value) // если значения равны, значит поискомый узел найден
            return current;
        // так, как дерево уже упорядоченное, то поиск будет длиться в худшем случае O(n/2)
        // ну в общем то говоря бинарный поиск
        if (value > current->value) 
            current = current->right;
        else
            current = current->left;
    }
    return NULL; // на случай , если узел не будет найден
}

template <typename T>
void Tree<T>::Delete(NodeTree<T> *node)
{
    FreeMemory(node);
}

template <typename T>
void Tree<T>::Delete(T value)
{
    FreeMemory(this->FindNode(value));
}

template <typename T>
NodeTree<T> *Tree<T>::GetRoot()
{
    return this->root;
}