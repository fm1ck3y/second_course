#include <iostream>
#include "Tree.h"

template <typename T>
Tree<T>::Tree()
{
    this->root = NULL;
}

template <typename T>
void Tree<T>::Insert(T value, NodeTree *root)
{
    root = new NodeTree(value, NULL, NULL);
    if (this->root == NULL)
    {
        this->root = root;
        return;
    }

    NodeTree *parent = NULL;
    NodeTree *current = this->root;
    while (current)
    {
        parent = current;
        if (root->value > current->value)
            current = current->right;
        else
            current = current->left;
    }
    if (root->value < parent->value)
        parent->left = root;
    else
        parent->right = root;
}

template <typename T>
void Tree<T>::TreePrintRec(NodeTree *root)
{
    if (root == NULL)
        return;
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