﻿#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
#include "BinarySearchTree.h"

using namespace std;


struct Vertex {};
vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraph()
{
	vertices.resize(6);
	
	adjacent.resize(6, vector<int>(6, -1));
	adjacent[0][1] = adjacent[1][0] = 15;
	adjacent[0][3] = adjacent[3][0] = 35;
	adjacent[1][2] = adjacent[2][1] = 5;
	adjacent[1][3] = adjacent[3][1] = 10;
	adjacent[3][4] = adjacent[4][3] = 5;
	adjacent[3][5] = adjacent[5][3] = 10;
	adjacent[4][5] = adjacent[5][4] = 5;
}

class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; ++i)
		{
			_parent[i] = i;
		}
	}

	int Find(int u)
	{
		if (_parent[u] == u)
		{
			return u;
		}

		return _parent[u] = Find(_parent[u]);
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
		{
			return;
		}

		if (_rank[u] > _rank[v])
		{
			::swap(u, v);
		}

		if (_rank[u] == _rank[v])
		{
			++_rank[v];
		}

		_parent[u] = v;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

struct CostEdge
{
	int cost;
	int u;
	int v;

	bool operator<(const CostEdge& other) const
	{
		return cost < other.cost;
	}

	bool operator>(const CostEdge& other) const
	{
		return cost > other.cost;
	}
};

int Kruskal(vector<CostEdge>& selected)
{
	//vector<CostEdge> edges;
	priority_queue<CostEdge, vector<CostEdge>, greater<CostEdge>> edges;
	for (int u = 0; u < adjacent.size(); ++u)
	{
		for (int v = 0; v < adjacent[u].size(); ++v)
		{
			if (u > v)
			{
				continue;
			}

			int cost = adjacent[u][v];
			if (cost == -1)
			{
				continue;
			}

			edges.push({ cost, u, v });
		}
	}

	//::sort(edges.begin(), edges.end());

	DisjointSet sets(vertices.size());

	int ret = 0;
	/*for (CostEdge& edge : edges)
	{
		if (sets.Find(edge.u) == sets.Find(edge.v))
		{
			continue;
		}

		selected.push_back(edge);
		sets.Merge(edge.u, edge.v);
		ret += edge.cost;
	}*/

	while (edges.empty() == false)
	{
		CostEdge edge = edges.top();
		edges.pop();
		if (sets.Find(edge.u) == sets.Find(edge.v))
		{
			continue;
		}

		selected.push_back(edge);
		sets.Merge(edge.u, edge.v);
		ret += edge.cost;
	}

	return ret;
}

int main()
{
	CreateGraph();
	vector<CostEdge> selected;
	int cost = Kruskal(selected);
}