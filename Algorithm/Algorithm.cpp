#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;


struct Vertex
{

};

struct VertexCost
{
	int vertex;
	int cost;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<int> parent;
vector<int> best;
list<VertexCost> discovered;


void CreateGraph()
{
	int size = 6;
	vertices.resize(size);
	adjacent =
	{
		{ -1, 15, -1, 35, -1, -1 },
		{ 15, -1, 5, 10, -1, -1 },
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, 5, -1 },
		{ -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, -1, 5, -1 },
	};
	parent.resize(size, -1);
	best.resize(size, INT32_MAX);
}

void Dijikstra(int here)
{
	for (int there = 0; there < 6; ++there)
	{
		if (adjacent[here][there] == -1)
		{
			continue;
		}

		int nextCost = best[here] + adjacent[here][there];
		if (nextCost >= best[there])
		{
			continue;
		}

		best[there] = nextCost;
		parent[there] = here;
		discovered.push_back(VertexCost{ there, nextCost });
	}

	if (discovered.empty())
	{
		return;
	}

	list<VertexCost>::iterator bestIt;
	int bestCost = INT32_MAX;
	for (auto it = discovered.begin(); it != discovered.end(); ++it)
	{
		if (it->cost >= bestCost)
		{
			continue;
		}

		bestCost = it->cost;
		bestIt = it;
	}

	int next = bestIt->vertex;
	discovered.erase(bestIt);
	Dijikstra(next);
}

int main()
{
	CreateGraph();

	parent[0] = 0;
	best[0] = 0;
	Dijikstra(0);

	cout << "end" << endl;
}