#include <iostream>
#include <vector>
#include "Windows.h"

using namespace std;
using uint64 = unsigned __int64;


// +1 / +2 / +3씩 증가할 때
// num ~ N까지 경우의 수

uint64 N;
vector<uint64> cache;


uint64 Enchant(uint64 num)
{
	// 기저 사례
	if (num > N)
	{
		return 0;
	}

	if (num == N)
	{
		return 1;
	}

	// 캐시 확인
	uint64& ret = cache[num];
	if (ret != -1)
	{
		return ret;
	}

	// 계산 적용
	ret = 0;
	for (uint64 i = 1; i <= 3; i++)
	{
		ret += Enchant(num + i);
	}

	return ret;
}


int main()
{
	N = 34;

	cache.resize(N, -1);

	uint64 start = ::GetTickCount64();
	uint64 ret = Enchant(0);
	uint64 end = ::GetTickCount64();

	cout << ret << endl;
	cout << end - start << endl;
}