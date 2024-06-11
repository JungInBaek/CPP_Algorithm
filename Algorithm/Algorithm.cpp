#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
#include "BinarySearchTree.h"

using namespace std;


void BubbleSort(vector<int>& v)
{
	int rear = v.size();
	while (rear > 0)
	{
		for (int i = 0; i < rear - 1; i++)
		{
			if (v[i] > v[i + 1])
			{
				int temp = v[i];
				v[i] = v[i + 1];
				v[i + 1] = temp;
			}
		}
		--rear;
	}
}

void SelectionSort(vector<int>& v)
{
	for (int i = 0; i < v.size() - 1; i++)
	{
		int index = i;
		for (int j = i + 1; j < v.size(); j++)
		{
			if (v[j] < v[index])
			{
				index = j;
			}
		}

		int temp = v[i];
		v[i] = v[index];
		v[index] = temp;
	}
}

void InsertionSort(vector<int>& v)
{
	for (int i = 0; i < v.size() - 1; i++)
	{
		int index = i + 1;
		int temp = v[index];
		for (int j = i; j >= 0; j--)
		{
			if (v[j] < temp)
			{
				break;
			}
			v[index] = v[j];
			index = j;
		}
		v[index] = temp;
	}
}

int main()
{
	vector<int> v{ 1, 5, 3, 4, 2 };
	//std::sort(v.begin(), v.end());

	//BubbleSort(v);
	//SelectionSort(v);
	InsertionSort(v);
}