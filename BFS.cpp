#include <iostream>
#include <map>
#include <list>

// Обход графа в ширину
void BFS(char v, std::map<char, bool> &Visited, std::list<char> &BypassOrder, std::map<char, std::list<char>> &Graph)
{
    if (Visited[v]) // проверка на то, была ли вершина уже в обходе
        return;
    Visited[v] = true;        // помечаем вершину, как пройденную
    BypassOrder.push_back(v); // запоминаем порядок прохождения
    for (auto _v : Graph[v])  // проходимся по всем соседям данной вершины
        if (!Visited[_v])
            BFS(_v, Visited, BypassOrder, Graph);
}

int main()
{
    std::map<char, std::list<char>> Graph; // граф
    std::map<char, bool> Visited;          // посещенные вершины
    std::list<char> BypassOrder;           // порядок обхода графа
    Graph['A'] = {'B', 'C', 'D'};
    Graph['B'] = {'A', 'C'};
    Graph['C'] = {'A', 'B', 'E'};
    Graph['D'] = {'A'};
    Graph['E'] = {'C'};
    // обозначем, что вершины еще не пройдены
    for (auto v : Graph)
        Visited[v.first] = false;
    // запускаем алгоритм в обхода ширину
    BFS('A', Visited, BypassOrder, Graph);
    std::cout << "Порядок обхода графа в ширину:" << std::endl;
    for (auto v : BypassOrder)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}
