#pragma once
#include "IGraph.h"
#include "ArcGraph.h"
#include <cassert>

ArcGraph::ArcGraph(int size)
	: verticescount(size)
{
}

ArcGraph::ArcGraph(const IGraph& graph)
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

ArcGraph::~ArcGraph()
{
}

void ArcGraph::AddEdge(int from, int to) 
{
	assert(0 <= from && from < verticescount);
	assert(0 <= to && to < verticescount);
	adjacencyLists.push_back({ from,to });
}

int ArcGraph::VerticesCount() const 
{
	return verticescount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const 
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

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const 
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

