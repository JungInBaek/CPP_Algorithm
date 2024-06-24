#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
#include "BinarySearchTree.h"
#include "Windows.h"

using namespace std;


int cache[45][6];

int Combination(int n, int k)
{
	if (k == 0 || n == k)
	{
		return 1;
	}

	if (cache[n][k] != 0)
	{
		return cache[n][k];
	}

	return cache[n][k] = Combination(n - 1, k - 1) + Combination(n - 1, k);
}

int main()
{
	__int64 start = ::GetTickCount64();

	int loto = Combination(45, 6);

	__int64 end = ::GetTickCount64();

	cout << end - start << "ms" << endl;
}