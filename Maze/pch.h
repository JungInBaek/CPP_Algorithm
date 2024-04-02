#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

#include "Types.h"


struct Pos
{
	bool operator==(const Pos& other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Pos& other)
	{
		return x != other.x || y != other.y;
	}

	Pos operator+(const Pos& other)
	{
		Pos ret;
		ret.x = x + other.x;
		ret.y = x + other.y;
		return ret;
	}

	Pos& operator+=(const Pos& other)
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