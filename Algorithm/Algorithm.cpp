#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <chrono>
#include "Windows.h"

using namespace std;
using namespace chrono;
using uint64 = unsigned __int64;


class DisjointSet
{
public:
	DisjointSet(int n, vector<int> edgeCount)
		: _parent(n), _rank(edgeCount)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int find(int u)
	{
		if (_parent[u] == u)
		{
			return u;
		}

		return _parent[u] = find(_parent[u]);
	}

	void merge(int u, int v)
	{
		u = find(u);
		v = find(v);

		if (u == v)
		{
			return;
		}

		if (_rank[u] > _rank[v])
		{
			swap(u, v);
		}

		_parent[u] = v;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};


vector<vector<int>> adjacent;
vector<bool> visited;
vector<vector<int>> cache;		// 0 = vertex, 1 = edge

// BFS + DP + DisjointSet
queue<int> q;

void bfs(int now)
{
	int& vertex = cache[now][0];
	int& edge = cache[now][1];

	if (vertex != -1 && edge != -1)
	{
		return;
	}

	vertex = 0;
	edge = 0;

	visited[now] = true;
	vertex += 1;

	for (int& next : adjacent[now])
	{
		edge += 1;

		if (visited[next] == true)
		{
			continue;
		}

		q.push(next);
	}

	while (q.empty() == false)
	{
		int next = q.front();
		q.pop();

		bfs(next);

		vertex += cache[next][0];
		edge += cache[next][1];
	}
}

vector<int> solution(vector<vector<int>> edges)
{
	vector<int> answer;
	answer.resize(4);

	int length = 0;
	for (vector<int>& edge : edges)
	{
		length = max(length, edge[0]);
		length = max(length, edge[1]);
	}
	length += 1;

	vector<int> outEdge(length, 0);
	vector<int> inEdge(length, 0);
	adjacent.resize(length);
	for (vector<int>& edge : edges)
	{
		adjacent[edge[0]].push_back(edge[1]);
		outEdge[edge[0]] += 1;
		inEdge[edge[1]] += 1;
	}

	int root = 0;
	for (int i = 1; i < length; i++)
	{
		if (outEdge[i] > outEdge[root] && inEdge[i] == 0)
		{
			root = i;
			answer[0] = root;
			continue;
		}
	}

	DisjointSet sets(length, outEdge);
	for (vector<int>& edge : edges)
	{
		if (edge[0] == root)
		{
			continue;
		}

		if (sets.find(edge[0]) == sets.find(edge[1]))
		{
			continue;
		}

		sets.merge(edge[0], edge[1]);
	}

	visited.resize(length, false);
	cache.resize(length, vector<int>(2, -1));
	
	for (int& next : adjacent[root])
	{
		if (outEdge[sets.find(next)] == 2 && inEdge[sets.find(next)] >= 2)
		{
			answer[3] += 1;
			continue;
		}

		int& vertex = cache[next][0];
		int& edge = cache[next][1];
	
		if (vertex == -1 || edge == -1)
		{
			bfs(next);
		}
		
		if (vertex == edge + 1)
		{
			answer[2] += 1;
		}
		else if (vertex == edge)
		{
			answer[1] += 1;
		}
	}

	return answer;
}

int main()
{
	//vector<vector<int>> edges = { {2, 3}, {4, 3}, {1, 1}, {2, 1} };		// [2, 1, 1, 0]
	vector<vector<int>> edges = { {4, 11}, {1, 12}, {8, 3}, {12, 7}, {4, 2}, {7, 11}, {4, 8}, {9, 6}, {10, 11}, {6, 10}, {3, 5}, {11, 1}, {5, 3}, {11, 9}, {3, 8} };		// [4, 0, 1, 2]

	system_clock::time_point start = system_clock::now();
	vector<int> answer = solution(edges);
	system_clock::time_point end = system_clock::now();

	cout << (end - start).count() << endl;

	for (int& i : answer)
	{
		cout << i;
	}
	cout << endl;
}