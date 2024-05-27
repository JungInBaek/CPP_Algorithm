#include "pch.h"
#include "Player.h"
#include "Board.h"

#include <stack>


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
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
	Pos pos = _pos;
	Pos dest = _board->GetExitPos();
	Pos front[4] =
	{
		Pos { 0, -1 },	// UP
		Pos { -1, 0 },	// LEFT
		Pos { 0, 1 },	// DOWN
		Pos { 1, 0 },	// RIGHT
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size));
	map<Pos, Pos> parent;

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest)
		{
			break;
		}

		for (int32 dir = 0; dir < 4; ++dir)
		{
			Pos nextPos = pos + front[dir];

			if (CanGo(nextPos) == false)
			{
				continue;
			}

			if (discovered[nextPos.y][nextPos.x])
			{
				continue;
			}

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	_path.clear();

	pos = dest;
	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos])
		{
			break;
		}
		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}
