/*
Задание 1. Сделать все виды графов
число вершин всегда знаем (задается в конструкторе)
нужно учитывать кратные ребра и петли
0 1 5 2 3 6 4
0 1 2 3 4 6 5
0 1 5 3 6 4 2

*/
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>
#include <unordered_map>
#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex : graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph& graph, const std::function<void(int)>& func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex : graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph& graph, const std::function<void(int)>& func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, func);
        }
    }
}

void topologicalSortInternal(const IGraph& graph, int vertex, std::vector<bool>& visited, std::deque<int>& sorted)
{
    visited[vertex] = true;

    for (int nextVertex : graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            topologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph& graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            topologicalSortInternal(graph, i, visited, sorted);
        }
    }

    return sorted;
}
int main(int argc, const char* argv[]) {
    ListGraph listGraph(7);
    listGraph.AddMultiAdge(0,1,5);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);
    std::cout << "first graph(ListGraph):" << std::endl;
    std::cout << "count of vertex:" << listGraph.VerticesCount() << std::endl;
    std::cout << "BFS:" << std::endl;
    mainBFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS:" << std::endl;
    mainDFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "TopologicalSort:" << std::endl;
    for (int vertex : topologicalSort(listGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    SetGraph setGraph(listGraph);
    MatrixGraph matrixGraph(setGraph);
    ArcGraph arcGraph(matrixGraph);
    std::cout << "second graph(arcGraph):" << std::endl;
    std::cout << "count of vertex:" << arcGraph.VerticesCount() << std::endl;
    std::cout << "BFS:" << std::endl;
    mainBFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS:" << std::endl;
    mainDFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "TopologicalSort:" << std::endl;
    for (int vertex : topologicalSort(arcGraph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    return 0;
}
