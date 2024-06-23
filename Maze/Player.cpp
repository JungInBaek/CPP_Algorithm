#include "pch.h"
#include "Player.h"
#include "Board.h"

#include <stack>


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		_board->GenerateMap_Prim();
		Init(_board);
		return;
	}

	_sumTick += deltaTick;

	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
		_pos = _path[_pathIndex++];
	}
}

bool Player::CanGo(Pos pos)
{
	return _board->GetTileType(pos) == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos { 0, -1 },	// UP
		Pos { -1, 0 },	// LEFT
		Pos { 0, 1 },	// DOWN
		Pos { 1, 0 },	// RIGHT
	};

	while (pos != dest)
	{
		int32 right = (_dir + DIR_RIGHT) % DIR_COUNT;
		int32 left = (_dir + DIR_LEFT) % DIR_COUNT;
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		if (CanGo(pos + front[right]))
		{
			// 오른쪽 방향으로 90도 회전
			_dir = right;

			// 앞으로 한 보 전진
			pos += front[_dir];

			// 경로 저장
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];

			// 경로 저장
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전
			_dir = left;
		}
	}

	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}

	// 목적지 도착
	if (_path.empty() == false)
	{
		s.push(_path.back());
	}

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	std::reverse(path.begin(), path.end());

	_path = path;
}

void Player::Bfs()
{
	queue<Pos> q;
	map<Pos, bool> discovered;
	map<Pos, Pos> parent;

	Pos pos = _pos;
	Pos dest = _board->GetExitPos();

	Pos front[] =
	{
		Pos{ 0, -1 },
		Pos{ 1, 0 },
		Pos{ 0, 1 },
		Pos{ -1, 0 },
	};

	q.push(pos);
	discovered[pos] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest)
		{
			break;
		}

		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];

			if (CanGo(nextPos) == false)
			{
				continue;
			}

			if (discovered[nextPos])
			{
				continue;
			}

			q.push(nextPos);
			discovered[nextPos] = true;
			parent[nextPos] = pos;
		}
	}

	_path.clear();

	pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (parent[pos] == pos)
		{
			break;
		}
		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::AStar()
{
	Pos start = _pos;
	Pos dest = _board->GetExitPos();
	int size = _board->GetSize();

	Pos front[] =
	{
		Pos { 0, -1 },	// UP
		Pos { -1, 0 },	// LEFT
		Pos { 0, 1 },	// DOWN
		Pos { 1, 0 },	// RIGHT
		Pos { -1, -1 },	// UP_LEFT
		Pos { -1, 1 },	// UP_RIGHT
		Pos { 1, -1 },	// DOWN_LEFT
		Pos { 1, 1 },	// DOWN_RIGHT
	};

	int cost[] =
	{
		10,				// UP
		10,				// LEFT
		10,				// DOWN
		10,				// RIGHT
		14,				// UP_LEFT
		14,				// UP_RIGHT
		14,				// DOWN_LEFT
		14,				// DOWN_RIGHT
	};

	struct PQNode
	{
		bool operator<(const PQNode& other) const
		{
			return f < other.f;
		}

		bool operator>(const PQNode& other) const
		{
			return f > other.f;
		}

		int f;
		int g;
		Pos pos;
	};

	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
	vector<vector<int>> best(size, vector<int>(size, INT32_MAX));
	map<Pos, Pos> parent;

	int g = 0;
	int h = 10 * (abs(dest.x - start.x) + abs(dest.y - start.y));
	pq.push(PQNode{ g + h, g, start });
	best[start.y][start.x] = g + h;
	parent[start] = start;

	while (pq.empty() == false)
	{
		PQNode node = pq.top();
		pq.pop();

		if (node.pos == dest)
		{
			break;
		}

		for (int dir = 0; dir < DIR_COUNT; ++dir)
		{
			Pos nextPos = node.pos + front[dir];

			if (CanGo(nextPos) == false)
			{
				continue;
			}

			int g = node.g + cost[dir];
			int h = 10 * (abs(dest.x - nextPos.x) + abs(dest.y - nextPos.y));

			if (best[nextPos.y][nextPos.x] <= g + h)
			{
				continue;
			}

			best[nextPos.y][nextPos.x] = g + h;
			parent[nextPos] = node.pos;
			pq.push(PQNode{ g + h, g, nextPos });
		}
	}

	_path.clear();
	_pathIndex = 0;

	Pos pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (parent[pos] == pos)
		{
			break;
		}
		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}
