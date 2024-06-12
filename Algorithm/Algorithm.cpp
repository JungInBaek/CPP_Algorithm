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
	int rear = static_cast<int>(v.size());
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

void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>,greater<>> pq;

	for (int i = 0; i < v.size(); i++)
	{
		pq.push(v[i]);
	}

	v.clear();

	while (pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}

void MergeSort(vector<int>& v)
{
	int size = static_cast<int>(v.size());
	int half = size / 2;

	if (size <= 1)
	{
		return;
	}

	vector<int> v1;
	for (int i = 0; i < half; i++)
	{
		v1.push_back(v[i]);
	}

	vector<int> v2;
	for (int i = half; i < size; i++)
	{
		v2.push_back(v[i]);
	}

	MergeSort(v1);
	MergeSort(v2);

	v.clear();

	int left = 0;
	int right = 0;
	while (left < v1.size() && right < v2.size())
	{
		if (v1[left] < v2[right])
		{
			v.push_back(v1[left++]);
		}
		else
		{
			v.push_back(v2[right++]);
		}
	}

	if (left >= v1.size())
	{
		while (right < v2.size())
		{
			v.push_back(v2[right++]);
		}
	}
	else
	{
		while (left < v1.size())
		{
			v.push_back(v1[left++]);
		}
	}
}

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	vector<int> temp;

	int idxL = left;
	int idxR = mid + 1;
	while (idxL <= mid && idxR <= right)
	{
		if (v[idxL] < v[idxR])
		{
			temp.push_back(v[idxL++]);
		}
		else
		{
			temp.push_back(v[idxR++]);
		}
	}

	if (idxL > mid)
	{
		while (idxR <= right)
		{
			temp.push_back(v[idxR++]);
		}
	}
	else
	{
		while (idxL <= mid)
		{
			temp.push_back(v[idxL++]);
		}
	}

	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSortIndex(vector<int>& v, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;

	MergeSortIndex(v, left, mid);
	MergeSortIndex(v, mid + 1, right);
	
	MergeResult(v, left, mid, right);
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	vector<int> v;
	int size = 10;
	for (int i = 0; i < size; i++)
	{
		v.push_back((rand() % 50) + 1);
	}
	//std::sort(v.begin(), v.end());

	//BubbleSort(v);
	//SelectionSort(v);
	//InsertionSort(v);
	//HeapSort(v);
	//MergeSort(v);
	MergeSortIndex(v, 0, size - 1);
}