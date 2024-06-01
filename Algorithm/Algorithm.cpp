#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;


template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
	bool empty()
	{
		return _heap.empty();
	}

	T& top()
	{
		return _heap[0];
	}

	void pop()
	{
		int index = 0;
		_heap[index] = _heap.back();
		_heap.pop_back();

		if (_heap.empty())
		{
			return;
		}
		PopAlign(index);
	}

	void push(const T& data)
	{
		_heap.push_back(data);

		int index = static_cast<int>(_heap.size()) - 1;
		if (index == 0)
		{
			return;
		}
		PushAlign(index);
	}

	void PopAlign(int index)
	{
		int size = static_cast<int>(_heap.size());

		int child = (index * 2) + 1;
		if (child >= size)
		{
			return;
		}

		if (child + 1 < size && _predicate(_heap[child], _heap[child + 1]))
		{
			++child;
		}

		if (_predicate(_heap[child], _heap[index]))
		{
			return;
		}

		T temp = _heap[index];
		_heap[index] = _heap[child];
		_heap[child] = temp;

		if ((child * 2) + 1 >= size)
		{
			return;
		}

		PopAlign(child);
	}

	void PushAlign(int index)
	{
		int parent = (index - 1) / 2;
		if (_predicate(_heap[parent], _heap[index]))
		{
			T temp = _heap[index];
			_heap[index] = _heap[parent];
			_heap[parent] = temp;
		}

		if (parent == 0)
		{
			return;
		}
		PushAlign(parent);
	}

private:
	Container _heap = {};
	Predicate _predicate = {};
};

int main()
{
	//priority_queue<int, vector<int>, greater<int>> pq;

	PriorityQueue<int, vector<int>, greater<int>> pq;

	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(400);

	while (pq.empty() == false)
	{
		int value = pq.top();
		pq.pop();

		cout << value << endl;
	}
}