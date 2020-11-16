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
    tree->TreePrint();
    tree->Delete(24);
    tree->TreePrint();

    cout << "Check copy constructor" << endl;
    Tree<int> *newTree = new Tree<int>(*tree);
    newTree->Delete(7);
    cout << "New Tree: " << endl;
    newTree->TreePrint();

    cout << "Old Tree: " << endl;
    tree->TreePrint();

    int *array = new int[10]{8, 7, 1, 3, 6, 12, 6, 5, 9, 10};
    Tree<int> *arrayTree = new Tree<int>(array, 10);
    cout << "Tree by array:" << endl;
    arrayTree->TreePrint();

    delete tree;
    delete arrayTree;
    delete newTree;
    delete[] array;
}