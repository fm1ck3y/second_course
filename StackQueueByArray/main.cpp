#include <iostream>
#include "Stack.cpp"
using namespace std;

int main()
{
    Stack<int> stack;
    stack.Push(5);
    stack.Push(7);
    stack.Push(3);
    cout << "Top in Stack = " << stack.Peek() << endl;
    stack.Pop();
    stack.Push(4);
    cout << "Top in Stack = " << stack.Peek() << endl;
    stack.Pop();
    cout << "Top in Stack = " << stack.Peek() << endl;
    cout << "Count elements in Stack = " << stack.GetCount() << endl;
    stack.Clear();
}