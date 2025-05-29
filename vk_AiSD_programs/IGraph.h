#pragma once
#include <vector>
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
