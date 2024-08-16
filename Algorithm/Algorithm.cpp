#include <iostream>
#include <vector>
#include <algorithm>
#include "Windows.h"

using namespace std;
using uint64 = unsigned __int64;


struct Shoe
{
public:
	Shoe(int generateTime, int delay, int duration, int speed)
		: time(generateTime), start(generateTime + delay), end(generateTime + delay + duration), speed(speed)
	{
	}

public:
	int time;
	int start;
	int end;
	int speed;
};


int T;
vector<Shoe> shoes;
vector<int> cache;


// now번 신발을 신고 갈 수 있는 최대 거리 리턴
int Solve(int now)
{
	// 기저
	if (now >= shoes.size())
	{
		return 0;
	}

	// 캐시
	int& ret = cache[now];
	if (ret != -1)
	{
		return ret;
	}

	// 현재 신발
	Shoe& shoe = shoes[now];

	int dist = (shoe.end - shoe.start) * shoe.speed;
	dist += (T - shoe.end) * 1;
	ret = max(ret, dist);

	for (int next = now + 1; next < shoes.size(); next++)
	{
		// 다음 신발
		Shoe& nextShoe = shoes[next];
		if (nextShoe.time < shoe.start)
		{
			continue;
		}

		int nextDist = 0;
		if (nextShoe.time <= shoe.end)
		{
			nextDist = (nextShoe.time - shoe.start) * shoe.speed;
		}
		else
		{
			nextDist = (shoe.end - shoe.start) * shoe.speed;
			nextDist += (nextShoe.time - shoe.end) * 1;
		}

		ret = max(ret, nextDist + Solve(next));
	}

	return ret;
}

int main()
{
	T = 20;

	shoes.push_back(Shoe(0, 0, T, 1));
	shoes.push_back(Shoe(3, 4, 10, 3));
	shoes.push_back(Shoe(4, 1, 4, 2));
	shoes.push_back(Shoe(10, 2, 5, 5));
	shoes.push_back(Shoe(15, 1, 3, 7));
	
	std::sort(shoes.begin(), shoes.end(), [=](Shoe& left, Shoe& right) { return left.time < right.time; });

	cache.resize(shoes.size(), -1);

	int ret = Solve(0);
	cout << ret << endl;
}