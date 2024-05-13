#include "pch.h"
#include "Player.h"
#include "Board.h"


void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// ������ �����ϱ� ������ ��� ����
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
		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��
		if (CanGo(pos + front[right]))
		{
			// ������ �������� 90�� ȸ��
			_dir = right;

			// ������ �� �� ����
			pos += front[_dir];

			// ��� ����
			_path.push_back(pos);
		}
		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			// ������ �� �� ����
			pos += front[_dir];

			// ��� ����
			_path.push_back(pos);
		}
		else
		{
			// ���� �������� 90�� ȸ��
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

	// ������ ����
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