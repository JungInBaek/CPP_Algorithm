#pragma once


class DisjointSet
{
public:
	DisjointSet(int32 n) : _parent(n), _rank(n, 1)
	{
		for (int32 i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int Find(int32 u)
	{
		if (_parent[u] == u)
		{
			return u;
		}

		return _parent[u] = Find(_parent[u]);
	}

	void Merge(int32 u, int32 v)
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
	vector<int32> _parent;
	vector<int32> _rank;
};