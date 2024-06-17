#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
#include "BinarySearchTree.h"

using namespace std;


class NavieDisJointSet
{

public:
	NavieDisJointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int Find(int n)
	{
		if (_parent[n] == n)
		{
			return n;
		}

		return Find(_parent[n]);
	}

	void Merge(int u, int v)
	{
		if (Find(u) == Find(v))
		{
			return;
		}

		_parent[u] = v;
	}

private:
	vector<int> _parent;
};

class DisJointSet
{

public:
	DisJointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int Find(int n)
	{
		if (_parent[n] == n)
		{
			return n;
		}

		return _parent[n] = Find(_parent[n]);
	}

	void Merge(int u, int v)
	{
		if (Find(u) == Find(v))
		{
			return;
		}

		if (_rank[u] > _rank[v])
		{
			::swap(u, v);
		}
		
		if (_rank[u] == _rank[v])
		{
			++_rank[u];
		}

		_parent[u] = v;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};


int main()
{
	DisJointSet teams(1000);

	teams.Merge(10, 1);
	int teamId1 = teams.Find(1);
	int teamId2 = teams.Find(10);

	teams.Merge(3, 2);
	int teamId3 = teams.Find(2);
	int teamId4 = teams.Find(3);

	teams.Merge(1, 3);
	int teamId5 = teams.Find(1);
	int teamId6 = teams.Find(3);
}