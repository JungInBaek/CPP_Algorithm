#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;


struct Vertex
{

};

vector<Vertex> vertices;
vector<vector<int>> adjacent;
vector<bool> visited;

queue<int> q;
vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);

	adjacent.resize(6, vector<int>());
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);

	visited.resize(6);
	
	discovered.resize(6);
}

void Dfs(int here)
{
	visited[here] = true;
	cout << "visited: " << here << endl;

	for (int there : adjacent[here])
	{
		if (visited[there] == false)
		{
			Dfs(there);
		}

	}
}

void DfsAll()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (visited[i] == false)
		{
			Dfs(i);
		}
	}
}



void RecursiveBfs()
{
	if (q.empty())
	{
		return;
	}
	int here = q.front();
	q.pop();

	cout << "discovered: " << here << endl;

	for (int there : adjacent[here])
	{
		if (discovered[there] == false)
		{
			q.push(there);
			discovered[there] = true;
		}
	}
	RecursiveBfs();
}

void RecursiveBfsAll()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (discovered[i] == false)
		{
			q.push(i);
			discovered[i] = true;
			RecursiveBfs();
		}
	}
}

void Bfs(int start)
{
	q.push(start);
	discovered[start] = true;

	while (q.empty() == false)
	{
		int here = q.front();
		q.pop();

		cout << "discovered: " << here << endl;

		for (int there : adjacent[here])
		{
			if (discovered[there] == true)
			{
				continue;
			}

			q.push(there);
			discovered[there] = true;
		}
	}
}

void BfsAll()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (discovered[i] == false)
		{
			Bfs(i);
		}
	}
}

int main()
{
	CreateGraph();

	DfsAll();
	
	BfsAll();
}