#include <iostream>
#include "AVLTree.h"

template <typename T>
T MAX(T a, T b)
{
    return (a > b) ? a : b;
}

template <typename T>
AVLTree<T>::AVLTree()
{
    this->root = NULL;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    FreeMemory(this->root);
}

template <typename T>
void AVLTree<T>::FreeMemory(NodeTree<T> *node)
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
NodeTree<T> *AVLTree<T>::FindNode(T value)
{
    NodeTree<T> *current = this->root; // поиск начинается с корня дерева
    while (current)                    // пока узел существует
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
NodeTree<T> *AVLTree<T>::GetRoot()
{
    return this->root;
}

template <typename T>
int AVLTree<T>::GetHeight(NodeTree<T> *root) const
{
    if (root == NULL)
        return 0;
    return root->height;
}

template <typename T>
int AVLTree<T>::GetBalance(NodeTree<T> *root) const
{
    if (root == NULL)
        return 0;
    return this->GetHeight(root->left) - this->GetHeight(root->right);
}

template <class T>
NodeTree<T> *AVLTree<T>::leftRotate(NodeTree<T> *x)
{
    NodeTree<T> *y = x->right;
    NodeTree<T> *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = MAX(this->GetHeight(x->left),
                    this->GetHeight(x->right)) +
                1;
    y->height = MAX(this->GetHeight(y->left),
                    this->GetHeight(y->right)) +
                1;

    return y;
}

template <class T>
NodeTree<T> *AVLTree<T>::rightRotate(NodeTree<T> *y)
{
    NodeTree<T> *x = y->left;
    NodeTree<T> *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = MAX(this->GetHeight(y->left),
                    this->GetHeight(y->right)) +
                1;
    x->height = MAX(this->GetHeight(x->left),
                    this->GetHeight(x->right)) +
                1;

    return x;
}

template <typename T>
void AVLTree<T>::TreePrintRec(NodeTree<T> *root)
{
    if (root == NULL)
        return;
    // рекурсивный вывод дерева (думаю ,что объяснять не стоит)
    TreePrintRec(root->left);
    std::cout << root->value << " ";
    TreePrintRec(root->right);
}

template <typename T>
void AVLTree<T>::TreePrint()
{
    this->TreePrintRec(this->root);
    std::cout << std::endl;
}

template <typename T>
NodeTree<T> *AVLTree<T>::InsertRec(NodeTree<T> *node, T value)
{
    if (node == NULL)
        node = new NodeTree<T>(value, NULL, NULL, NULL);

    if (value < node->value)
        node->left = this->InsertRec(node->left, value);
    else if (value > node->value)
        node->right = this->InsertRec(node->right, value);
    else // Equal keys not allowed
        return node;

    node->height = 1 + MAX(this->GetHeight(node->left),
                           this->GetHeight(node->right));

    int balance = this->GetBalance(node);

    if (balance > 1 && value < node->left->value)
        return this->rightRotate(node);

    if (balance < -1 && value > node->right->value)
        return this->leftRotate(node);

    if (balance > 1 && value > node->left->value)
    {
        node->left = this->leftRotate(node->left);
        return this->rightRotate(node);
    }

    if (balance < -1 && value < node->right->value)
    {
        node->right = this->rightRotate(node->right);
        return this->leftRotate(node);
    }

    return node;
}

template <typename T>
NodeTree<T> *AVLTree<T>::minValueNode(NodeTree<T> *node) const
{
    NodeTree<T> *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

template <typename T>
NodeTree<T> *AVLTree<T>::DeleteRec(NodeTree<T> *root, T value)
{
    if (root == NULL)
        return root;
    if (value < root->value)
        root->left = this->DeleteRec(root->left, value);
    else if (value > root->value)
        root->right = this->DeleteRec(root->right, value);
    else
    {
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            NodeTree<T> *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            NodeTree<T> *temp = this->minValueNode(root->right);
            root->value = temp->value;
            root->right = this->DeleteRec(root->right,
                                          temp->value);
        }
    }

    if (root == NULL)
        return root;
    root->height = 1 + MAX(this->GetHeight(root->left),
                           this->GetHeight(root->right));
    int balance = this->GetBalance(root);

    if (balance > 1 &&
        this->GetBalance(root->left) >= 0)
        return this->rightRotate(root);

    if (balance > 1 &&
        this->GetBalance(root->left) < 0)
    {
        root->left = this->leftRotate(root->left);
        return this->rightRotate(root);
    }

    if (balance < -1 &&
        this->GetBalance(root->right) <= 0)
        return this->leftRotate(root);

    if (balance < -1 &&
        this->GetBalance(root->right) > 0)
    {
        root->right = this->rightRotate(root->right);
        return this->leftRotate(root);
    }

    return root;
}

template <typename T>
bool AVLTree<T>::Delete(T value)
{
    if (this->DeleteRec(this->root, value))
        return true;
    return false;
}

template <typename T>
bool AVLTree<T>::Insert(T value)
{
    NodeTree<T> *node = this->InsertRec(this->root, value);
    if (node)
    {
        this->root = node;
        return true;
    }
    else
    {
        return false;
    }
}