#include <iostream>
#include "Tree.cpp"
using namespace std;

int main()
{
    Tree<int> *tree = new Tree<int>();
    tree->Insert(5);
    tree->Insert(6);
    tree->Insert(7);
    tree->Insert(8);
    tree->Insert(24);
    tree->Insert(1);
    cout << "************************************" << endl;
    cout << "Вставили элементы" << endl;
    tree->TreePrint();
    tree->Delete(24);
    cout << "************************************" << endl;
    cout << "Удалили узел со значением 24" << endl;
    tree->TreePrint();
    cout << "************************************" << endl;
    cout << "Находим узел по значению 1:" << endl;
    NodeTree<int> *node = tree->FindNode(1);
    if (node != NULL)
        cout << "Узел со значением <" << node->value << "> находится по адресу " << node << endl;
    else
        cout << "Узел не найден." << endl;
    cout << "************************************" << endl;
    cout << "Проверяем конструктор копирования" << endl;
    delete tree;
}
