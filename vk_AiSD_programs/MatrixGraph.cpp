#pragma once
#include "IGraph.h"
#include "MatrixGraph.h"
#include <cassert>
MatrixGraph::MatrixGraph(int size)
	: adjacencyLists(size, std::vector<int>(size, 0))
{
}
MatrixGraph::MatrixGraph(const IGraph& graph)
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
MatrixGraph::~MatrixGraph()
{
}

void MatrixGraph::AddEdge(int from, int to) 
{
	assert(0 <= from && from < adjacencyLists.size());
	assert(0 <= to && to < adjacencyLists.size());
	adjacencyLists[from][to] += 1;
}

int MatrixGraph::VerticesCount() const 
{
	return (int)adjacencyLists.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const 
{
	assert(0 <= vertex && vertex < adjacencyLists.size());
	std::vector<int> nextVertices;
	for (int j = 0; j < adjacencyLists.size(); j++)
	{
		nextVertices.insert(nextVertices.end(), adjacencyLists[vertex][j], j);
	}

	return nextVertices;
}

    std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const 
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;
        for (int i = 0; i < adjacencyLists.size(); i++)
        {
            prevVertices.insert(prevVertices.end(), adjacencyLists[i][vertex], i);
        }

        return prevVertices;
    }
