#pragma once
#ifndef NODETREE_H
#define NODETREE_H

template <typename T>
class NodeTree
{
public:
    NodeTree(T value, NodeTree *l, NodeTree *r, NodeTree *p)
    {
        this->value = value;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    T value;          // значения узла
    NodeTree *left;   // левый узел
    NodeTree *right;  // правый узел
    NodeTree *parent; // родительский  узел
};

#endif