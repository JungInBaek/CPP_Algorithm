#pragma once

#include "Types.h"
#include <Windows.h>
#include <iostream>

#include <vector>
#include <queue>
#include <map>
using namespace std;



struct Pos
{
	bool operator==(const Pos& other) const
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(const Pos& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Pos& other) const
	{
		if (y != other.y)
		{
			return y < other.y;
		}
		return x < other.x;
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Pos& operator+=(Pos& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	int32 x = 0;
	int32 y = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4,
};