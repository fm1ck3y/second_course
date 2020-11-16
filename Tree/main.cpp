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
}