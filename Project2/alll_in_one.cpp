/*
«адание 1. —делать все виды графов
число вершин всегда знаем (задаетс€ в конструкторе)
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

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;
    void AddEdgeTwice(int from, int to)
    {
        AddEdge(from, to);
        AddEdge(to, from);
    }
    void AddMultiAdge(int from, int to, int n)
    {
        for (int i = 0; i < n; i++)
        {
            AddEdge(from, to);
        }
    }
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph : public IGraph
{
public:
    ListGraph(int size)
        : adjacencyLists(size)
    {
    }

    ListGraph(const IGraph& graph)
    {
        adjacencyLists.resize(graph.VerticesCount());
        for (int i = 0; i < graph.VerticesCount(); ++i)
        {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }

    ~ListGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }

    int VerticesCount() const override
    {
        return (int)adjacencyLists.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); ++from)
        {
            for (int to : adjacencyLists[from])
            {
                if (to == vertex)
                    prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<int>> adjacencyLists;
};
struct MatrixGraph : public IGraph
{
public:
    MatrixGraph(int size)
        : adjacencyLists(size, std::vector<int>(size, 0))
    {
    }

    MatrixGraph(const IGraph& graph)
    {
        int size = graph.VerticesCount();
        adjacencyLists.assign(size, std::vector<int>(size, 0));
        for (int i = 0; i < graph.VerticesCount(); ++i)
        {
            for (int j : graph.GetNextVertices(i))
            {
                adjacencyLists[i][j] += 1;
            }
        }
    }

    ~MatrixGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from][to] += 1;
    }

    int VerticesCount() const override
    {
        return (int)adjacencyLists.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> nextVertices;
        for (int j = 0; j < adjacencyLists.size(); j++)
        {
            nextVertices.insert(nextVertices.end(), adjacencyLists[vertex][j], j);
        }

        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        for (int i = 0; i < adjacencyLists.size(); i++)
        {
            prevVertices.insert(prevVertices.end(), adjacencyLists[i][vertex], i);
        }

        return prevVertices;
    }

private:
    std::vector<std::vector<int>> adjacencyLists;
};

struct SetGraph : public IGraph
{
public:
    SetGraph(int size)
        : adjacencyLists(size)
    {
    }

    SetGraph(const IGraph& graph)
    {
        adjacencyLists.resize(graph.VerticesCount());
        for (int i = 0; i < graph.VerticesCount(); ++i)
        {
            for (int j : graph.GetNextVertices(i))
            {
                adjacencyLists[i][j] += 1;
            }
        }
    }

    ~SetGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from][to] += 1;
    }

    int VerticesCount() const override
    {
        return (int)adjacencyLists.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> nextVertices;
        for (const auto& [key, value] : adjacencyLists[vertex])
        {
            nextVertices.insert(nextVertices.end(), value, key);
        }

        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        for (int i = 0; i < adjacencyLists.size(); i++)
        {
            int count = adjacencyLists[i].contains(vertex) ? adjacencyLists[i].at(vertex) : 0;
            prevVertices.insert(prevVertices.end(), count, vertex);
        }

        return prevVertices;
    }

private:
    std::vector<std::unordered_map<int, int>> adjacencyLists;
};
struct ArcGraph : public IGraph
{
public:
    ArcGraph(int size)
        : verticescount(size)
    {
    }

    ArcGraph(const IGraph& graph)
    {
        verticescount = graph.VerticesCount();
        for (int i = 0; i < graph.VerticesCount(); i++)
        {
            for (int to : graph.GetNextVertices(i))
            {
                adjacencyLists.push_back({ i,to });
            }

        }
    }

    ~ArcGraph()
    {
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from < verticescount);
        assert(0 <= to && to < verticescount);
        adjacencyLists.push_back({ from,to });
    }

    int VerticesCount() const override
    {
        return verticescount;
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < verticescount);
        std::vector<int> nextVertices;
        for (const auto& [from, to] : adjacencyLists)
        {
            if (from == vertex)
            {
                nextVertices.push_back(to);
            }
        }
        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex < verticescount);
        std::vector<int> prevVertices;
        for (const auto& [from, to] : adjacencyLists)
        {
            if (to == vertex)
            {
                prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::pair<int, int>> adjacencyLists;
    int verticescount;
};

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
    listGraph.AddMultiAdge(0, 1, 5);
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
