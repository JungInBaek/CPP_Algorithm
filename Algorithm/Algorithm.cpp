#include <iostream>
#include <vector>

using namespace std;


int N;
vector<int> _path;
vector<vector<int>> board;
vector<vector<int>> cache;

int path(int y, int x)
{
	if (y >= N)
	{
		return 0;
	}

	int& ret = cache[y][x];
	if (ret != 0)
	{
		return ret;
	}

	if (y + 1 >= N)
	{
		return ret += board[y][x];
	}

	int path1 = path(y + 1, x);
	_path[y + 1] = x;
	ret = path1;

	if (x + 1 >= board[y + 1].size())
	{
		return ret += board[y][x];
	}

	int path2 = path(y + 1, x + 1);
	if (path2 > path1)
	{
		_path[y + 1] = x + 1;
		ret = path2;
	}

	return ret += board[y][x];
}


int main()
{
	board = vector<vector<int>>
	{
		{ 6 },
		{ 1, 2 },
		{ 3, 7, 4 },
		{ 9, 4, 1, 7 },
		{ 2, 7, 5, 9, 4 },
	};

	N = board.size();
	_path.resize(N);
	cache.resize(N, vector<int>(N));

	_path[0] = 0;
	int ret = path(0, 0);
	cout << ret << endl;
}