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