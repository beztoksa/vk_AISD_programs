#pragma once
#include "IGraph.h"
#include "SetGraph.h"
#include <vector>
#include <unordered_map>
#include <cassert>
SetGraph::SetGraph(int size)
	: adjacencyLists(size)
{
}

SetGraph::SetGraph(const IGraph& graph)
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

SetGraph::~SetGraph()
{
}

void SetGraph::AddEdge(int from, int to) 
{
	assert(0 <= from && from < adjacencyLists.size());
	assert(0 <= to && to < adjacencyLists.size());
	adjacencyLists[from][to] += 1;
}

int SetGraph::VerticesCount() const 
{
	return (int)adjacencyLists.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const 
{
	assert(0 <= vertex && vertex < adjacencyLists.size());
	std::vector<int> nextVertices;
	for (const auto& [key, value] : adjacencyLists[vertex])
	{
		nextVertices.insert(nextVertices.end(), value, key);
	}

	return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const 
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

