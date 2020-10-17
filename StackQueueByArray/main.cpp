#include <iostream>
#include "Stack.cpp"
#include "Queue.cpp"
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
    cout << "-----------------------" << endl;
    Queue<int> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Print();
    cout << " Dequeue : " << queue.Dequeue() << endl;
    cout << " Dequeue : " << queue.Dequeue() << endl;
    cout << " Dequeue : " << queue.Dequeue() << endl;
    queue.Print();
    queue.Enqueue(5);
    queue.Enqueue(7);
    queue.Print();
    cout << "Peek is : " << queue.Peek() << endl;
}