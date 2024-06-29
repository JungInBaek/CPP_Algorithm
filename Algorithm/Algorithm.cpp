#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
#include "BinarySearchTree.h"
#include "Windows.h"

using namespace std;


int cache[100];
vector<int> seq;

int LIS(int pos)
{
	int& ret = cache[pos];
	if (ret != -1)
	{
		return ret;
	}

	ret = 1;

	for (int next = pos + 1; next < seq.size(); next++)
	{
		if (seq[pos] < seq[next])
		{
			ret = max(ret, LIS(next) + 1);
		}
	}

	return ret;
}

int main()
{
	::memset(cache, -1, sizeof(cache));
	seq = vector<int>{ 10, 1, 9, 2, 5, 7 };

	int start = ::GetTickCount64();

	int len = 0;
	for (int pos = 0; pos < seq.size(); pos++)
	{
		len = max(len, LIS(pos));
	}

	int end = ::GetTickCount64();

	cout << end - start << "ms" << endl;
}