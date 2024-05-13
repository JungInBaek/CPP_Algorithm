#pragma once

#include <vector>
#include <stack>
#include <Windows.h>
#include <iostream>
using namespace std;

#include "Types.h"


struct Pos
{
	bool operator==(Pos& other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(Pos& other)
	{
		return x != other.x || y != other.y;
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